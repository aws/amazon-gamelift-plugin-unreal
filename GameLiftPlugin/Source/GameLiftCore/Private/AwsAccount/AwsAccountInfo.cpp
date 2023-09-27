// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "AwsAccountInfo.h"

#include "GameLiftCoreLog.h"
#include "GameLiftCoreConstants.h"

#include <Misc/App.h>
#include <Interfaces/IPluginManager.h>
#include <Runtime/EngineSettings/Classes/GeneralProjectSettings.h>

#include "aws/gamelift/core/exports.h"

namespace AwsAccountInfoInternal
{
	void LogCallback(unsigned int InLevel, const char* InMessage, int InSize)
	{
		UE_LOG(GameLiftCoreLog, Log, TEXT("AwsAccountInfo: %s"), *FString(InMessage));
	}
} // namespace AwsAccountInfoInternal

int AwsAccountInfo::BuildAccountInfo()
{
	StdGameName = Convertors::FSToStdS(FApp::GetName());
	StdBuildConfiguration = "dev";

	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	StdCompanyName = Convertors::FSToStdS(ProjectSettings->CompanyName);

	return GameLift::GAMELIFT_SUCCESS;
}

void AwsAccountInfo::SetGameName(std::string NewGameName)
{
	StdGameName = NewGameName;
}

GameLift::AccountInfo AwsAccountInfo::GetAccountInfo() const
{
	auto GetCString = [&](const std::string& StdString) -> const char*
	{
		return StdString.length() > 1 ? StdString.c_str() : "";
	};

	GameLift::AccountInfo GameLiftAccountInfo;
	GameLiftAccountInfo.environment = GetCString(StdBuildConfiguration);
	GameLiftAccountInfo.accountId = GetCString(StdAccountId);
	GameLiftAccountInfo.companyName = GetCString(StdCompanyName);
	GameLiftAccountInfo.gameName = GetCString(StdGameName);
	return GameLiftAccountInfo;
}

const std::string& AwsAccountInfo::GetAccountId() const
{
	return StdAccountId;
}

const std::string& AwsAccountInfo::GetBuildConfiguration() const
{
	return StdBuildConfiguration;
}

const std::string& AwsAccountInfo::GetCompanyName() const
{
	return StdCompanyName;
}

const std::string& AwsAccountInfo::GetGameName() const
{
	return StdGameName;
}
