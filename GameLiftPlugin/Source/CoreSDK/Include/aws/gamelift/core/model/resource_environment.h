// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <string>
#include <regex>

// GameLift
#include <aws/gamelift/core/enums.h>

namespace GameLift
{
    struct ResourceEnvironment
    {
    private:
        EnvironmentType environmentType;
        std::string environmentCode;
    public:
        ResourceEnvironment() {
            environmentType = EnvironmentType::Development;
        }

        // Do not use EnvironmentType::Custom in this constructor.
        // It will be defaulted to EnvironmentType::Development if you do.
        inline ResourceEnvironment(EnvironmentType env)
        {
            this->environmentType = env;
            switch (env)
            {
            case EnvironmentType::Development: this->environmentCode = "dev";
            case EnvironmentType::QA: this->environmentCode = "qa";
            case EnvironmentType::Staging: this->environmentCode = "stg";
            case EnvironmentType::Production: this->environmentCode = "prd";
            default:
                this->environmentType = EnvironmentType::Development;
                this->environmentCode = "dev";
            }
        }

        inline ResourceEnvironment(const std::string& envCode)
        {
            if (!std::regex_match(envCode, std::regex("[a-z0-9]{2,3}")))
            {
                throw "Invalid environment code. Environment codes are all lowercase alphanumeric characters with a maximum length of 3.";
            }

            this->environmentCode = envCode;
            if (envCode == "dev")
            {
                this->environmentType = EnvironmentType::Development;
            }
            else if (envCode == "qa")
            {
                this->environmentType = EnvironmentType::QA;
            }
            else if (envCode == "stg")
            {
                this->environmentType = EnvironmentType::Staging;
            }
            else if (envCode == "prod")
            {
                this->environmentType = EnvironmentType::Production;
            }
            else
            {
                this->environmentType = EnvironmentType::Custom;
            }
        }

        inline EnvironmentType GetEnvironmentType()
        {
            return this->environmentType;
        }

        inline std::string GetEnvironmentString() const
        {
            return this->environmentCode;
        }
    };
}
