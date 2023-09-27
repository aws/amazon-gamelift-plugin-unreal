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
 * WebSocketDescribePlayerSessionsRequest Request. This request is sent to the GameLift WebSocket
 * during a DescribePlayerSessions call
 */
class WebSocketDescribePlayerSessionsRequest : public Message {
public:
    WebSocketDescribePlayerSessionsRequest() : m_limit(-1) { SetAction(ACTION); };
    WebSocketDescribePlayerSessionsRequest(const WebSocketDescribePlayerSessionsRequest &) = default;
    WebSocketDescribePlayerSessionsRequest(WebSocketDescribePlayerSessionsRequest &&) = default;
    WebSocketDescribePlayerSessionsRequest &operator=(const WebSocketDescribePlayerSessionsRequest &) = default;
    WebSocketDescribePlayerSessionsRequest &operator=(WebSocketDescribePlayerSessionsRequest &&) = default;
    ~WebSocketDescribePlayerSessionsRequest() = default;

    inline const std::string &GetGameSessionId() const { return m_gameSessionId; }

    inline const std::string &GetPlayerId() const { return m_playerId; }

    inline const std::string &GetPlayerSessionId() const { return m_playerSessionId; }

    inline const std::string &GetPlayerSessionStatusFilter() const { return m_playerSessionStatusFilter; }

    inline const std::string &GetNextToken() const { return m_nextToken; }

    inline int GetLimit() const { return m_limit; }

    inline void SetGameSessionId(const std::string &gameSessionId) { m_gameSessionId = gameSessionId; }

    inline void SetPlayerId(const std::string &playerId) { m_playerId = playerId; }

    inline void SetPlayerSessionId(const std::string &playerSessionId) { m_playerSessionId = playerSessionId; }

    inline void SetPlayerSessionStatusFilter(const std::string &playerSessionStatusFilter) { m_playerSessionStatusFilter = playerSessionStatusFilter; }

    inline void SetNextToken(const std::string &nextToken) { m_nextToken = nextToken; }

    inline void SetLimit(const int limit) { m_limit = limit; }

    inline WebSocketDescribePlayerSessionsRequest &WithGameSessionId(const std::string &gameSessionId) {
        SetGameSessionId(gameSessionId);
        return *this;
    }

    inline WebSocketDescribePlayerSessionsRequest &WithPlayerId(const std::string &playerId) {
        SetPlayerId(playerId);
        return *this;
    }

    inline WebSocketDescribePlayerSessionsRequest &WithPlayerSessionId(const std::string &playerSessionId) {
        SetPlayerSessionId(playerSessionId);
        return *this;
    }

    inline WebSocketDescribePlayerSessionsRequest &WithPlayerSessionStatusFilter(const std::string &playerSessionStatusFilter) {
        SetPlayerSessionStatusFilter(playerSessionStatusFilter);
        return *this;
    }

    inline WebSocketDescribePlayerSessionsRequest &WithNextToken(const std::string &nextToken) {
        SetNextToken(nextToken);
        return *this;
    }

    inline WebSocketDescribePlayerSessionsRequest &WithLimit(const int limit) {
        SetLimit(limit);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const WebSocketDescribePlayerSessionsRequest &describePlayerSessionsRequest);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const override;
    bool Deserialize(const rapidjson::Value &value) override;

private:
    static constexpr const char *ACTION = "DescribePlayerSessions";

    static constexpr const char *GAME_SESSION_ID = "GameSessionId";
    static constexpr const char *PLAYER_ID = "PlayerId";
    static constexpr const char *PLAYER_SESSION_ID = "PlayerSessionId";
    static constexpr const char *PLAYER_SESSION_STATUS_FILTER = "PlayerSessionStatusFilter";
    static constexpr const char *NEXT_TOKEN = "NextToken";
    static constexpr const char *LIMIT = "Limit";

    std::string m_gameSessionId;
    std::string m_playerId;
    std::string m_playerSessionId;
    std::string m_playerSessionStatusFilter;
    std::string m_nextToken;
    int m_limit;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws