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

#include <utility>

namespace Aws {
namespace GameLift {
namespace Internal {
class RemovePlayerSessionRequest : public Message {
public:
    RemovePlayerSessionRequest() { SetAction(ACTION); }
    RemovePlayerSessionRequest(std::string gameSessionId, std::string playerSessionId)
        : m_gameSessionId(std::move(gameSessionId)), m_playerSessionId(std::move(playerSessionId)) {
        SetAction(ACTION);
    }

    RemovePlayerSessionRequest(const RemovePlayerSessionRequest &) = default;
    RemovePlayerSessionRequest(RemovePlayerSessionRequest &&) = default;
    RemovePlayerSessionRequest &operator=(const RemovePlayerSessionRequest &) = default;
    RemovePlayerSessionRequest &operator=(RemovePlayerSessionRequest &&) = default;
    ~RemovePlayerSessionRequest() = default;

    inline const std::string &GetGameSessionId() const { return m_gameSessionId; }

    inline const std::string &GetPlayerSessionId() const { return m_playerSessionId; }

    inline void SetGameSessionId(const std::string &gameSessionId) { m_gameSessionId = gameSessionId; }

    inline void SetPlayerSessionId(const std::string &playerSessionId) { m_playerSessionId = playerSessionId; }

    inline RemovePlayerSessionRequest &WithGameSessionId(const std::string &gameSessionId) {
        SetGameSessionId(gameSessionId);
        return *this;
    }

    inline RemovePlayerSessionRequest &WithPlayerSessionId(const std::string &playerSessionId) {
        SetPlayerSessionId(playerSessionId);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const RemovePlayerSessionRequest &request);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    bool Deserialize(const rapidjson::Value &value);

private:
    static constexpr const char *ACTION = "RemovePlayerSession";
    static constexpr const char *GAME_SESSION_ID = "GameSessionId";
    static constexpr const char *PLAYER_SESSION_ID = "PlayerSessionId";

    std::string m_gameSessionId;
    std::string m_playerSessionId;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws