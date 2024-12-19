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
#include <iostream>

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * Message from GameLift/Customer reporting process health.
 */
class WebSocketStopMatchBackfillRequest : public Message {
public:
    WebSocketStopMatchBackfillRequest() { SetAction(STOP_MATCH_BACKFILL); };
    WebSocketStopMatchBackfillRequest(const WebSocketStopMatchBackfillRequest &) = default;
    WebSocketStopMatchBackfillRequest(WebSocketStopMatchBackfillRequest &&) = default;
    WebSocketStopMatchBackfillRequest &operator=(const WebSocketStopMatchBackfillRequest &) = default;
    WebSocketStopMatchBackfillRequest &operator=(WebSocketStopMatchBackfillRequest &&) = default;
    ~WebSocketStopMatchBackfillRequest() = default;

    inline const std::string &GetGameSessionArn() const { return m_gameSessionArn; }
    inline const std::string &GetMatchmakingConfigurationArn() const { return m_matchmakingConfigurationArn; }
    inline const std::string &GetTicketId() const { return m_ticketId; }

    inline void SetGameSessionArn(const std::string &gameSessionArn) { m_gameSessionArn = gameSessionArn; }
    inline void SetMatchmakingConfigurationArn(const std::string &matchmakingConfigurationArn) { m_matchmakingConfigurationArn = matchmakingConfigurationArn; }
    inline void SetTicketId(const std::string &ticketId) { m_ticketId = ticketId; }

    inline WebSocketStopMatchBackfillRequest &WithMatchmakingConfigurationArn(const std::string &matchmakingConfigurationArn) {
        SetMatchmakingConfigurationArn(matchmakingConfigurationArn);
        return *this;
    }
    inline WebSocketStopMatchBackfillRequest &WithGameSessionArn(const std::string &gameSessionArn) {
        SetGameSessionArn(gameSessionArn);
        return *this;
    }
    inline WebSocketStopMatchBackfillRequest &WithTicketId(const std::string &ticketId) {
        SetTicketId(ticketId);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const WebSocketStopMatchBackfillRequest &stopMatchBackfillMessage);

protected:
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    virtual bool Deserialize(const rapidjson::Value &obj);

private:
    static constexpr const char *STOP_MATCH_BACKFILL = "StopMatchBackfill";
    static constexpr const char *GAME_SESSION_ARN = "GameSessionArn";
    static constexpr const char *MATCHMAKING_CONFIG_ARN = "MatchmakingConfigurationArn";
    static constexpr const char *TICKET_ID = "TicketId";

    std::string m_gameSessionArn;
    std::string m_matchmakingConfigurationArn;
    std::string m_ticketId;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
