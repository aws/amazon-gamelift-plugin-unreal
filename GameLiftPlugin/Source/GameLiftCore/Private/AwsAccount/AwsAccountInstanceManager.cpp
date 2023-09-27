// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "AwsAccountInstanceManager.h"

#include "GameLiftCoreLog.h"
#include "GameLiftCoreConstants.h"

#include "aws/gamelift/core/errors.h"
#include "aws/gamelift/core/exports.h"

#include "AwsAccount/AwsAccountCredentials.h"
#include "AwsAccount/AwsAccountInfo.h"

#include "Utils/StringPaths.h"
#include "Utils/NativeLogPrinter.h"
#include "Utils/LogMessageStorage.h"

namespace AwsAccountInstanceInternal
{
	static Logs::MessageStorage sLatestAccountConfigurationLogErrorMessage = {};

	void LogCallback(unsigned int InLevel, const char* InMessage, int InSize)
	{
		auto Level = Logs::PrintAwsLog(InLevel, InMessage, InSize, Account::Logs::kLogReceived);

		if (Level == ELogVerbosity::Error)
		{
			sLatestAccountConfigurationLogErrorMessage.Set(InMessage);
		}
	}
} // namespace AwsAccountInstanceInternal

AwsAccountInstanceManager::AwsAccountInstanceManager()
	: AccountInstance(nullptr)
{
}

AwsAccountInstanceManager::~AwsAccountInstanceManager()
{
	ReleaseInstance();
}

bool AwsAccountInstanceManager::IsValid() const
{
	return GameLiftAccountHasValidCredentials(static_cast<GAMELIFT_ACCOUNT_INSTANCE_HANDLE>(AccountInstance));
}

FString AwsAccountInstanceManager::GetBucketName() const
{
	return BucketName;
}

int AwsAccountInstanceManager::BuildInstance(const FString& InProfile, TSharedRef<IAWSConfigFileProfile> InProfileReader, const FString& InRootPath, const FString& InPluginRootPath)
{
	ReleaseInstance();

	auto result = AccountInfo.BuildAccountInfo();

	if (result != GameLift::GAMELIFT_SUCCESS)
	{
		UE_LOG(GameLiftCoreLog, Warning, TEXT("%s"), Account::Logs::kUnableToBuildAccountInfo);
		return result;
	}

	GameLift::AccountInfo AccountInfoData = AccountInfo.GetAccountInfo();
	std::string StdRootPath = Convertors::FSToStdS(InRootPath);
	std::string StdPluginRootPath = Convertors::FSToStdS(InPluginRootPath);
	std::string ProfileName = Convertors::FSToStdS(InProfile);

	AccountInstance = GameLiftAccountInstanceCreateWithRootPathsAndProfile(
		AccountInfoData,
		ProfileName.c_str(),
		StdRootPath.c_str(),
		StdPluginRootPath.c_str(),
		&AwsAccountInstanceInternal::LogCallback
	);

	if (AccountInstance == nullptr)
	{
		UE_LOG(GameLiftCoreLog, Warning, TEXT("%s"), Account::Logs::kAccountIsNotCreated);
		return GameLift::GAMELIFT_ERROR_GENERAL;
	}

	if (!IsValid())
	{
		UE_LOG(GameLiftCoreLog, Warning, TEXT("%s"), Account::Logs::kAccountIsInvalid);
		return GameLift::GAMELIFT_ERROR_GENERAL;
	}

	return GameLift::GAMELIFT_SUCCESS;
}

void AwsAccountInstanceManager::ReleaseInstance()
{
	AwsAccountInstanceInternal::sLatestAccountConfigurationLogErrorMessage.Clear();

	if (AccountInstance != nullptr)
	{
		GameLiftAccountInstanceRelease(AccountInstance);
	}
}

void AwsAccountInstanceManager::SetBucketName(const FString& NewBucketName)
{
	BucketName = NewBucketName;
}

void* AwsAccountInstanceManager::GetInstance() const
{
	return AccountInstance;
}

const char* AwsAccountInstanceManager::GetGameName() const
{
	return AccountInfo.GetGameName().c_str();
}

const char* AwsAccountInstanceManager::GetAccountId() const
{
	return AccountInfo.GetAccountId().c_str();
}

const char* AwsAccountInstanceManager::GetBuildConfiguration() const
{
	return AccountInfo.GetBuildConfiguration().c_str();
}

FString AwsAccountInstanceManager::GetLastErrorMessage() const
{
	return AwsAccountInstanceInternal::sLatestAccountConfigurationLogErrorMessage.Get();
}
