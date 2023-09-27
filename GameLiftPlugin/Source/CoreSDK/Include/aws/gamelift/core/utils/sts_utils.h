// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// AWS SDK
#include <aws/sts/model/GetAccessKeyInfoRequest.h>
#include <aws/sts/model/GetCallerIdentityRequest.h>

// GameLift
#include <aws/gamelift/core/api.h>
#include <aws/gamelift/core/awsclients/api_initializer.h>
#include <aws/gamelift/core/awsclients/default_clients.h>
#include <aws/gamelift/core/logging.h>

namespace GameLift
{
    namespace Utils
    {
        class GAMELIFT_API STSUtils
        {
        private:
            bool m_deleteClients;
            Aws::STS::STSClient* m_stsClient;
            FuncLogCallback m_logCb;

        public:
            STSUtils(const std::string& profileName, FuncLogCallback logCallback);
            STSUtils(const std::string& accessKey, const std::string& secretKey, FuncLogCallback logCallback);
            virtual ~STSUtils();
            void SetSTSClient(Aws::STS::STSClient* stsClient);

            std::string GetAwsAccountId() const;
            bool TryGetAssumeRoleCredentials(const std::string& roleArn, const std::string& roleSessionName, const std::string& sesionPolicy, Aws::STS::Model::Credentials& sessionCredentials) const;
        };
    }
}
