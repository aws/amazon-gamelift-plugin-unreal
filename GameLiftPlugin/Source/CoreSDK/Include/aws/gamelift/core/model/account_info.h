// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <string>
#include <regex>

// GameLift
#include <aws/gamelift/core/model/resource_environment.h>
#include <aws/gamelift/core/utils/encoding_utils.h>


namespace GameLift
{
    // Marshallable struct to be used with P/Invoke
    struct AccountInfo
    {
        const char* environment;
        const char* accountId;
        const char* companyName;
        const char* gameName;
    };

    struct AccountInfoCopy
    {
        ResourceEnvironment environment;
        std::string accountId;
        std::string companyName;
        std::string gameName;
    };

    inline std::string TruncateAtLower(std::string str, const std::regex& pattern)
    {
        auto rbegin = std::sregex_iterator(str.begin(), str.end(), pattern);
        auto rend = std::sregex_iterator();
        std::string matchStr;
        for (std::sregex_iterator i = rbegin; i != rend; ++i)
        {
            std::smatch match = *i;
            matchStr = match.str();
        }

        std::transform(matchStr.begin(), matchStr.end(), matchStr.begin(), 
                    [](unsigned char c){ return std::tolower(c); }
                );
        return matchStr;
    }

    inline AccountInfoCopy CreateAccountInfoCopy(const AccountInfo& accountInfo)
    {
        AccountInfoCopy acctCopy{
            ResourceEnvironment(accountInfo.environment),
            accountInfo.accountId,
            accountInfo.companyName,
            accountInfo.gameName
        };

        // using the regex pattern for each field, truncate and convert them to lowercase
        acctCopy.accountId = TruncateAtLower(acctCopy.accountId, std::regex("\\d{12}"));
        acctCopy.gameName = TruncateAtLower(acctCopy.gameName, std::regex("[a-zA-Z0-9]{1,12}"));
        acctCopy.companyName = TruncateAtLower(acctCopy.companyName, std::regex("[a-zA-Z0-9]{3,12}"));

        return acctCopy;
    }

    // Method to compose bootstrap bucket name
    inline std::string GetBootstrapBucketName(const AccountInfoCopy& accountInfo, const std::string& shortRegionCode)
    {
        std::string bootstrapBucketName = "do-not-delete-gamelift-";

        // Bootstrap bucket names have a maximum 63 characters and has the format:
        // do-not-delete-gamelift-<env>-<5_letter_aws_region_code>-<base36_account_id>-<gamename>
        bootstrapBucketName.append(accountInfo.environment.GetEnvironmentString())
            .append("-")
            .append(shortRegionCode)
            .append("-")
            .append(GameLift::Utils::EncodingUtils::DecimalToBase(accountInfo.accountId, GameLift::Utils::BASE_36));

        return bootstrapBucketName;
    }
}
