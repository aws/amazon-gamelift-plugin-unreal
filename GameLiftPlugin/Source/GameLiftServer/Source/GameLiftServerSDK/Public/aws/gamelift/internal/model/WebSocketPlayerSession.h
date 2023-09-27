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

#include <aws/gamelift/internal/model/WebSocketPlayerSessionStatus.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <string>

namespace Aws {
namespace GameLift {
namespace Internal {

class WebSocketPlayerSession {
public:
    WebSocketPlayerSession() : m_creationTime(-1), m_terminationTime(-1), m_status(), m_port(-1) {}

    ~WebSocketPlayerSession() = default;
    WebSocketPlayerSession(const WebSocketPlayerSession &other) = default;
    WebSocketPlayerSession(WebSocketPlayerSession &&other) { *this = std::move(other); }

    WebSocketPlayerSession &operator=(const WebSocketPlayerSession &other) = default;
    WebSocketPlayerSession &operator=(WebSocketPlayerSession &&other) noexcept {
        m_playerSessionId = std::move(other.m_playerSessionId);
        m_playerId = std::move(other.m_playerId);
        m_gameSessionId = std::move(other.m_gameSessionId);
        m_fleetId = std::move(other.m_fleetId);
        m_creationTime = other.m_creationTime;
        m_terminationTime = other.m_terminationTime;
        m_status = other.m_status;
        m_ipAddress = std::move(other.m_ipAddress);
        m_port = other.m_port;
        m_playerData = std::move(other.m_playerData);
        m_dnsName = std::move(other.m_dnsName);

        return *this;
    }

    inline const std::string &GetPlayerSessionId() const { return m_playerSessionId; }

    inline void SetPlayerSessionId(const std::string &playerSessionId) { m_playerSessionId = playerSessionId; }

    inline WebSocketPlayerSession &WithPlayerSessionId(const std::string &playerSessionId) {
        SetPlayerSessionId(playerSessionId);
        return *this;
    }

    inline const std::string &GetPlayerId() const { return m_playerId; }

    inline void SetPlayerId(const std::string &playerId) { m_playerId = playerId; }

    inline WebSocketPlayerSession &WithPlayerId(const std::string &playerId) {
        SetPlayerId(playerId);
        return *this;
    }

    inline const std::string &GetGameSessionId() const { return m_gameSessionId; }

    inline void SetGameSessionId(const std::string &gameSessionId) { m_gameSessionId = gameSessionId; }

    inline WebSocketPlayerSession &WithGameSessionId(const std::string &gameSessionId) {
        SetGameSessionId(gameSessionId);
        return *this;
    }

    inline const std::string &GetFleetId() const { return m_fleetId; }

    inline void SetFleetId(const std::string &fleetId) { m_fleetId = fleetId; }

    inline WebSocketPlayerSession &WithFleetId(const std::string &fleetId) {
        SetFleetId(fleetId);
        return *this;
    }

    inline long GetCreationTime() const { return m_creationTime; }

    inline void SetCreationTime(const long creationTime) { m_creationTime = creationTime; }

    inline WebSocketPlayerSession &WithCreationTime(const long creationTime) {
        SetCreationTime(creationTime);
        return *this;
    }

    inline long GetTerminationTime() const { return m_terminationTime; }

    inline void SetTerminationTime(const long terminationTime) { m_terminationTime = terminationTime; }

    inline WebSocketPlayerSession &WithTerminationTime(const long terminationTime) {
        SetTerminationTime(terminationTime);
        return *this;
    }

    inline WebSocketPlayerSessionStatus GetStatus() const { return m_status; }

    inline void SetStatus(const WebSocketPlayerSessionStatus status) { m_status = status; }

    inline WebSocketPlayerSession &WithStatus(const WebSocketPlayerSessionStatus status) {
        SetStatus(status);
        return *this;
    }

    inline const std::string &GetIpAddress() const { return m_ipAddress; }

    inline void SetIpAddress(const std::string &ipAddress) { m_ipAddress = ipAddress; }

    inline WebSocketPlayerSession &WithIpAddress(const std::string &ipAddress) {
        SetIpAddress(ipAddress);
        return *this;
    }

    inline int GetPort() const { return m_port; }

    inline void SetPort(const int port) { m_port = port; }

    inline WebSocketPlayerSession &WithPort(const int port) {
        SetPort(port);
        return *this;
    }

    inline const std::string &GetPlayerData() const { return m_playerData; }

    inline void SetPlayerData(const std::string &playerData) { m_playerData = playerData; }

    inline WebSocketPlayerSession &WithPlayerData(const std::string &playerData) {
        SetPlayerData(playerData);
        return *this;
    }

    inline const std::string &GetDnsName() const { return m_dnsName; }

    inline void SetDnsName(const std::string &dnsName) { m_dnsName = dnsName; }

    inline WebSocketPlayerSession &WithDnsName(const std::string &dnsName) {
        SetDnsName(dnsName);
        return *this;
    }

    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    bool Deserialize(const rapidjson::Value &value);

private:
    static constexpr const char *PLAYER_SESSION_ID = "PlayerSessionId";
    static constexpr const char *PLAYER_ID = "PlayerId";
    static constexpr const char *GAME_SESSION_ID = "GameSessionId";
    static constexpr const char *FLEET_ID = "FleetId";
    static constexpr const char *CREATION_TIME = "CreationTime";
    static constexpr const char *TERMINATION_TIME = "TerminationTime";
    static constexpr const char *STATUS = "Status";
    static constexpr const char *IP_ADDRESS = "IpAddress";
    static constexpr const char *PORT = "Port";
    static constexpr const char *PLAYER_DATA = "PlayerData";
    static constexpr const char *DNS_NAME = "DnsName";

    std::string m_playerSessionId;
    std::string m_playerId;
    std::string m_gameSessionId;
    std::string m_fleetId;
    long m_creationTime;
    long m_terminationTime;
    WebSocketPlayerSessionStatus m_status;
    std::string m_ipAddress;
    int m_port;
    std::string m_playerData;
    std::string m_dnsName;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws