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

enum class WebSocketPlayerSessionCreationPolicy { NOT_SET, DENY_ALL, ACCEPT_ALL };

/**
 * UpdatePlayerSessionCreationPolicyRequest Request. This request is sent to the GameLift WebSocket
 * during a DescribePlayerSessions call
 */
class UpdatePlayerSessionCreationPolicyRequest : public Message {
public:
    UpdatePlayerSessionCreationPolicyRequest() { SetAction(ACTION); };

    UpdatePlayerSessionCreationPolicyRequest(std::string gameSessionId, std::string playerSessionCreationPolicy) : m_gameSessionId(std::move(gameSessionId)) {
        SetAction(ACTION);
        SetPlayerSessionCreationPolicy(playerSessionCreationPolicy);
    }

    UpdatePlayerSessionCreationPolicyRequest(const UpdatePlayerSessionCreationPolicyRequest &) = default;
    UpdatePlayerSessionCreationPolicyRequest(UpdatePlayerSessionCreationPolicyRequest &&) = default;
    UpdatePlayerSessionCreationPolicyRequest &operator=(const UpdatePlayerSessionCreationPolicyRequest &) = default;
    UpdatePlayerSessionCreationPolicyRequest &operator=(UpdatePlayerSessionCreationPolicyRequest &&) = default;
    ~UpdatePlayerSessionCreationPolicyRequest() = default;

    inline const std::string &GetGameSessionId() const { return m_gameSessionId; }

    inline void SetGameSessionId(const std::string &gameSessionId) { m_gameSessionId = gameSessionId; }

    inline UpdatePlayerSessionCreationPolicyRequest &WithGameSessionId(const std::string &gameSessionId) {
        SetGameSessionId(gameSessionId);
        return *this;
    }

    inline const WebSocketPlayerSessionCreationPolicy &GetPlayerSessionCreationPolicy() const { return m_playerSessionCreationPolicy; }

    inline const std::string GetPlayerSessionCreationPolicyAsString() const {
        switch (m_playerSessionCreationPolicy) {
        case WebSocketPlayerSessionCreationPolicy::ACCEPT_ALL:
            return std::string(ACCEPT_ALL);
        case WebSocketPlayerSessionCreationPolicy::DENY_ALL:
            return std::string(DENY_ALL);
        default:
            return std::string(NOT_SET);
        }
    }

    inline void SetPlayerSessionCreationPolicy(const WebSocketPlayerSessionCreationPolicy &playerSessionCreationPolicy) {
        m_playerSessionCreationPolicy = playerSessionCreationPolicy;
    }

    inline UpdatePlayerSessionCreationPolicyRequest &WithPlayerSessionCreationPolicy(const WebSocketPlayerSessionCreationPolicy &playerSessionCreationPolicy) {
        SetPlayerSessionCreationPolicy(playerSessionCreationPolicy);
        return *this;
    }

    inline void SetPlayerSessionCreationPolicy(const std::string &playerSessionCreationPolicy) {
        if (strcmp(playerSessionCreationPolicy.c_str(), ACCEPT_ALL) == 0) {
            m_playerSessionCreationPolicy = WebSocketPlayerSessionCreationPolicy::ACCEPT_ALL;
        } else if (strcmp(playerSessionCreationPolicy.c_str(), DENY_ALL) == 0) {
            m_playerSessionCreationPolicy = WebSocketPlayerSessionCreationPolicy::DENY_ALL;
        } else {
            m_playerSessionCreationPolicy = WebSocketPlayerSessionCreationPolicy::NOT_SET;
        }
    }

    inline UpdatePlayerSessionCreationPolicyRequest &WithPlayerSessionCreationPolicy(const std::string &playerSessionCreationPolicy) {
        SetPlayerSessionCreationPolicy(playerSessionCreationPolicy);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const UpdatePlayerSessionCreationPolicyRequest &describePlayerSessionsRequest);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const override;
    bool Deserialize(const rapidjson::Value &value) override;

private:
    static constexpr const char *ACTION = "UpdatePlayerSessionCreationPolicy";

    static constexpr const char *GAME_SESSION_ID = "GameSessionId";
    static constexpr const char *PLAYER_SESSION_POLICY = "PlayerSessionPolicy";
    static constexpr const char *ACCEPT_ALL = "ACCEPT_ALL";
    static constexpr const char *DENY_ALL = "DENY_ALL";
    static constexpr const char *NOT_SET = "NOT_SET";

    std::string m_gameSessionId;
    WebSocketPlayerSessionCreationPolicy m_playerSessionCreationPolicy = WebSocketPlayerSessionCreationPolicy::NOT_SET;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws