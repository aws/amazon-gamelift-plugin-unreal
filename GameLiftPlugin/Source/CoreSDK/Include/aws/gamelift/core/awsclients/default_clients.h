// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// AWS SDK
#include <aws/apigateway/APIGatewayClient.h>
#include <aws/apigateway/APIGateway_EXPORTS.h>
#include <aws/cloudformation/CloudFormationClient.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/core/auth/AWSCredentials.h>
#include <aws/gamelift/GameLiftClient.h>
#include <aws/lambda/LambdaClient.h>
#include <aws/s3/S3Client.h>
#include <aws/secretsmanager/SecretsManagerClient.h>
#include <aws/ssm/SSMClient.h>
#include <aws/sts/STSClient.h>
#include <aws/sts/model/AssumeRoleRequest.h>

// GameLift
#include <aws/gamelift/core/model/account_credentials.h>
#include <aws/gamelift/core/model/account_info.h>

namespace GameLift
{
    class DefaultClients
    {
    private:
        template <class T>
        static inline T* getDefaultClient(const AccountCredentialsCopy& credentials)
        {
            Aws::Client::ClientConfiguration clientConfig;
            Aws::Auth::AWSCredentials creds;

            clientConfig.region = credentials.region.c_str();
            creds.SetAWSAccessKeyId(credentials.accessKey.c_str());
            creds.SetAWSSecretKey(credentials.accessSecret.c_str());
            creds.SetSessionToken(credentials.accessToken.c_str());

            return new T(creds, clientConfig);
        }

        static inline Aws::S3::S3Client* getDefaultS3Client(const AccountCredentialsCopy& credentials)
        {
            Aws::Client::ClientConfiguration clientConfig;
            Aws::Auth::AWSCredentials creds;

            clientConfig.region = credentials.region.c_str();
            creds.SetAWSAccessKeyId(credentials.accessKey.c_str());
            creds.SetAWSSecretKey(credentials.accessSecret.c_str());
            creds.SetSessionToken(credentials.accessToken.c_str());

            return new Aws::S3::S3Client(
                creds,
                Aws::MakeShared<Aws::S3::S3EndpointProvider>(Aws::S3::S3Client::ALLOCATION_TAG),
                clientConfig);
        }

    public:
        static inline Aws::S3::S3Client* GetDefaultS3Client(const AccountCredentialsCopy& credentials)
        {
            return getDefaultS3Client(credentials);
        }

        static inline Aws::SSM::SSMClient* GetDefaultSSMClient(const AccountCredentialsCopy& credentials)
        {
            return getDefaultClient<Aws::SSM::SSMClient>(credentials);
        }

        static inline Aws::CloudFormation::CloudFormationClient* GetDefaultCloudFormationClient(const AccountCredentialsCopy& credentials)
        {
            return getDefaultClient<Aws::CloudFormation::CloudFormationClient>(credentials);
        }

        static inline Aws::SecretsManager::SecretsManagerClient* GetDefaultSecretsManagerClient(const AccountCredentialsCopy& credentials)
        {
            return getDefaultClient<Aws::SecretsManager::SecretsManagerClient>(credentials);
        }

        static inline Aws::CognitoIdentityProvider::CognitoIdentityProviderClient* GetDefaultCognitoIdentityProviderClient(const Aws::Client::ClientConfiguration& clientConfig)
        {
            return new Aws::CognitoIdentityProvider::CognitoIdentityProviderClient(clientConfig);
        }

        static inline Aws::APIGateway::APIGatewayClient* GetDefaultApiGatewayClient(const AccountCredentialsCopy& credentials)
        {
            return getDefaultClient<Aws::APIGateway::APIGatewayClient>(credentials);
        }

        static inline Aws::Lambda::LambdaClient* GetDefaultLambdaClient(const AccountCredentialsCopy& credentials)
        {
            return getDefaultClient<Aws::Lambda::LambdaClient>(credentials);
        }

        static inline Aws::GameLift::GameLiftClient* GetDefaultGameLiftClient(const AccountCredentialsCopy& credentials)
        {
            return getDefaultClient<Aws::GameLift::GameLiftClient>(credentials);
        }
    };
}
