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
#include <aws/gamelift/internal/security/ContainerTaskMetadata.h>
#include <aws/gamelift/common/Outcome.h>

namespace Aws {
namespace GameLift {
namespace Internal {

class ContainerMetadataFetcher {
private:
    const std::string EnvironmentVariableContainerMetadataUri = "ECS_CONTAINER_METADATA_URI_V4";
    const std::string TaskMetadataRelativePath = "task";

    HttpClient &httpClient;

public:
    ContainerMetadataFetcher(HttpClient &httpClient);

    Aws::GameLift::Outcome<ContainerTaskMetadata, std::string> FetchContainerTaskMetadata();
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws

