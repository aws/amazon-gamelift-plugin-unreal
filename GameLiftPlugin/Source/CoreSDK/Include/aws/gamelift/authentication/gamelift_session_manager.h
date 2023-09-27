// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once
// Standard Library
#include <array>
#include <map>
#include <memory>
#include <string>

// AWS SDK
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/CognitoIdentityProviderErrors.h>
#include <aws/cognito-idp/model/InitiateAuthRequest.h>
#include <aws/cognito-idp/model/SignUpRequest.h>
#include <aws/cognito-idp/model/ConfirmSignUpRequest.h>

// GameLift
#include <aws/gamelift/core/api.h>
#include <aws/gamelift/core/awsclients/api_initializer.h>
#include <aws/gamelift/core/awsclients/default_clients.h>
#include <aws/gamelift/core/enums.h>
#include <aws/gamelift/core/logging.h>
#include <aws/gamelift/core/utils/ticker.h>

namespace GameLift
{
    namespace ClientSettings
    {
        namespace Authentication
        {
            static const std::string SETTINGS_USER_POOL_CLIENT_ID = "user_pool_client_id";
            static const std::string SETTINGS_IDENTITY_REGION = "identity_region";
            static const std::string SETTINGS_IDENTITY_API_GATEWAY_BASE_URL = "identity_api_gateway_base_url";
        }

        namespace Achievements
        {
            static const std::string SETTINGS_ACHIEVEMENTS_API_GATEWAY_BASE_URL = "achievements_api_gateway_base_url";
            static const std::string SETTINGS_ACHIEVEMENTS_ICONS_BASE_URL = "achievements_icons_base_url";
        }

        namespace UserGameplayData
        {
            static const std::string SETTINGS_USER_GAMEPLAY_DATA_API_GATEWAY_BASE_URL = "usergamedata_api_gateway_base_url";
        }

        namespace GameSaving
        {
            static const std::string SETTINGS_GAME_SAVING_BASE_URL = "gamesaving_api_gateway_base_url";
        }
    }

    namespace Authentication
    {
        static const int DEFAULT_REFRESH_SECONDS_BEFORE_EXPIRATION = 120;
        static const int MAX_REFRESH_RETRY_ATTEMPTS = 5;

        class GAMELIFT_API GameLiftSessionManager
        {
        private:
            std::mutex m_sessionTokensMutex;
            std::array<std::string, (size_t)TokenType::TokenType_COUNT> m_sessionTokens; // Indexed by TokenType enum values
            std::shared_ptr<Utils::Ticker> m_tokenRefresher;
            FuncLogCallback m_logCb = nullptr;
            std::shared_ptr<std::map<std::string, std::string>> m_clientSettings;
            Aws::CognitoIdentityProvider::CognitoIdentityProviderClient* m_cognitoClient;
            bool m_awsClientsInitializedInternally;

            void loadConfigFile(std::string clientConfigFile) const;

        protected:
            void executeTokenRefresh();

        public:
            GameLiftSessionManager(const std::string& clientConfigFile, FuncLogCallback logCallback);
            virtual ~GameLiftSessionManager();

            /**
             * @brief Initializes the AWS Clients internally.
             * Clients initialized with this method will be deleted on ~SessionManager().
            */            
            bool InitializeDefaultAwsClients();

            /**
             * @brief  
            */
            unsigned int UpdateTokensByUserPass(const std::string& user, const std::string& pass);

            /**
             * @brief
            */
            unsigned int SignUpByUserPass(const std::string& user, const std::string& pass);

            /**
             * @brief
            */
            unsigned int ConfirmSignUp(const std::string& user, const std::string& code);

            /**
             * @brief Sets a token's value.
             * @param tokenType The type of token to set.
             * @param value The value of the token.
            */
            void SetToken(TokenType tokenType, const std::string& value);

            /**
             * @brief Retrieves a token.
             * @param tokenType The type of token to retrieve.
             * @return Token string.
            */
            std::string GetToken(TokenType tokenType);

            /**
             * @brief Deletes a token.
             * @param tokenType The type of token to delete.
            */
            void DeleteToken(TokenType tokenType);

            /**
             * @brief Sets the token's session expiration.
             * @param expirationInSeconds Token duration before it expires.
            */
            void SetSessionExpiration(int expirationInSeconds);

            /**
             * @brief Checks if the settings are loaded for the feature. These settings are found in the generated awsGameLiftClientConfig.yml.
             * The setting are loaded either through the constructor of GameLiftSessionManager or by calling ReloadConfigFile().
             * @param featureType The feature to check
             * @return Returns true if the settings for the feature are loaded.
            */
            bool AreSettingsLoaded(FeatureType featureType) const;

            /**
             * @brief Get the current client settings.
             * @return A map of the current client settings.
            */
            Aws::Map<std::string, std::string> GetClientSettings() const;

            /**
             * @brief Reads and loads the configuration file into SessionManager.
             * @param clientConfigFile The awsGameLiftClientConfig.yml file to reload.
            */
            void ReloadConfigFile(std::string clientConfigFile);

            inline static std::string GetTokenTypeString(TokenType tokenType)
            {
                switch (tokenType)
                {
                case TokenType::AccessToken: return "access_token";
                case TokenType::RefreshToken: return "refresh_token";
                case TokenType::IdToken: return "id_token";
                case TokenType::IamSessionToken: return "session_token";
                default: return "";
                }
            }

            // Sets the CognitoIdentityProviderClient explicitly.
            // It's the caller responsibility to call delete on the instance passed to this method.
            inline void SetCognitoClient(Aws::CognitoIdentityProvider::CognitoIdentityProviderClient* client)
            {
                m_awsClientsInitializedInternally = false;
                m_cognitoClient = client;
            }
        };
    }
}
