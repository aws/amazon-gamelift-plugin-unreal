// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

#include "IAWSConfigFileProfile.h"
#include "Utils/StringConvertors.h"

#include "aws/gamelift/core/model/account_credentials.h"

class AwsAccountCredentials
{
public:
	AwsAccountCredentials(const FString& ProfileName, TSharedRef<IAWSConfigFileProfile> ProfileReader);

	GameLift::AccountCredentials GetCredentials() const;
	int BuildCredentials();

private:
	std::string StdRegion;
	std::string StdAccessKey;
	std::string StdSecretKey;
	std::string StdAccountId;
};
