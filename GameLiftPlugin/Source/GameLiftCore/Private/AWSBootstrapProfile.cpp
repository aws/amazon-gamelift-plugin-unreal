// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "AWSBootstrapProfile.h"

#include "AwsAccount/AwsAccountInstanceManager.h"

#include "GameLiftCoreLog.h"
#include "GameLiftCoreConstants.h"
#include "IGameLiftCoreModule.h"
#include "Utils/StringPaths.h"
#include "Utils/LogMessageStorage.h"
#include "Utils/NativeLogPrinter.h"

#include "aws/gamelift/core/exports.h"
#include "aws/gamelift/core/errors.h"
#include "AwsErrors/Converter.h"

namespace AwsBootstrapInternal
{
	static Logs::MessageStorage sLatestDeploymentLogErrorMessage = {};

	void LogCallback(unsigned int InLevel, const char* InMessage, int InSize)
	{
		auto Level = Logs::PrintAwsLog(InLevel, InMessage, InSize, Bootstrap::Logs::kLogReceived);

		if (Level == ELogVerbosity::Error)
		{
			sLatestDeploymentLogErrorMessage.Set(InMessage);
		}
	}

	class EmptyAccount : public IAWSAccountInstance
	{
	public:
		bool IsValid() const override { return false; }
		void* GetInstance() const override { return nullptr; }
		FString GetBucketName() const override { return FString(); }
		const char* GetGameName() const override { return ""; }
		const char* GetAccountId() const override { return ""; }
		const char* GetBuildConfiguration() const override { return ""; }
		FString GetLastErrorMessage() const override { return FString(); }
	};

	void ReceiveResult(DISPATCH_RECEIVER_HANDLE DispatchReceiver, const char* BucketName)
	{
		UE_LOG(GameLiftCoreLog, Log, TEXT("%s %s"), Bootstrap::Logs::kReceiveBucketNameCallback, *FString(BucketName));
		((AwsAccountInstanceManager*)DispatchReceiver)->SetBucketName(BucketName);
	}
} // namespace AwsBootstrapInternal

#define LOCTEXT_NAMESPACE "AWSBootstrapProfile"

AWSBootstrapProfile::AWSBootstrapProfile() :
	AwsAccountInstance(MakeUnique<AwsBootstrapInternal::EmptyAccount>())
{
}

bool AWSBootstrapProfile::ConfigureAccount(const FString& ProfileName, 
	TSharedRef<IAWSConfigFileProfile> ProfileReader, const FString& NewBucketName)
{
	UE_LOG(GameLiftCoreLog, Log, TEXT("%s"), Bootstrap::Logs::kBootstrapStarted);
	AwsBootstrapInternal::sLatestDeploymentLogErrorMessage.Clear();

	AwsAccountInstance = MakeUnique<AwsBootstrapInternal::EmptyAccount>();
	TUniquePtr<AwsAccountInstanceManager> AccountInstance = MakeUnique<AwsAccountInstanceManager>();

	FString PluginRootPath = Paths::ScenarioPath("scenario_common");
	FString GameLiftRootPath = Paths::ScenarioInstancePath("scenario_common");

	LastError = AccountInstance->BuildInstance(ProfileName, ProfileReader, GameLiftRootPath, PluginRootPath);

	if (LastError != GameLift::GAMELIFT_SUCCESS)
	{
		AwsBootstrapInternal::sLatestDeploymentLogErrorMessage.Set(AccountInstance->GetLastErrorMessage());
		UE_LOG(GameLiftCoreLog, Warning, TEXT("%s %s."), Bootstrap::Logs::kBootstrapFailedCreateAccount, *GameLiftErrorAsString::Convert(LastError));
		return false;
	}

	AccountInstance->SetBucketName(NewBucketName);

	AwsAccountInstance = std::move(AccountInstance);
	return true;
}

bool AWSBootstrapProfile::Bootstrap()
{
	AwsBootstrapInternal::sLatestDeploymentLogErrorMessage.Clear();

	if (AwsAccountInstance->IsValid())
	{
		LastError = GameLiftAccountInstanceBootstrap(AwsAccountInstance->GetInstance(), AwsAccountInstance.Get(), &AwsBootstrapInternal::ReceiveResult);

		if (LastError == GameLift::GAMELIFT_SUCCESS)
		{
			UE_LOG(GameLiftCoreLog, Log, TEXT("%s"), Bootstrap::Logs::kBootstrapCompleted);
			return true;
		}
		else
		{
			UE_LOG(GameLiftCoreLog, Warning, TEXT("%s %s."), Bootstrap::Logs::kBootstrapFailedBootstrap, *GameLiftErrorAsString::Convert(LastError));
			return false;
		}
	}

	LastError = GameLift::GAMELIFT_ERROR_GENERAL;
	UE_LOG(GameLiftCoreLog, Warning, TEXT("%s"), Bootstrap::Logs::kBootstrapFailedAccountNotValid);

	return false;
}

FString AWSBootstrapProfile::GetLastError() const
{
	return GameLiftErrorAsString::Convert(LastError);
}

FString AWSBootstrapProfile::GetLastErrorMessage() const
{	
	return AwsBootstrapInternal::sLatestDeploymentLogErrorMessage.Get();
}

IAWSAccountInstance* AWSBootstrapProfile::GetAccountInstance()
{
	return AwsAccountInstance.Get();
}

#undef LOCTEXT_NAMESPACE

