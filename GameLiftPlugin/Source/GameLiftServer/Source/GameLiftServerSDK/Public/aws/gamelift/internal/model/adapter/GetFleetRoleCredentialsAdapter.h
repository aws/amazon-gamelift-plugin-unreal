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

#include <aws/gamelift/internal/model/request/WebSocketGetFleetRoleCredentialsRequest.h>
#include <aws/gamelift/internal/model/response/WebSocketGetFleetRoleCredentialsResponse.h>
#include <aws/gamelift/server/model/GetFleetRoleCredentialsRequest.h>
#include <aws/gamelift/server/model/GetFleetRoleCredentialsResult.h>
namespace Aws {
namespace GameLift {
namespace Internal {
class GetFleetRoleCredentialsAdapter {
public:
    static Server::Model::GetFleetRoleCredentialsResult convert(const WebSocketGetFleetRoleCredentialsResponse *webSocketResponse);

    static WebSocketGetFleetRoleCredentialsRequest convert(const Server::Model::GetFleetRoleCredentialsRequest &request);
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws