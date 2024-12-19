// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "FGameLiftCoreModule.h"

#include "CoreMinimal.h"

#include "GameLiftCoreProc.h"
#include "AWSScenariosDeployer.h"
#include "AWSConfigFileProfile.h"
#include "AWSBootstrapProfile.h"
#include "Anywhere/GameLiftAnywhereHandler.h"
#include "Containers/GameLiftContainersHandler.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif

#include "aws/core/Aws.h"
#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/client/AWSClient.h>
#include <aws/core/client/AWSErrorMarshaller.h>

#include <aws/gamelift/core/gamelift_account.h>
#include <aws/gamelift/core/exports.h>

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#include "GameLiftCoreLog.h"

namespace Internal
{
	void LogCallback(unsigned int Level, const char* Message, int Size)
	{
		std::cout << __FUNCTION__ << ": level [" << Level << "], message [" << Message << "], size [" << Size << "]\n";
	}

	class SimpleCaller
	{
	public:
		virtual void OnHandleResult(const char* Result)
		{
			std::cout << "GameLiftGetAwsAccountId result :  " << Result << std::endl;
		}

		static void OnCallback(void* DispatchReceiver, const char* CharPtr)
		{
			SimpleCaller* Instance = static_cast<SimpleCaller*>(DispatchReceiver);
			return Instance->OnHandleResult(CharPtr);
		}
	};
} // namespace Internal

#define LOCTEXT_NAMESPACE "FGameLiftCoreModule"

static void TestGameLiftCore()
{
	const char* AccessKey = nullptr;
	const char* SecretKey = nullptr; // Use your secret.

	Internal::SimpleCaller Caller;
	unsigned int result = GameLiftGetAwsAccountId(&Caller, &Internal::SimpleCaller::OnCallback, AccessKey, SecretKey, Internal::LogCallback);
}

//***************************************************************************************************************************

static class UUserWidget* CreatedWidget;

FGameLiftCoreModule::FGameLiftCoreModule()
	: Deployer(new AWSScenariosDeployer), ProfileBootstrap(new AWSBootstrapProfile), AnywhereHandler(new GameLiftAnywhereHandler), ContainersHandler(new GameLiftContainersHandler)
{
}

void FGameLiftCoreModule::StartupModule()
{
	UE_LOG(GameLiftCoreLog, Display, TEXT("%s"), Core::Logs::kStartupModule);

	// TEST : AWS Core Library ...
	//TestGameLiftCore();

	auto LogProxy = [](unsigned int InLevel, const char* InMessage, int InSize)
	{
		UE_LOG(GameLiftCoreLog, Log, TEXT(">>>>> %s"), UTF8_TO_TCHAR(InMessage));
	};

	GameLift::AwsApiInitializer::Initialize(LogProxy, this);

	UE_LOG(GameLiftCoreLog, Display, TEXT("%s"), Core::Logs::kDllLoaded);
}

void FGameLiftCoreModule::ShutdownModule()
{
	UE_LOG(GameLiftCoreLog, Display, TEXT("%s"), Core::Logs::kShutdownModule);

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GameLiftCoreTabName);

	GameLift::AwsApiInitializer::Shutdown();
}

bool FGameLiftCoreModule::SupportsDynamicReloading()
{
	return true;
}

TSharedRef<IGameLiftCoreProc> FGameLiftCoreModule::MakeRunner()
{
	return MakeShared<GameLiftCoreProc>();
}

IAWSScenariosDeployer& FGameLiftCoreModule::GetScenarioDeployer()
{
	return *Deployer;
}

IAWSBootstrapProfile& FGameLiftCoreModule::GetProfileBootstrap()
{
	return *ProfileBootstrap;
}

IGameLiftAnywhereHandler& FGameLiftCoreModule::GetGameLiftAnywhereHandler()
{
	return *AnywhereHandler;
}

IGameLiftContainersHandler& FGameLiftCoreModule::GetGameLiftContainersHandler()
{
	return *ContainersHandler;
}

TSharedRef<IAWSConfigFileProfile> FGameLiftCoreModule::MakeAWSConfigFileProfile()
{
	return MakeShared<AWSConfigFileProfile>();
}

IMPLEMENT_MODULE(FGameLiftCoreModule, GameLiftCore);

#undef LOCTEXT_NAMESPACE
