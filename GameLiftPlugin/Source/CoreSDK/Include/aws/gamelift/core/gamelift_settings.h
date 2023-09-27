// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Lib
#include <fstream>
#include <iostream>
#include <map>
#include <string>

// GameLift
#include <aws/gamelift/core/api.h>
#include <aws/gamelift/core/model/account_info.h>
#include <aws/gamelift/core/model/config_consts.h>
#include <aws/gamelift/core/errors.h>
#include <aws/gamelift/core/logging.h>

// yaml-cpp
#include <yaml-cpp/yaml.h>

namespace GameLift
{
    static const std::string GAMELIFT_SETTINGS_FILE = "saveInfo.yml";
    static const std::string GAMELIFT_SETTINGS_VERSION_KEY = "gameliftPluginVersion";
    static const std::string GAMELIFT_SETTINGS_GAME_KEY = "game";
    static const std::string GAMELIFT_SETTINGS_GAME_NAME = "name";
    static const std::string GAMELIFT_SETTINGS_SHORT_GAME_NAME = "short_name";
    static const std::string GAMELIFT_SETTINGS_LAST_USED_REGION = "lastUsedRegion";
    static const std::string GAMELIFT_SETTINGS_LAST_USED_ENVIRONMENT = "lastUsedEnvironment";
    static const std::string GAMELIFT_SETTINGS_LAST_USED_ENVIRONMENT_CODE = "code";
    static const std::string GAMELIFT_SETTINGS_ENVIRONMENTS_KEY = "customEnvironments";
    static const std::string GAMELIFT_SETTINGS_ENVIRONMENT_DESCRIPTION = "description";
    static const std::string GAMELIFT_SETTINGS_FEATURES_KEY = "features";
    static const std::string GAMELIFT_SETTINGS_FEATURE_ACTIVE = "active";
    static const std::string GAMELIFT_SETTINGS_FEATURE_VARS = "vars";

    /**
     * GameLiftSettings offers read/write access to the "saveInfo.yml" GAMELIFT Settings file.
     *
     * The settings file contains information such as:
     * - Game name
     * - Custom deployment environments (ex: "Gamma")
     * - List of activated/deactivated features
     * - Feature-specific variables (ex: "isFacebookLoginEnabled" for Identity)
     *
     * The file is stored at "GAMELIFT_ROOT/shortGameName/saveInfo.yml".
     *
     * The file is read/written through usage of the plugin UI. For example, when a feature is activated,
     * when feature variables are filled in, or when a custom deployment environment is added or removed.
     *
     * The file is loaded during the constructor, and can be reloaded by calling Reload().
     * Call SaveSettings() to write the settings to back to disk after making modifications with any "Set", "Add/Delete", "Activate/Deactivate" methods.
     */
    class GAMELIFT_API GameLiftSettings
    {
    private:
        std::string m_gameliftPluginVersion;
        std::string m_gameliftRootPath;
        std::string m_shortGameName;
        std::string m_currentEnvironment;
        YAML::Node m_gameliftYamlSettings;
        FuncLogCallback m_logCb;
    public:
        GameLiftSettings(const std::string& gameliftRoot, const std::string& pluginVersion, const std::string& shortGameName, const std::string& currentEnvironment, FuncLogCallback logCallback);
        ~GameLiftSettings();
        void SetGameName(const std::string& gameName);
        void SetLastUsedRegion(const std::string& region);
        void SetLastUsedEnvironment(const std::string& gameName);
        void AddCustomEnvironment(const std::string& envCode, const std::string& envDescription);
        void DeleteCustomEnvironment(const std::string& envCode);
        void ActivateFeature(FeatureType featureType);
        void DeactivateFeature(FeatureType featureType);
        void SetFeatureVariables(FeatureType featureType, const std::map<std::string, std::string>& vars);
        void DeleteFeatureVariable(FeatureType featureType, std::string varName);
        unsigned int SaveSettings();
        std::string GetGameName() const;
        std::string GetLastUsedRegion() const;
        std::string GetLastUsedEnvironment() const;
        std::map<std::string, std::string> GetCustomEnvironments() const;
        std::string GetCustomEnvironmentDescription(std::string envCode) const;
        bool IsFeatureActive(FeatureType featureType) const;
        std::map<std::string, std::string> GetFeatureVariables(FeatureType featureType) const;
        std::string GetFeatureVariable(FeatureType featureType, std::string varName) const;
        std::string GetSettingsFilePath() const;
        void Reload();
    };
}
