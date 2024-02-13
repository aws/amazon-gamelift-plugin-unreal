// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "AWSScenariosDeployer.h"

#include <Misc/FileHelper.h>

#include "aws/gamelift/core/exports.h"
#include "aws/gamelift/core/errors.h"

#include "GameLiftCoreLog.h"
#include "GameLiftCoreConstants.h"

#include "AwsAccount/AwsAccountCredentials.h"
#include "AwsAccount/AwsAccountInstanceManager.h"
#include "AwsAccount/AwsAccountInfo.h"
#include "Utils/StringPaths.h"
#include "Utils/StringConvertors.h"
#include "Utils/LogMessageStorage.h"
#include "Utils/NativeLogPrinter.h"
#include "AwsErrors/Converter.h"

#include "AwsScenarios/FlexMatch.h"
#include "AwsScenarios/SingleRegionFleet.h"
#include "AwsScenarios/CustomScenario.h"

#define LOCTEXT_NAMESPACE "AWSScenariosDeployer"

namespace AwsDeployerInternal
{
	static Logs::MessageStorage sLatestDeploymentLogErrorMessage = {};

	void LogCallback(unsigned int InLevel, const char* InMessage, int InSize)
	{
		auto Level = Logs::PrintAwsLog(InLevel, InMessage, InSize, Deploy::Logs::kLogReceived);

		if (Level == ELogVerbosity::Error)
		{
			sLatestDeploymentLogErrorMessage.Set(InMessage);
		}
	}

	void ReceiveReplacementId(DISPATCH_RECEIVER_HANDLE DispatchReceiver, const char* ReplacementId)
	{
		UE_LOG(GameLiftCoreLog, Verbose, TEXT("%s %s"), Deploy::Logs::kReceiveReplacementIdCallback, *Convertors::ASToFS(ReplacementId));
		((AWSScenariosDeployer*)DispatchReceiver)->SetMainFunctionsReplacementId(ReplacementId);
	}

	void ReceiveClientConfigPath(DISPATCH_RECEIVER_HANDLE DispatchReceiver, const char* ConfigPath)
	{
		UE_LOG(GameLiftCoreLog, Verbose, TEXT("%s %s"), Deploy::Logs::kReceiveClientConfigPathCallback, *Convertors::ASToFS(ConfigPath));
		((AWSScenariosDeployer*)DispatchReceiver)->SetClientConfigPath(ConfigPath);
	}

	auto BuildAwsScenarios()
	{
		TMap<FString, TUniquePtr<AwsScenarios::IAWSScenario>> ScenarioMap;
		ScenarioMap.Add(AwsScenarios::SingleRegionFleet::Name().ToString(), AwsScenarios::SingleRegionFleet::Create());
		ScenarioMap.Add(AwsScenarios::FlexMatch::Name().ToString(), AwsScenarios::FlexMatch::Create());

		return ScenarioMap;
	}

	const auto& GetAwsScenarios()
	{
		static TMap<FString, TUniquePtr<AwsScenarios::IAWSScenario>> ScenarioMap(BuildAwsScenarios());
		return ScenarioMap;
	}

	AwsScenarios::IAWSScenario* GetAwsScenarioByName(const FText& ScenarioName)
	{
		auto Invariant = FText::AsCultureInvariant(ScenarioName);
		return GetAwsScenarios().FindChecked(Invariant.ToString()).Get();
	}

	FString ExtractYamlValue(const TArray<FString>& YamlStrings, const char* Name)
	{
		for (const FString& Line : YamlStrings)
		{
			auto FoundPosition = Line.Find(Name);

			if (FoundPosition >= 0)
			{
				FoundPosition += strlen(Name);
				return Line.RightChop(FoundPosition + 1);
			}
		}
		return FString();
	}

	class ResourcesInstanceGuard
	{
	public:
		ResourcesInstanceGuard(IAWSAccountInstance* AwsAccountInstance) :
			Instance(GameLiftAccountCreateGameLiftResourcesInstance(AwsAccountInstance->GetInstance()))
		{
		}

		~ResourcesInstanceGuard()
		{
			GameLiftResourcesInstanceRelease(Instance);
		}

		GAMELIFT_FEATURERESOURCES_INSTANCE_HANDLE Get()
		{
			return Instance;
		}

	private:
		GAMELIFT_FEATURERESOURCES_INSTANCE_HANDLE Instance;
	};

	bool IsDeployedSuccessfully(const std::string& StackStatus)
	{
		static std::unordered_set<std::string> SuccessfulStatuses
		{
			Aws::Status::kStackUpdateComplete, Aws::Status::kStackCreateComplete
		};

		return SuccessfulStatuses.find(StackStatus) != SuccessfulStatuses.end();
	}
} // namespace AwsDeployerInternal

void AWSScenariosDeployer::SetMainFunctionsReplacementId(const char* ReplacementId)
{
	MainFunctionsReplacementId = ReplacementId;
}

void AWSScenariosDeployer::SetClientConfigPath(const char* ConfigPath)
{
	ClientConfigPath = Convertors::ASToFS(ConfigPath);
}

void AWSScenariosDeployer::SetLastCognitoClientId(const FString& ClientId)
{
	LastCognitoClientId = ClientId;
}

void AWSScenariosDeployer::SetLastApiGatewayEndpoint(const FString& ApiGateway)
{
	LastApiGatewayEndpoint = ApiGateway;
}

bool AWSScenariosDeployer::DeployScenario(
	const FText& Scenario, 
	IAWSAccountInstance* AwsAccountInstance, 
	const FString& GameName,
	const FString& BuildOperatingSystem,
	const FString& BuildFolderPath, 
	const FString& BuildFilePath, 
	const FString& OutConfigFilePath, 
	const FString& ExtraServerResourcesPath
)
{
	UE_LOG(GameLiftCoreLog, Log, TEXT("%s %s"), Deploy::Logs::kRunAwsScenario, *Scenario.ToString());

	AwsScenarios::IAWSScenario* AwsScenario = AwsDeployerInternal::GetAwsScenarioByName(Scenario);
	return DeployScenarioImpl(AwsAccountInstance, AwsScenario, GameName, BuildOperatingSystem, BuildFolderPath, BuildFilePath, OutConfigFilePath, ExtraServerResourcesPath);
}

bool AWSScenariosDeployer::DeployCustomScenario(
	const FString& CustomScenarioPath, 
	IAWSAccountInstance* AwsAccountInstance,
	const FString& GameName,
	const FString& BuildOperatingSystem,
	const FString& BuildFolderPath,
	const FString& BuildFilePath,
	const FString& OutConfigFilePath,
	const FString& ExtraServerResourcesPath
)
{
	UE_LOG(GameLiftCoreLog, Log, TEXT("%s %s"), Deploy::Logs::kRunCustomScenario, *CustomScenarioPath);

	TUniquePtr<AwsScenarios::IAWSScenario> AwsScenario = AwsScenarios::CustomScenario::Create(CustomScenarioPath);
	return DeployScenarioImpl(AwsAccountInstance, AwsScenario.Get(), GameName, BuildOperatingSystem, BuildFolderPath, BuildFilePath, OutConfigFilePath, ExtraServerResourcesPath);
}

bool AWSScenariosDeployer::StopDeployment(IAWSAccountInstance* AwsAccountInstance)
{
	UE_LOG(GameLiftCoreLog, Log, TEXT("%s"), Deploy::Logs::kDeploymentStop);

	AwsDeployerInternal::sLatestDeploymentLogErrorMessage.Clear();

	if (!AwsAccountInstance->IsValid())
	{
		AwsDeployerInternal::sLatestDeploymentLogErrorMessage.Set(Deploy::Errors::kAccountIsInvalidText);
		return false;
	}

	AwsDeployerInternal::ResourcesInstanceGuard ResourcesInstance(AwsAccountInstance);
	std::string StackStatus = GameLiftResourcesGetCurrentStackStatus(ResourcesInstance.Get());

	if (StackStatus.compare(Aws::Status::kStackUndeployed) == 0)
	{
		AwsDeployerInternal::sLatestDeploymentLogErrorMessage.Set(Deploy::Errors::kNoStacksToStopDeployment);
		return false;
	}

	ShouldBeStopped = true;
	bool IsStopped = GameLiftResourcesInstanceCancelUpdateStack(ResourcesInstance.Get()) == GameLift::GAMELIFT_SUCCESS;

	if (!IsStopped)
	{
		AwsDeployerInternal::sLatestDeploymentLogErrorMessage.Set(Deploy::Errors::kUnableToStopDeployment);
	}

	return IsStopped;
}

bool AWSScenariosDeployer::DeployScenarioImpl(
	IAWSAccountInstance* AwsAccountInstance, 
	AwsScenarios::IAWSScenario* AwsScenario, 
	const FString& GameName,
	const FString& BuildOperatingSystem, 
	const FString& BuildFolderPath, 
	const FString& BuildFilePath, 
	const FString& OutConfigFilePath,
	const FString& ExtraServerResourcesPath
)
{
	constexpr auto DeployAbortResult = false;
	constexpr auto DeployCompletedResult = true;

	AwsDeployerInternal::sLatestDeploymentLogErrorMessage.Clear();

	ShouldBeStopped = false;

	auto AccountHandle = AwsAccountInstance->GetInstance();

	if (AccountHandle == nullptr)
	{
		AwsDeployerInternal::sLatestDeploymentLogErrorMessage.Set(Deploy::Errors::kAccountIsInvalidText);
		LastAwsError = GameLift::GAMELIFT_ERROR_GENERAL;
		UE_LOG(GameLiftCoreLog, Error, TEXT("%s"), Deploy::Logs::kAccountInstanceIsNull);
		return DeployAbortResult;
	}

	if (GameName.Len() > Deploy::kMaxGameNameLength)
	{
		AwsDeployerInternal::sLatestDeploymentLogErrorMessage.Set(Deploy::Errors::kGameNameIsTooLongText);
		LastAwsError = GameLift::GAMELIFT_ERROR_GENERAL;
		return DeployAbortResult;
	}

	auto StdGameName = Convertors::FSToStdS(GameName);
	GameLiftAccountSetGameName(AccountHandle, StdGameName.c_str());

	auto ScenarioPath = AwsScenario->GetScenarioPath();
	auto StdScenarioPath = Convertors::FSToStdS(ScenarioPath);
	GameLiftAccountSetPluginRootPath(AccountHandle, StdScenarioPath.c_str());

	auto ScenarioInstancePath = AwsScenario->GetScenarioInstancePath();
	auto StdScenarioInstancePath = Convertors::FSToStdS(ScenarioInstancePath);
	GameLiftAccountSetRootPath(AccountHandle, StdScenarioInstancePath.c_str());

	auto StdBuildOperatingSystemParameter = Convertors::FSToStdS(BuildOperatingSystem);

	std::string StdAwsAccountId = GameLiftGetAwsAccountIdByAccountInstance(AccountHandle);

	if (ShouldBeStopped)
	{
		LastAwsError = GameLift::GAMELIFT_ERROR_GENERAL;
		UE_LOG(GameLiftCoreLog, Error, TEXT("%s"), Deploy::Logs::kDeploymentHasBeenStopped);
		return DeployAbortResult;
	}

	auto ShouldDeployBeAborted = [this](int ErrorCode, auto&& ErrorDebugString)
	{
		LastAwsError = ErrorCode;

		if (LastAwsError != GameLift::GAMELIFT_SUCCESS)
		{
			UE_LOG(GameLiftCoreLog, Error, TEXT("%s %s"), ErrorDebugString, *GameLiftErrorAsString::Convert(LastAwsError));
			return true;
		}

		if (ShouldBeStopped)
		{
			LastAwsError = GameLift::GAMELIFT_ERROR_GENERAL;
			UE_LOG(GameLiftCoreLog, Error, TEXT("%s"), Deploy::Logs::kDeploymentHasBeenStopped);
			return true;
		}

		return false;
	};

	if (ShouldDeployBeAborted(GameLiftAccountCreateAndSetFunctionsReplacementId(AccountHandle), Deploy::Logs::kCreateAndSetFunctionsReplacementIdFailed))
	{
		return DeployAbortResult;
	}

	if (ShouldDeployBeAborted(GameLiftAccountGetMainFunctionsReplacementId(AccountHandle, this, AwsDeployerInternal::ReceiveReplacementId),
		Deploy::Logs::kGetMainFunctionsReplacementIdFailed))
	{
		return DeployAbortResult;
	}

	auto StdBootstrapBucketName = Convertors::FSToStdS(AwsAccountInstance->GetBucketName());
	auto StdBuildFolderPath = Convertors::FSToStdS(BuildFolderPath);
	auto StdExtraServerResourcesPath = Convertors::FSToStdS(ExtraServerResourcesPath);

	if (ShouldDeployBeAborted(AwsScenario->UploadGameServer(AwsAccountInstance, StdBuildFolderPath.c_str(), StdExtraServerResourcesPath.c_str()),
		Deploy::Logs::kUploadGameServerFailed))
	{
		return DeployAbortResult;
	}

	std::string StdLaunchPathParameter;
	if (ShouldDeployBeAborted(AwsScenario->CreateLaunchPathParameter(BuildOperatingSystem, BuildFolderPath, BuildFilePath, StdLaunchPathParameter),
		Deploy::Logs::kCreateLaunchPathParameterFailed))
	{
		return DeployAbortResult;
	}

	AwsScenarios::InstanceTemplateParams Params;
	Params.GameNameParameter = Convertors::FSToStdS(AwsAccountInstance->GetGameName());
	Params.BuildOperatingSystemParameter = StdBuildOperatingSystemParameter;
	Params.BuildS3BucketParameter = StdBootstrapBucketName;
	Params.LambdaZipS3BucketParameter = StdBootstrapBucketName;
	Params.LambdaZipS3KeyParameter = AwsScenarios::GetLambdaS3Key(StdGameName, MainFunctionsReplacementId);
	Params.ApiGatewayStageNameParameter = AwsAccountInstance->GetBuildConfiguration();
	Params.AccountId = StdAwsAccountId;
	Params.LaunchPathParameter = StdLaunchPathParameter;

	if (ShouldDeployBeAborted(AwsScenario->SaveFeatureInstanceTemplate(AwsAccountInstance, Params),
		Deploy::Logs::kSaveFeatureInstanceTemplatesFailed))
	{
		return DeployAbortResult;
	}

	if (ShouldDeployBeAborted(GameLiftAccountUploadFunctions(AccountHandle), Deploy::Logs::kAccountUploadFunctionsFailed))
	{
		return DeployAbortResult;
	}

	if (ShouldDeployBeAborted(GameLiftAccountCreateOrUpdateMainStack(AccountHandle), Deploy::Logs::kCreateOrUpdateMainStackFailed))
	{
		return DeployAbortResult;
	}

	if (ShouldDeployBeAborted(GameLiftAccountDeployApiGatewayStage(AccountHandle), Deploy::Logs::kDeployApiGatewayStageFailed))
	{
		return DeployAbortResult;
	}

	if (ShouldDeployBeAborted(UpdateDeploymentResults(AwsAccountInstance, ScenarioInstancePath, GameName, AwsAccountInstance->GetBucketName(), OutConfigFilePath), 
		Deploy::Logs::kDeploymentStackStatusFailed))
	{
		return DeployAbortResult;
	}

	return DeployCompletedResult;
}

int AWSScenariosDeployer::UpdateDeploymentResults(IAWSAccountInstance* AwsAccountInstance, const FString& ScenarioInstancePath, const FString& GameName, const FString& BucketName, const FString& OutConfigFilePath)
{
	AwsDeployerInternal::ResourcesInstanceGuard ResourcesInstance(AwsAccountInstance);

	// Result will be stored to ClientConfigPath with sync call.
	GameLiftResourcesGetInstanceClientConfigPath(ResourcesInstance.Get(), this, AwsDeployerInternal::ReceiveClientConfigPath);
	std::string StackStatus = GameLiftResourcesGetCurrentStackStatus(ResourcesInstance.Get());
	UE_LOG(GameLiftCoreLog, Log, TEXT("%s %s"), Deploy::Logs::kDeploymentStackStatus, *Convertors::ASToFS(StackStatus.c_str()));

	auto CurrentScenarioInstancePath = Paths::ScenarioInstancePath(Menu::DeploymentServer::kCurrentScenarioFolder);

	FString ConfigPathPart, ConfigFilenamePart, ConfigExtensionPart;
	FPaths::Split(ClientConfigPath, ConfigPathPart, ConfigFilenamePart, ConfigExtensionPart);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	PlatformFile.DeleteDirectoryRecursively(*CurrentScenarioInstancePath);
	PlatformFile.CopyDirectoryTree(*CurrentScenarioInstancePath, *ConfigPathPart, true);

	FString DestinationFileName = ConfigFilenamePart + "." + ConfigExtensionPart;
	PlatformFile.CreateDirectoryTree(*OutConfigFilePath);
	PlatformFile.CopyFile(*FPaths::Combine(OutConfigFilePath, DestinationFileName), *ClientConfigPath);

	FString UUID;
	FString Temp;
	BucketName.Split("-", &Temp, &UUID, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	FString Region;
	Temp.Split("-", &Temp, &Region, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	FString DestinationFileNameExtra = GameName + "_" + UUID + "_" + Region + "_" + ConfigFilenamePart + "." + ConfigExtensionPart;
	PlatformFile.CopyFile(*FPaths::Combine(OutConfigFilePath, DestinationFileNameExtra), *ClientConfigPath);

	TArray<FString> YamlStrings;
	FFileHelper::LoadANSITextFileToStrings(*ClientConfigPath, NULL, YamlStrings);
	LastCognitoClientId = AwsDeployerInternal::ExtractYamlValue(YamlStrings, Aws::Config::kUserPoolClientIdYamlName).TrimStartAndEnd();
	LastApiGatewayEndpoint = AwsDeployerInternal::ExtractYamlValue(YamlStrings, Aws::Config::kApiGatewayEndpointYamlName).TrimStartAndEnd();

	return AwsDeployerInternal::IsDeployedSuccessfully(StackStatus) ?
		GameLift::GAMELIFT_SUCCESS : GameLift::GAMELIFT_ERROR_GENERAL;
}

FString AWSScenariosDeployer::GetLastCognitoClientId() const
{
	return LastCognitoClientId;
}

FString AWSScenariosDeployer::GetLastApiGatewayEndpoint() const
{
	return LastApiGatewayEndpoint;
}

FString AWSScenariosDeployer::GetLastError() const
{
	return GameLiftErrorAsString::Convert(LastAwsError);
}

FString AWSScenariosDeployer::GetLastErrorMessage() const
{
	return AwsDeployerInternal::sLatestDeploymentLogErrorMessage.Get();
}

TArray<FText> AWSScenariosDeployer::GetScenarios() const
{
	TArray<FText> Result;
	const auto& Scenarios = AwsDeployerInternal::GetAwsScenarios();
	Result.Reserve(Scenarios.Num());

	for (const auto& Item : Scenarios)
	{
		Result.Add(Item.Value->GetUserName());
	}

	return Result;
}

FText AWSScenariosDeployer::GetToolTip(const FText& ScenarioName) const
{
	return AwsDeployerInternal::GetAwsScenarioByName(ScenarioName)->GetTooltip();
}

#undef LOCTEXT_NAMESPACE
