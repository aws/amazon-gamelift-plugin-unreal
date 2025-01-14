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

#include <aws/gamelift/internal/model/Message.h>
#include <aws/gamelift/internal/model/Uri.h>
#include <aws/gamelift/internal/network/IWebSocketClientWrapper.h>
#include <future>
#include <mutex>

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * Class Managing a single WebSocketClientWrapper, enabling connection and communication with
 * GameLift
 */
class GameLiftWebSocketClientManager {
public:
    GameLiftWebSocketClientManager(std::shared_ptr<IWebSocketClientWrapper> webSocketClientWrapper) : m_webSocketClientWrapper(webSocketClientWrapper) {}

    ~GameLiftWebSocketClientManager() = default;

    inline bool IsConnected() { return m_webSocketClientWrapper->IsConnected(); }

    Aws::GameLift::GenericOutcome Connect(std::string websocketUrl, const std::string &authToken, const std::string &processId, const std::string &hostId,
                                          const std::string &fleetId, const std::map<std::string, std::string> &sigV4QueryParameters = {});
    // Messages are synchronously sent and a response is waited for.
    GenericOutcome SendSocketMessage(Message &message);
    void Disconnect();

private:
    static bool EndsWith(const std::string &actualString, const std::string &ending);

    static constexpr const char *PID_KEY = "pID";
    static constexpr const char *SDK_VERSION_KEY = "sdkVersion";
    static constexpr const char *FLAVOR_KEY = "sdkLanguage";
    static constexpr const char *AUTH_TOKEN_KEY = "Authorization";
    static constexpr const char *COMPUTE_ID_KEY = "ComputeId";
    static constexpr const char *FLEET_ID_KEY = "FleetId";

    static constexpr const char *REQUIRED_URL_ENDING = "/";

    // The WebSocketClient that this class is managing.
    std::shared_ptr<IWebSocketClientWrapper> m_webSocketClientWrapper;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws
