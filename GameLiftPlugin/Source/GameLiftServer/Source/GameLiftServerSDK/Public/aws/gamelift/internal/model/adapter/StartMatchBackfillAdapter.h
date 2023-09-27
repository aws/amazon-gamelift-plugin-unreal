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

#include <aws/gamelift/internal/model/request/WebSocketStartMatchBackfillRequest.h>
#include <aws/gamelift/internal/model/response/WebSocketStartMatchBackfillResponse.h>
#include <aws/gamelift/server/model/AttributeValue.h>
#include <aws/gamelift/server/model/Player.h>
#include <aws/gamelift/server/model/StartMatchBackfillRequest.h>
#include <aws/gamelift/server/model/StartMatchBackfillResult.h>
#include <cstring>

namespace Aws {
namespace GameLift {
namespace Internal {
class StartMatchBackfillAdapter {
public:
    static Server::Model::StartMatchBackfillResult convert(const WebSocketStartMatchBackfillResponse *webSocketResponse);
    static WebSocketStartMatchBackfillRequest convert(const Server::Model::StartMatchBackfillRequest &request);
    static std::map<std::string, int> fetchAndConvertLatency(const Server::Model::Player &player);
    static std::map<std::string, WebSocketAttributeValue> fetchAndConvertAttributes(const Server::Model::Player &player);
    static std::vector<std::string> convertStringList(const Server::Model::AttributeValue &attributeValue);
    static std::map<std::string, double> convertStringDoubleMap(const Server::Model::AttributeValue &attributeValue);
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws