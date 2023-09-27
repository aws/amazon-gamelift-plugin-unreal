/*
 * All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
 * its licensors.
 *
 * For complete copyright and license terms please see the LICENSE at the root of this
 * distribution (the "License"). All use of this software is governed by the License,
 * or, if provided, by the license below or the license accompanying this file. Do not
 * remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#pragma once

#include <aws/gamelift/internal/model/WebSocketAttributeValue.h>
#include <map>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <string>

namespace Aws {
namespace GameLift {
namespace Internal {

class WebSocketPlayer {
public:
    WebSocketPlayer(){};
    WebSocketPlayer(const WebSocketPlayer &) = default;
    WebSocketPlayer(WebSocketPlayer &&) = default;
    WebSocketPlayer &operator=(const WebSocketPlayer &) = default;
    WebSocketPlayer &operator=(WebSocketPlayer &&) = default;
    ~WebSocketPlayer() = default;

    inline const std::string &GetPlayerId() const { return m_playerId; }

    inline void SetPlayerId(const std::string &playerId) { m_playerId = playerId; }

    inline WebSocketPlayer &WithPlayerId(const std::string &playerId) {
        SetPlayerId(playerId);
        return *this;
    }

    inline const std::string &GetTeam() const { return m_team; }

    inline void SetTeam(const std::string &team) { m_team = team; }

    inline WebSocketPlayer &WithTeam(const std::string &team) {
        SetTeam(team);
        return *this;
    }

    inline const std::map<std::string, WebSocketAttributeValue> &GetPlayerAttributes() const { return m_playerAttributes; }

    inline void SetPlayerAttributes(const std::map<std::string, WebSocketAttributeValue> &playerAttributes) { m_playerAttributes = playerAttributes; }

    inline WebSocketPlayer &WithPlayerAttributes(const std::map<std::string, WebSocketAttributeValue> &playerAttributes) {
        SetPlayerAttributes(playerAttributes);
        return *this;
    }

    inline const std::map<std::string, int> &GetLatencyInMs() const { return m_latencyInMs; }

    inline void SetLatencyInMs(const std::map<std::string, int> &latencyInMs) { m_latencyInMs = latencyInMs; }

    inline WebSocketPlayer &WithLatencyInMs(const std::map<std::string, int> &latencyInMs) {
        SetLatencyInMs(latencyInMs);
        return *this;
    }

    std::string Serialize() const;
    bool Deserialize(const std::string &jsonString);
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    bool Deserialize(const rapidjson::Value &value);

private:
    static constexpr const char *PLAYER_ID = "PlayerId";
    static constexpr const char *PLAYER_ATTRIBUTES = "PlayerAttributes";
    static constexpr const char *LATENCY_IN_MS = "LatencyInMs";
    static constexpr const char *TEAM = "Team";

    std::string m_playerId;
    std::map<std::string, WebSocketAttributeValue> m_playerAttributes;
    std::map<std::string, int> m_latencyInMs;
    std::string m_team;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws