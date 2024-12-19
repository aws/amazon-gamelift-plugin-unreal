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
#include <aws/gamelift/internal/model/WebSocketPlayer.h>
#include <string>
#include <vector>

namespace Aws {
namespace GameLift {
namespace Internal {
/**
 * WebSocketStartMatchBackfillRequest request. This request is sent to the GameLift WebSocket during
 * a DescribePlayerSessions call
 */
class WebSocketStartMatchBackfillRequest : public Message {
public:
    WebSocketStartMatchBackfillRequest();
    WebSocketStartMatchBackfillRequest(const WebSocketStartMatchBackfillRequest &) = default;
    WebSocketStartMatchBackfillRequest(WebSocketStartMatchBackfillRequest &&) = default;
    WebSocketStartMatchBackfillRequest &operator=(const WebSocketStartMatchBackfillRequest &) = default;
    WebSocketStartMatchBackfillRequest &operator=(WebSocketStartMatchBackfillRequest &&) = default;
    ~WebSocketStartMatchBackfillRequest() = default;

    inline const std::string &GetTicketId() const { return m_ticketId; }

    inline void SetTicketId(const std::string &ticketId) { m_ticketId = ticketId; }

    inline WebSocketStartMatchBackfillRequest &WithTicketId(const std::string &ticketId) {
        SetTicketId(ticketId);
        return *this;
    }

    inline const std::string &GetGameSessionArn() const { return m_gameSessionArn; }

    inline void SetGameSessionArn(const std::string &gameSessionArn) { m_gameSessionArn = gameSessionArn; }

    inline WebSocketStartMatchBackfillRequest &WithGameSessionArn(const std::string &gameSessionArn) {
        SetGameSessionArn(gameSessionArn);
        return *this;
    }

    inline const std::string &GetMatchmakingConfigurationArn() const { return m_matchmakingConfigurationArn; }

    inline void SetMatchmakingConfigurationArn(const std::string &matchmakingConfigurationArn) { m_matchmakingConfigurationArn = matchmakingConfigurationArn; }

    inline WebSocketStartMatchBackfillRequest &WithMatchmakingConfigurationArn(const std::string &matchmakingConfigurationArn) {
        SetMatchmakingConfigurationArn(matchmakingConfigurationArn);
        return *this;
    }

    inline const std::vector<WebSocketPlayer> &GetPlayers() const { return m_players; }

    inline void SetPlayers(const std::vector<WebSocketPlayer> &players) { m_players = players; }

    inline WebSocketStartMatchBackfillRequest &WithPlayers(const std::vector<WebSocketPlayer> &players) {
        SetPlayers(players);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const WebSocketStartMatchBackfillRequest &describePlayerSessionsRequest);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const override;
    bool Deserialize(const rapidjson::Value &value) override;

private:
    static constexpr const char *ACTION = "StartMatchBackfill";

    static constexpr const char *TICKET_ID = "TicketId";
    static constexpr const char *GAME_SESSION_ARN = "GameSessionArn";
    static constexpr const char *MATCHMAKING_CONFIGURATION_ARN = "MatchmakingConfigurationArn";
    static constexpr const char *PLAYERS = "Players";

    std::string m_ticketId;
    std::string m_gameSessionArn;
    std::string m_matchmakingConfigurationArn;
    std::vector<WebSocketPlayer> m_players;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws