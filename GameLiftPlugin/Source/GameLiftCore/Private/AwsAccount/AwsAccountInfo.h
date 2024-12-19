// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

#include "IAWSConfigFileProfile.h"
#include "Utils/StringConvertors.h"

#include "aws/gamelift/core/model/account_info.h"

class AwsAccountInfo
{
public:
	AwsAccountInfo(const char* AccountId = "") : StdAccountId(AccountId) {}

	GameLift::AccountInfo GetAccountInfo() const;

	int BuildAccountInfo(std::string BootstrapBucketName = "");

	void SetGameName(std::string NewGameName);
	void SetBucketName(std::string NewBucketName);

	const std::string& GetAccountId() const;
	const std::string& GetBucketName() const;
	const std::string& GetBuildConfiguration() const;
	const std::string& GetCompanyName() const;
	const std::string& GetGameName() const;

private:
	std::string StdAccountId;
	std::string StdBucketName;
	std::string StdBuildConfiguration;  
	std::string StdCompanyName;
	std::string StdGameName;
};
