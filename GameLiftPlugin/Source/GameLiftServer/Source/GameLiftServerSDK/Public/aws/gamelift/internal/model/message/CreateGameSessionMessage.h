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
#include <map>
#include <string>

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * Message from GameLift initializing GameSession Creation
 */
class CreateGameSessionMessage : public Message {
public:
    CreateGameSessionMessage() : m_maximumPlayerSessionCount(-1), m_port(-1) { SetAction(CREATE_GAME_SESSION); };
    CreateGameSessionMessage(const CreateGameSessionMessage &) = default;
    CreateGameSessionMessage(CreateGameSessionMessage &&) = default;
    CreateGameSessionMessage &operator=(const CreateGameSessionMessage &) = default;
    CreateGameSessionMessage &operator=(CreateGameSessionMessage &&) = default;
    ~CreateGameSessionMessage() = default;

    inline const std::string &GetGameSessionId() const { return m_gameSessionId; }

    inline const std::string &GetGameSessionName() const { return m_gameSessionName; }

    inline const std::string &GetGameSessionData() const { return m_gameSessionData; }

    inline const std::string &GetMatchmakerData() const { return m_matchmakerData; }

    inline const std::string &GetIpAddress() const { return m_ipAddress; }

    inline const std::string &GetDnsName() const { return m_dnsName; }

    inline int GetMaximumPlayerSessionCount() const { return m_maximumPlayerSessionCount; }

    inline int GetPort() const { return m_port; }

    inline const std::map<std::string, std::string> &GetGameProperties() const { return m_gameProperties; }

    inline void SetGameSessionId(const std::string &gameSessionId) { m_gameSessionId = gameSessionId; }

    inline void SetGameSessionName(const std::string &gameSessionName) { m_gameSessionName = gameSessionName; }

    inline void SetGameSessionData(const std::string &gameSessionData) { m_gameSessionData = gameSessionData; }

    inline void SetMatchmakerData(const std::string &matchmakerData) { m_matchmakerData = matchmakerData; }

    inline void SetIpAddress(const std::string &ipAddress) { m_ipAddress = ipAddress; }

    inline void SetDnsName(const std::string &dnsName) { m_dnsName = dnsName; }

    inline void SetMaximumPlayerSessionCount(const int maximumPlayerSessionCount) { m_maximumPlayerSessionCount = maximumPlayerSessionCount; }

    inline void SetPort(const int port) { m_port = port; }

    inline void SetGameProperties(const std::map<std::string, std::string> &gameProperties) { m_gameProperties = gameProperties; }

    inline CreateGameSessionMessage &WithGameSessionId(const std::string &gameSessionId) {
        SetGameSessionId(gameSessionId);
        return *this;
    }

    inline CreateGameSessionMessage &WithGameSessionName(const std::string &gameSessionName) {
        SetGameSessionName(gameSessionName);
        return *this;
    }

    inline CreateGameSessionMessage &WithGameSessionData(const std::string &gameSessionData) {
        SetGameSessionData(gameSessionData);
        return *this;
    }

    inline CreateGameSessionMessage &WithMatchmakerData(const std::string &matchmakerData) {
        SetMatchmakerData(matchmakerData);
        return *this;
    }

    inline CreateGameSessionMessage &WithIpAddress(const std::string &ipAddress) {
        SetIpAddress(ipAddress);
        return *this;
    }

    inline CreateGameSessionMessage &WithDnsName(const std::string &dnsName) {
        SetDnsName(dnsName);
        return *this;
    }

    inline CreateGameSessionMessage &WithMaximumPlayerSessionCount(const int maximumPlayerSessionCount) {
        SetMaximumPlayerSessionCount(maximumPlayerSessionCount);
        return *this;
    }

    inline CreateGameSessionMessage &WithPort(const int port) {
        SetPort(port);
        return *this;
    }

    inline CreateGameSessionMessage &WithGameProperties(const std::map<std::string, std::string> &gameProperties) {
        SetGameProperties(gameProperties);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const CreateGameSessionMessage &createGameSessionMessage);

protected:
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    virtual bool Deserialize(const rapidjson::Value &obj);

private:
    static constexpr const char *CREATE_GAME_SESSION = "CreateGameSession";
    static constexpr const char *GAME_SESSION_ID = "GameSessionId";
    static constexpr const char *GAME_SESSION_NAME = "GameSessionName";
    static constexpr const char *GAME_SESSION_DATA = "GameSessionData";
    static constexpr const char *MATCHMAKER_DATA = "MatchmakerData";
    static constexpr const char *DNS_NAME = "DnsName";
    static constexpr const char *IP_ADDRESS = "IpAddress";
    static constexpr const char *MAXIMUM_PLAYER_SESSION_COUNT = "MaximumPlayerSessionCount";
    static constexpr const char *PORT = "Port";
    static constexpr const char *GAME_PROPERTIES = "GameProperties";

    std::string m_gameSessionId;
    std::string m_gameSessionName;
    std::string m_gameSessionData;
    std::string m_matchmakerData;
    std::string m_ipAddress;
    std::string m_dnsName;
    int m_maximumPlayerSessionCount;
    int m_port;
    std::map<std::string, std::string> m_gameProperties;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
