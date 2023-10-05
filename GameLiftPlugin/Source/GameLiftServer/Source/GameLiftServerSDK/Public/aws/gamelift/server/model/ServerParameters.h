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

#if defined(_MSC_VER) && !defined(GAMELIFT_USE_STD)
#pragma warning(push)           // Save warning settings.
#pragma warning(disable : 4996) // Disable deprecated warning for strncpy
#endif

#include <aws/gamelift/common/GameLift_EXPORTS.h>

#ifndef GAMELIFT_USE_STD
#ifndef MAX_WEBSOCKET_URL_LENGTH
#define MAX_WEBSOCKET_URL_LENGTH 1024
#endif
#ifndef MAX_FLEET_ID_LENGTH
#define MAX_FLEET_ID_LENGTH 1024
#endif
#ifndef MAX_HOST_ID_LENGTH
#define MAX_HOST_ID_LENGTH 1024
#endif
#ifndef MAX_PROCESS_ID_LENGTH
#define MAX_PROCESS_ID_LENGTH 1024
#endif
#ifndef MAX_AUTH_TOKEN_LENGTH
#define MAX_AUTH_TOKEN_LENGTH 1024
#endif
#endif

namespace Aws {
namespace GameLift {
namespace Server {
namespace Model {

class AWS_GAMELIFT_API ServerParameters {
#ifdef GAMELIFT_USE_STD
public:
    ServerParameters() = default;
    ServerParameters(const ServerParameters &) = default;
    ServerParameters(ServerParameters &&) = default;
    ServerParameters &operator=(const ServerParameters &) = default;
    ServerParameters &operator=(ServerParameters &&) = default;

    ServerParameters(const std::string &websocketUrl, const std::string &authToken, const std::string &fleetId, const std::string &hostId,
                     const std::string &processId)
        : m_webSocketUrl(websocketUrl), m_authToken(authToken), m_fleetId(fleetId), m_hostId(hostId), m_processId(processId) {}

    inline const std::string &GetWebSocketUrl() const { return m_webSocketUrl; }

    inline const std::string &GetAuthToken() const { return m_authToken; }

    inline const std::string &GetFleetId() const { return m_fleetId; }

    inline const std::string &GetProcessId() const { return m_processId; }

    inline const std::string &GetHostId() const { return m_hostId; }

    inline void SetWebSocketUrl(const std::string &webSocketUrl) { m_webSocketUrl = webSocketUrl; }

    inline void SetAuthToken(const std::string &authToken) { m_authToken = authToken; }

    inline void SetFleetId(const std::string &fleetId) { m_fleetId = fleetId; }

    inline void SetProcessId(const std::string &processId) { m_processId = processId; }

    inline void SetHostId(const std::string &hostId) { m_hostId = hostId; }

    inline void SetWebSocketUrl(const char *webSocketUrl) { m_webSocketUrl.assign(webSocketUrl); }

    inline void SetAuthToken(const char *authToken) { m_authToken.assign(authToken); }

    inline void SetFleetId(const char *fleetId) { m_fleetId.assign(fleetId); }

    inline void SetProcessId(const char *processId) { m_processId.assign(processId); }

    inline void SetHostId(const char *hostId) { m_hostId.assign(hostId); }

    inline ServerParameters &WithWebSocketUrl(const std::string &webSocketUrl) {
        SetWebSocketUrl(webSocketUrl);
        return *this;
    }

    inline ServerParameters &WithAuthToken(const std::string &authToken) {
        SetAuthToken(authToken);
        return *this;
    }

    inline ServerParameters &WithFleetId(const std::string &fleetId) {
        SetFleetId(fleetId);
        return *this;
    }

    inline ServerParameters &WithProcessId(const std::string &processId) {
        SetProcessId(processId);
        return *this;
    }

    inline ServerParameters &WithHostId(const std::string &hostId) {
        SetHostId(hostId);
        return *this;
    }

    inline ServerParameters &WithWebSocketUrl(const char *webSocketUrl) {
        SetWebSocketUrl(webSocketUrl);
        return *this;
    }

    inline ServerParameters &WithAuthToken(const char *authToken) {
        SetAuthToken(authToken);
        return *this;
    }

    inline ServerParameters &WithFleetId(const char *fleetId) {
        SetFleetId(fleetId);
        return *this;
    }

    inline ServerParameters &WithProcessId(const char *processId) {
        SetProcessId(processId);
        return *this;
    }

    inline ServerParameters &WithHostId(const char *hostId) {
        SetHostId(hostId);
        return *this;
    }

private:
    std::string m_webSocketUrl;
    std::string m_fleetId;
    std::string m_processId;
    std::string m_hostId;
    std::string m_authToken;
#else
public:
    ServerParameters() {
        memset(m_webSocketUrl, 0, sizeof(m_webSocketUrl));
        memset(m_authToken, 0, sizeof(m_authToken));
        memset(m_processId, 0, sizeof(m_processId));
        memset(m_hostId, 0, sizeof(m_hostId));
        memset(m_fleetId, 0, sizeof(m_fleetId));
    }

    ServerParameters(const char *webSocketUrl, const char *authToken, const char *fleetId, const char *hostId, const char *processId) {
        strncpy(m_webSocketUrl, webSocketUrl, sizeof(m_webSocketUrl));
        m_webSocketUrl[sizeof(m_webSocketUrl) - 1] = '\0';
        strncpy(m_authToken, authToken, sizeof(m_authToken));
        m_authToken[sizeof(m_authToken) - 1] = '\0';
        strncpy(m_fleetId, fleetId, sizeof(m_fleetId));
        m_fleetId[sizeof(m_fleetId) - 1] = '\0';
        strncpy(m_processId, processId, sizeof(m_processId));
        m_processId[sizeof(m_processId) - 1] = '\0';
        strncpy(m_hostId, hostId, sizeof(m_hostId));
        m_hostId[sizeof(m_hostId) - 1] = '\0';
    }

    ServerParameters(const ServerParameters &) = default;
    ServerParameters(ServerParameters &&) = default;
    ServerParameters &operator=(const ServerParameters &) = default;
    ServerParameters &operator=(ServerParameters &&) = default;

    inline const char *GetWebSocketUrl() const { return m_webSocketUrl; }

    inline const char *GetAuthToken() const { return m_authToken; }

    inline const char *GetFleetId() const { return m_fleetId; }

    inline const char *GetProcessId() const { return m_processId; }

    inline const char *GetHostId() const { return m_hostId; }

    inline void SetWebSocketUrl(const char *webSocketUrl) {
        strncpy(m_webSocketUrl, webSocketUrl, sizeof(m_webSocketUrl));
        m_webSocketUrl[sizeof(m_webSocketUrl) - 1] = '\0';
    }

    inline void SetAuthToken(const char *authToken) {
        strncpy(m_authToken, authToken, sizeof(m_authToken));
        m_authToken[sizeof(m_authToken) - 1] = '\0';
    }

    inline void SetFleetId(const char *fleetId) {
        strncpy(m_fleetId, fleetId, sizeof(m_fleetId));
        m_fleetId[sizeof(m_fleetId) - 1] = '\0';
    }

    inline void SetProcessId(const char *processId) {
        strncpy(m_processId, processId, sizeof(m_processId));
        m_processId[sizeof(m_processId) - 1] = '\0';
    }

    inline void SetHostId(const char *hostId) {
        strncpy(m_hostId, hostId, sizeof(m_hostId));
        m_hostId[sizeof(m_hostId) - 1] = '\0';
    }

    inline ServerParameters &WithWebSocketUrl(const char *webSocketUrl) {
        SetWebSocketUrl(webSocketUrl);
        return *this;
    }

    inline ServerParameters &WithAuthToken(const char *authToken) {
        SetAuthToken(authToken);
        return *this;
    }

    inline ServerParameters &WithFleetId(const char *fleetId) {
        SetFleetId(fleetId);
        return *this;
    }

    inline ServerParameters &WithProcessId(const char *processId) {
        SetProcessId(processId);
        return *this;
    }

    inline ServerParameters &WithHostId(const char *hostId) {
        SetHostId(hostId);
        return *this;
    }

private:
    char m_webSocketUrl[MAX_WEBSOCKET_URL_LENGTH];
    char m_fleetId[MAX_FLEET_ID_LENGTH];
    char m_processId[MAX_PROCESS_ID_LENGTH];
    char m_hostId[MAX_HOST_ID_LENGTH];
    char m_authToken[MAX_AUTH_TOKEN_LENGTH];
#endif
};

} // namespace Model
} // namespace Server
} // namespace GameLift
} // namespace Aws

#if defined(_MSC_VER) && !defined(GAMELIFT_USE_STD)
#pragma warning(pop) // Restore warnings to previous state.
#endif