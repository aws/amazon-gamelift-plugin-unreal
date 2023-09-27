// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

/** @file
 * @brief aws-gamelift-core enums.
 */

#pragma once
namespace GameLift
{
    enum class TokenType { AccessToken = 0, RefreshToken, IdToken, IamSessionToken, TokenType_COUNT /* TokenType_COUNT must be the last item in this enum */ };
    enum class FeatureType { Main, Identity, Authentication, Achievements, GameStateCloudSaving, UserGameplayData };
    enum class TemplateType { Base, Instance };
    enum class EnvironmentType { Development = 0, QA = 1, Staging = 2, Production = 3, Custom = 4 };
    enum class FederatedIdentityProvider { Facebook = 0, Google = 1, Apple = 2, Amazon = 3 };

    inline std::string GetFeatureTypeString(FeatureType feature)
    {
        switch (feature)
        {
        case FeatureType::Main: return "main";
        case FeatureType::Identity: return "identity";
        case FeatureType::Authentication: return "authentication";
        case FeatureType::Achievements: return "achievements";
        case FeatureType::GameStateCloudSaving: return "gamesaving";
        case FeatureType::UserGameplayData: return "usergamedata";
        default: return "main";
        }
    }

    inline FeatureType GetFeatureTypeFromString(const std::string& feature)
    {
        if (feature == "identity") return FeatureType::Identity;
        if (feature == "authentication") return FeatureType::Authentication;
        if (feature == "achievements") return FeatureType::Achievements;
        if (feature == "gamesaving") return FeatureType::GameStateCloudSaving;
        if (feature == "usergamedata") return FeatureType::UserGameplayData;

        return FeatureType::Main;
    }
}
