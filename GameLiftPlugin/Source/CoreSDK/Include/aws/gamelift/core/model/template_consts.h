// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once
#include <string>

namespace GameLift
{
    // Template system variables. These variables are replaced when instance templates are saved.
    namespace TemplateVars
    {
        static const std::string BEGIN = "\\{\\{";
        static const std::string END = "\\}\\}";
        static const std::string AWS_GAMELIFT_ENVIRONMENT = "AWSGAMELIFT::SYS::ENV";
        static const std::string AWS_GAMELIFT_GAMENAME = "AWSGAMELIFT::SYS::GAMENAME";
        static const std::string AWS_GAMELIFT_USERVAR_PREFIX = "AWSGAMELIFT::VARS::";
        static const std::string AWS_GAMELIFT_CLOUDFORMATION_OUTPUT_PREFIX = "AWSGAMELIFT::CFNOUTPUT::";
        static const std::string AWS_GAMELIFT_BASE36_AWS_ACCOUNTID = "AWSGAMELIFT::SYS::BASE36AWSACCOUNTID";
        static const std::string AWS_GAMELIFT_SHORT_REGION_CODE = "AWSGAMELIFT::SYS::SHORTREGIONCODE";
    }

    namespace ResourceDirectories
    {
        static const std::string CLOUDFORMATION_DIRECTORY = "/cloudformation/";
        static const std::string LAYERS_DIRECTORY = "/layers/";
        static const std::string FUNCTIONS_DIRECTORY = "/functions/";
        static const std::string CONFIG_OUTPUTS_DIRECTORY = "/configOutputs/";
    }

    namespace TemplateFileNames
    {
        static const std::string FEATURE_DASHBOARD_FILE = "dashboard.yml";
        static const std::string CLOUDFORMATION_FILE = "cloudFormation.yml";
        static const std::string PARAMETERS_FILE = "parameters.yml";
        static const std::string FEATURE_CLIENT_CONFIGURATION_FILE = "clientConfig.yml";
        static const std::string GAMELIFT_CLIENT_CONFIGURATION_FILE = "awsGameLiftClientConfig.yml";
    }
}
