// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <string>

namespace GameLift
{
    struct CredentialProfile
    {
        const char* name;
    };

    // Marshalable struct to be used with P/Invoke
    struct AccountCredentials
    {
        const char* region;
        const char* accessKey;
        const char* accessSecret;
        const char* accessToken;
        const char* accountId;
    };

    struct AccountCredentialsCopy
    {
        std::string region;
        std::string accessKey;
        std::string accessSecret;
        std::string accessToken;
        std::string shortRegionCode;
        std::string accountId;
    };

    inline AccountCredentialsCopy CreateAccountCredentialsCopy(const AccountCredentials& credentials)
    {
        return AccountCredentialsCopy{ credentials.region, credentials.accessKey, credentials.accessSecret, (credentials.accessToken == nullptr) ? "" : credentials.accessToken };
    }

    inline AccountCredentialsCopy CreateAccountCredentialsCopy(const AccountCredentials& credentials, const std::string& shortRegionCode)
    {
        return AccountCredentialsCopy{ credentials.region, credentials.accessKey, credentials.accessSecret, (credentials.accessToken == nullptr) ? "" : credentials.accessToken, shortRegionCode };
    }
}
