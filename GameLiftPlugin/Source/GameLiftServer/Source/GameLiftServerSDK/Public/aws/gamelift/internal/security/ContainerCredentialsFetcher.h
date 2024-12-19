/*
 * All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
 * its licensors.
 *
 * For complete copyright and license terms please see the LICENSE at the root of this
 * distribution (the "License"). All use of this software is governed by the License,
 * or, if provided, by the license below or the license accompanying this file. Do not
 * remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *
 */
#pragma once

#include <string>
#include <aws/gamelift/internal/util/HttpClient.h>
#include <aws/gamelift/internal/security/AwsCredentials.h>
#include <aws/gamelift/common/Outcome.h>

namespace Aws {
namespace GameLift {
namespace Internal {

class ContainerCredentialsFetcher {
private:
    const std::string ContainerCredentialProviderUrl = "http://169.254.170.2";
    const std::string EnvironmentVariableContainerCredentialsRelativeUri = "AWS_CONTAINER_CREDENTIALS_RELATIVE_URI";

    HttpClient &httpClient;

public:
    ContainerCredentialsFetcher(HttpClient &httpClient);

    Aws::GameLift::Outcome<AwsCredentials, std::string> FetchContainerCredentials();
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws

