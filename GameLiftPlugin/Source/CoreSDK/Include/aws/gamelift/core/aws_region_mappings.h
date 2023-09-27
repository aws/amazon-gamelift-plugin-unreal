#pragma once

// Standard Lib
#include <string>
#include <unordered_map>

// GameLift
#include <aws/gamelift/core/api.h>
#include <aws/gamelift/core/logging.h>

// yaml-cpp
#include <yaml-cpp/yaml.h>

using namespace GameLift::Logger;

namespace GameLift
{
    static const std::string GAMELIFT_AWS_REGION_MAPPINGS_FILE_NAME = "awsGameLiftAwsRegionMappings.yml";
    static const std::string GAMELIFT_FIVE_LETTER_REGION_CODES_PREFIX = "five_letter_region_codes";

    class GAMELIFT_API AwsRegionMappings
    {
    private:
        std::string m_pluginRootPath;
        YAML::Node m_regionShortCodes;
        FuncLogCallback m_logCb;

        // Make the constructors and destructor private to prevent duplicate instances
        AwsRegionMappings() {};
        AwsRegionMappings(const std::string& pluginRootPath, FuncLogCallback logCallback);
        ~AwsRegionMappings();
        
        std::string GetRegionMappingsFilePath() const;

    public:
        // Delete constructors and operator overloading that should not be used
        AwsRegionMappings(const AwsRegionMappings&) = delete;
        const AwsRegionMappings& operator=(const AwsRegionMappings&) = delete;

        static AwsRegionMappings& getInstance(const std::string& pluginRootPath, FuncLogCallback logCallback);

        /**
        * @brief Get the 5-letter region code for AWS region.
        *
        * @details Converts an input AWS region code to it's 5-letter short code based on mapping in GAMELIFT_AWS_REGION_MAPPINGS_FILE_NAME in gamelift root directory.
        *
        * @param fullRegionCode Input aws region code.
        * @returns 5-letter short region code based on mapping in GAMELIFT_AWS_REGION_MAPPINGS_FILE_NAME in plugin, empty string if error or doesn't exist in map.
        */
        std::string getFiveLetterRegionCode(const std::string& fullRegionCode) const;
    };
}