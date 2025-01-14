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

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * ActivateGameSessionRequest Request. This request is sent to the GameLift WebSocket during
 * ActivateGameSession
 */
class ActivateGameSessionRequest : public Message {
public:
    ActivateGameSessionRequest();
    ActivateGameSessionRequest(std::string gameSessionId);

    ActivateGameSessionRequest(const ActivateGameSessionRequest &) = default;
    ActivateGameSessionRequest(ActivateGameSessionRequest &&) = default;
    ActivateGameSessionRequest &operator=(const ActivateGameSessionRequest &) = default;
    ActivateGameSessionRequest &operator=(ActivateGameSessionRequest &&) = default;
    ~ActivateGameSessionRequest() = default;

    inline const std::string &GetGameSessionId() const { return m_gameSessionId; }

    inline void SetGameSessionId(const std::string &gameSessionId) { m_gameSessionId = gameSessionId; }

    inline ActivateGameSessionRequest &WithGameSessionId(const std::string &gameSessionId) {
        SetGameSessionId(gameSessionId);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const ActivateGameSessionRequest &request);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    bool Deserialize(const rapidjson::Value &value);

private:
    static constexpr const char *ACTIVATE_GAME_SESSION = "ActivateGameSession";
    static constexpr const char *GAME_SESSION_ID = "GameSessionId";

    std::string m_gameSessionId;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
