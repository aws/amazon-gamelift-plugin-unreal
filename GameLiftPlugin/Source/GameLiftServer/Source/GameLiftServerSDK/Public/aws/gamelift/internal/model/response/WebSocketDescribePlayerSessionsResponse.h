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
 * WebSocketDescribePlayerSessionsRequest Response. This response is sent to the GameLift WebSocket
 * during a DescribePlayerSessions call
 */
class WebSocketDescribePlayerSessionsResponse : public Message {
public:
    WebSocketDescribePlayerSessionsResponse() { SetAction(ACTION); };
    WebSocketDescribePlayerSessionsResponse(const WebSocketDescribePlayerSessionsResponse &) = default;
    WebSocketDescribePlayerSessionsResponse(WebSocketDescribePlayerSessionsResponse &&) = default;
    WebSocketDescribePlayerSessionsResponse &operator=(const WebSocketDescribePlayerSessionsResponse &) = default;
    WebSocketDescribePlayerSessionsResponse &operator=(WebSocketDescribePlayerSessionsResponse &&) = default;
    ~WebSocketDescribePlayerSessionsResponse() = default;

    inline const std::string &GetNextToken() const { return m_nextToken; }

    inline const std::vector<WebSocketPlayerSession> &GetPlayerSessions() const { return m_playerSessions; }

    inline void SetNextToken(const std::string &nextToken) { m_nextToken = nextToken; }

    inline void SetPlayerSessions(const std::vector<WebSocketPlayerSession> &playerSessions) { m_playerSessions = playerSessions; }

    inline WebSocketDescribePlayerSessionsResponse &WithNextToken(const std::string &nextToken) {
        SetNextToken(nextToken);
        return *this;
    }

    inline WebSocketDescribePlayerSessionsResponse &WithPlayerSessions(const std::vector<WebSocketPlayerSession> &playerSessions) {
        SetPlayerSessions(playerSessions);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const WebSocketDescribePlayerSessionsResponse &describePlayerSessionsResponse);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const override;
    bool Deserialize(const rapidjson::Value &value) override;

private:
    static constexpr const char *ACTION = "DescribePlayerSessions";

    static constexpr const char *PLAYER_SESSIONS = "PlayerSessions";
    static constexpr const char *NEXT_TOKEN = "NextToken";

    std::vector<WebSocketPlayerSession> m_playerSessions;
    std::string m_nextToken;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws