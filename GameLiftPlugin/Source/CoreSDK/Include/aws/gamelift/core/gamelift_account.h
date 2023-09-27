// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// AWS SDK
#include <aws/apigateway/model/CreateDeploymentRequest.h>
#include <aws/apigateway/model/Op.h>
#include <aws/apigateway/model/PatchOperation.h>
#include <aws/apigateway/model/UpdateResourceRequest.h>
#include <aws/apigateway/model/UpdateResourceResult.h>
#include <aws/apigateway/model/UpdateStageRequest.h>
#include <aws/cloudformation/model/DescribeStackResourceRequest.h>
#include <aws/gamelift/GameLiftClient.h>
#include <aws/s3/model/Bucket.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/PutBucketLifecycleConfigurationRequest.h>
#include <aws/secretsmanager/model/CreateSecretRequest.h>
#include <aws/secretsmanager/model/DescribeSecretRequest.h>
#include <aws/secretsmanager/model/UpdateSecretRequest.h>
#include <aws/secretsmanager/model/DeleteSecretRequest.h>
#include <aws/ssm/model/PutParameterRequest.h>

// GameLift
#include <aws/gamelift/core/awsclients/api_initializer.h>
#include <aws/gamelift/core/errors.h>
#include <aws/gamelift/core/feature_resources.h>
#include <aws/gamelift/core/logging.h>
#include <aws/gamelift/core/awsclients/default_clients.h>
#include <aws/gamelift/core/model/account_credentials.h>
#include <aws/gamelift/core/model/account_info.h>
#include <aws/gamelift/core/model/template_consts.h>
#include <aws/gamelift/core/aws_region_mappings.h>

namespace GameLift
{
    /**
     * GameLiftAccount offers plugin-level, AWS account-level, and cross-feature methods.
     *
     * The feature-related methods operate on ALL features at the same time.
     * To work on a single feature, use GameLiftFeatureResources instead.
     *
     * For example, GameLiftAccount can:
     * - Get path to the plugin's installation directory.
     * - Get path to the base resources and instance resources.
     * - Create instance resource files.
     * - Create the bootstrap S3 bucket.
     * - Deploy the main stack and all feature stacks.
     * - Deploy the shared API Gateway stage.
     * - Save secrets to AWS Secrets Manager.
     */
    class GAMELIFT_API GameLiftAccount
    {
    private:
        AccountInfoCopy m_accountInfo;
        AccountCredentialsCopy m_credentials;
        FuncLogCallback m_logCb;
        bool m_deleteClients = false;

        Aws::S3::S3Client* m_s3Client;
        Aws::SSM::SSMClient* m_ssmClient;
        Aws::CloudFormation::CloudFormationClient* m_cfnClient;
        Aws::SecretsManager::SecretsManagerClient* m_secretsClient;
        Aws::APIGateway::APIGatewayClient* m_apigwyClient;
        Aws::Lambda::LambdaClient* m_lambdaClient;
        Aws::GameLift::GameLiftClient* m_gameLiftClient; // note: This is the client used to call AWS SDK GameLift APIs, not the client used for the game client build.

        std::string m_pluginRoot;
        std::string m_gameliftRoot;
        std::string m_baseLayersPath;
        std::string m_baseFunctionsPath;
        std::string m_baseCloudformationPath;
        std::string m_instanceLayersPath;
        std::string m_instanceFunctionsPath;
        std::string m_instanceCloudformationPath;
        std::string m_instanceGameServerPath;

        std::string composeSecretId(const std::string& secretName);
        bool hasBootstrapBucket(const std::string& bootstrapBucketName);
        bool isLayersPathValid(TemplateType templateType);
        bool isFunctionsPathValid(TemplateType templateType);
        bool isCloudFormationPathValid(TemplateType templateType);
        unsigned int createSecret(const std::string& secretId, const std::string& secretValue);
        unsigned int updateSecret(const std::string& secretId, const std::string& secretValue);
        unsigned int deleteSecret(const std::string& secretId);
        std::string getShortRegionCode();

    public:
        GameLiftAccount(AccountInfo accountInfo, CredentialProfile profile, FuncLogCallback logCallback);
        GameLiftAccount(AccountInfo accountInfo, AccountCredentials credentials, FuncLogCallback logCallback);
        virtual ~GameLiftAccount();

        bool HasBootstrapBucket();

        using BootstrapResult = std::pair<unsigned int, std::string>;
        BootstrapResult Bootstrap();

        void DeleteClients();

        // Returns Account Info
        AccountInfoCopy GetAccountInfo()
        {
            return m_accountInfo;
        }

        // Returns Account Credentials
        AccountCredentialsCopy GetAccountCredentials()
        {
            return m_credentials;
        }

        inline void DeleteClientsOnDestruction(bool cleanup = true)
        {
            m_deleteClients = cleanup;
        }

        // Returns the AWS account id
        inline const std::string& GetAwsAccountId()
        {
            return m_accountInfo.accountId;
        }

        inline const std::string& GetGameName()
        {
            return m_accountInfo.gameName;
        }

        inline void SetGameName(const std::string& gameName)
        {
            m_accountInfo.gameName = gameName;
        }

        // Sets the root directory of the plugin's installation
        inline void SetPluginRoot(const std::string& pluginRoot)
        {
            m_pluginRoot = pluginRoot;
            m_baseLayersPath = pluginRoot + ResourceDirectories::LAYERS_DIRECTORY;
            m_baseFunctionsPath = pluginRoot + ResourceDirectories::FUNCTIONS_DIRECTORY;
            m_baseCloudformationPath = pluginRoot + ResourceDirectories::CLOUDFORMATION_DIRECTORY;
        }

        // Returns the root directory of the plugin's installation
        inline const std::string& GetPluginRoot()
        {
            return m_pluginRoot;
        }

        // The value GAMELIFT_ROOT where instance templates and settings are going to be stored
        inline void SetGameLiftRoot(const std::string& gameliftRoot)
        {
            m_gameliftRoot = gameliftRoot;
            m_instanceLayersPath = gameliftRoot + "/" + m_accountInfo.gameName + "/" + m_accountInfo.environment.GetEnvironmentString() + ResourceDirectories::LAYERS_DIRECTORY;
            m_instanceFunctionsPath = gameliftRoot + "/" + m_accountInfo.gameName + "/" + m_accountInfo.environment.GetEnvironmentString() + ResourceDirectories::FUNCTIONS_DIRECTORY;
            m_instanceCloudformationPath = gameliftRoot + "/" + m_accountInfo.gameName + "/" + m_accountInfo.environment.GetEnvironmentString() + ResourceDirectories::CLOUDFORMATION_DIRECTORY;
        }

        // Returns the GAMELIFT_ROOT where instance templates and settings are stored
        inline const std::string& GetGameLiftRoot()
        {
            return m_gameliftRoot;
        }

        // Returns the base Lambda Layers path
        inline const std::string& GetBaseLayersPath()
        {
            return m_baseLayersPath;
        }

        // Returns the base Lambda Functions path
        inline const std::string& GetBaseFunctionsPath()
        {
            return m_baseFunctionsPath;
        }

        // Returns the base CloudFormation path
        inline const std::string& GetBaseCloudFormationPath()
        {
            return m_baseCloudformationPath;
        }

        // Returns the instance Lambda Functions path
        inline const std::string& GetInstanceFunctionsPath()
        {
            return m_instanceFunctionsPath;
        }

        // Returns the instance CloudFormation path
        inline const std::string& GetInstanceCloudFormationPath()
        {
            return m_instanceCloudformationPath;
        }

        unsigned int CheckSecretExists(const std::string& secretName);
        unsigned int SaveSecret(const std::string& secretName, const std::string& secretValue);
        unsigned int DeleteSecret(const std::string& secretName);
        unsigned int SaveFeatureInstanceTemplates(const Aws::Map<std::string, std::string>& vars);
        unsigned int UploadDashboards();
        unsigned int UploadLayers();
        unsigned int UploadFunctions();
        unsigned int UploadGameServer(const std::string& path, const std::string& addPath, std::string& s3Path);
        bool HasValidCredentials();
        unsigned int CreateOrUpdateStacks();
        unsigned int CreateOrUpdateMainStack();
        unsigned int CreateOrUpdateFeatureStacks();
        unsigned int CreateAndSetFunctionsReplacementId();

        using FuncReplacementIdResult = std::pair<unsigned int, std::string>;
        FuncReplacementIdResult GetMainFunctionsReplacementId();

        unsigned int DeployApiGatewayStage();

        // Creates an instance of GameLiftFeatureResources based on account information
        // Up to caller to destroy the instance
        GameLift::GameLiftFeatureResources* CreateGameLiftResourcesInstance();

        // Initializes the AWS Clients internally.
        // Clients initialized witht his method will be deleted on ~GameLiftAccount().
        void InitializeDefaultAwsClients();

        // Sets the S3Client explicitly.
        // It's the caller responsibility to call delete on the instance passed to this method.
        inline void SetS3Client(Aws::S3::S3Client* s3Client)
        {
            m_s3Client = s3Client;
        }

        // Sets the SSMClient explicitly.
        // It's the caller responsibility to call delete on the instance passed to this method.
        inline void SetSSMClient(Aws::SSM::SSMClient* ssmClient)
        {
            m_ssmClient = ssmClient;
        }

        // Sets the CloudFormationClient explicitly.
        // It's the caller responsibility to call delete on the instance passed to this method.
        inline void SetCloudFormationClient(Aws::CloudFormation::CloudFormationClient* cfnClient)
        {
            m_cfnClient = cfnClient;
        }

        // Sets the SecretsManagerClient explicitly.
        // It's the caller responsibility to call delete on the instance passed to this method.
        inline void SetSecretsManagerClient(Aws::SecretsManager::SecretsManagerClient* secretsClient)
        {
            m_secretsClient = secretsClient;
        }

        // Sets the ApiGatewayClient explicitly.
        // It's the caller responsibility to call delete on the instance passed to this method.
        inline void SetApiGatewayClient(Aws::APIGateway::APIGatewayClient* apigwyClient)
        {
            m_apigwyClient = apigwyClient;
        }

        // Sets the LambdaClient explicitly.
        // It's the caller responsibility to call delete on the instance passed to this method.
        inline void SetLambdaClient(Aws::Lambda::LambdaClient* lambdaClient)
        {
            m_lambdaClient = lambdaClient;
        }

        // Sets the GameLiftClient explicitly.
        // It's the caller responsibility to call delete on the instance passed to this method.
        inline void SetGameLiftClient(Aws::GameLift::GameLiftClient* gameLiftClient)
        {
            m_gameLiftClient = gameLiftClient;
        }

        // Gets the GameLiftClient.
        inline const Aws::GameLift::GameLiftClient* GetGameLiftClient() const
        {
            return m_gameLiftClient;
        }
    };
}
