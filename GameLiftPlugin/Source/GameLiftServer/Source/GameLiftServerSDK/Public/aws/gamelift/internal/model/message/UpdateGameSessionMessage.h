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
#include <aws/gamelift/internal/model/WebSocketGameSession.h>

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * Message from GameLift initializing GameSession Creation
 */
class UpdateGameSessionMessage : public Message {
public:
    UpdateGameSessionMessage() { SetAction(UPDATE_GAME_SESSION); };
    UpdateGameSessionMessage(const UpdateGameSessionMessage &) = default;
    UpdateGameSessionMessage(UpdateGameSessionMessage &&) = default;
    UpdateGameSessionMessage &operator=(const UpdateGameSessionMessage &) = default;
    UpdateGameSessionMessage &operator=(UpdateGameSessionMessage &&) = default;
    ~UpdateGameSessionMessage() = default;

    inline const WebSocketGameSession &GetGameSession() const { return m_gameSession; }

    inline const std::string &GetUpdateReason() const { return m_updateReason; }

    inline const std::string &GetBackfillTicketId() const { return m_backfillTicketId; }

    inline void SetGameSession(WebSocketGameSession &gameSession) { m_gameSession = gameSession; }

    inline void SetUpdateReason(const std::string &updateReason) { m_updateReason = updateReason; }

    inline void SetBackfillTicketId(const std::string &backfillTicketId) { m_backfillTicketId = backfillTicketId; }

    inline UpdateGameSessionMessage &WithGameSession(WebSocketGameSession &gameSession) {
        SetGameSession(gameSession);
        return *this;
    }

    inline UpdateGameSessionMessage &WithUpdateReason(const std::string &updateReason) {
        SetUpdateReason(updateReason);
        return *this;
    }

    inline UpdateGameSessionMessage &WithBackfillTicketId(const std::string &backfillTicketId) {
        SetBackfillTicketId(backfillTicketId);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const UpdateGameSessionMessage &createGameSessionMessage);

protected:
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    virtual bool Deserialize(const rapidjson::Value &obj);

private:
    static constexpr const char *UPDATE_GAME_SESSION = "UpdateGameSession";
    static constexpr const char *GAME_SESSION = "GameSession";
    static constexpr const char *UPDATE_REASON = "UpdateReason";
    static constexpr const char *BACKFILL_TICKET_ID = "BackfillTicketId";

    WebSocketGameSession m_gameSession;
    std::string m_updateReason;
    std::string m_backfillTicketId;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
