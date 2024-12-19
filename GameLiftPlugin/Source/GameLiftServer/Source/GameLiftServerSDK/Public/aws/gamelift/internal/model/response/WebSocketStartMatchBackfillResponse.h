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
#include <aws/gamelift/internal/model/WebSocketPlayerSession.h>
#include <vector>

namespace Aws {
namespace GameLift {
namespace Internal {
/**
 * WebSocketStartMatchBackfillRequest Response. This response is sent to the GameLift WebSocket
 * during a DescribePlayerSessions call
 */
class WebSocketStartMatchBackfillResponse : public Message {
public:
    WebSocketStartMatchBackfillResponse() { SetAction(ACTION); };
    WebSocketStartMatchBackfillResponse(const WebSocketStartMatchBackfillResponse &) = default;
    WebSocketStartMatchBackfillResponse(WebSocketStartMatchBackfillResponse &&) = default;
    WebSocketStartMatchBackfillResponse &operator=(const WebSocketStartMatchBackfillResponse &) = default;
    WebSocketStartMatchBackfillResponse &operator=(WebSocketStartMatchBackfillResponse &&) = default;
    ~WebSocketStartMatchBackfillResponse() = default;

    inline const std::string &GetTicketId() const { return m_ticketId; }

    inline void SetTicketId(const std::string &ticketId) { m_ticketId = ticketId; }

    inline WebSocketStartMatchBackfillResponse &WithTicketId(const std::string &ticketId) {
        SetTicketId(ticketId);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const WebSocketStartMatchBackfillResponse &describePlayerSessionsResponse);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const override;
    bool Deserialize(const rapidjson::Value &value) override;

private:
    static constexpr const char *ACTION = "StartMatchBackfill";

    static constexpr const char *TICKET_ID = "TicketId";

    std::string m_ticketId;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws