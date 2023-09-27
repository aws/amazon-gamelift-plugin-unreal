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
 * Message from GameLift indicating the SDK should refresh its websocket connection.
 */
class RefreshConnectionMessage : public Message {
public:
    RefreshConnectionMessage() { SetAction(REFRESH_CONNECTION); };
    RefreshConnectionMessage(const RefreshConnectionMessage &) = default;
    RefreshConnectionMessage(RefreshConnectionMessage &&) = default;
    RefreshConnectionMessage &operator=(const RefreshConnectionMessage &) = default;
    RefreshConnectionMessage &operator=(RefreshConnectionMessage &&) = default;
    ~RefreshConnectionMessage() = default;

    inline const std::string &GetRefreshConnectionEndpoint() const { return m_refreshConnectionEndpoint; }
    inline const std::string &GetAuthToken() const { return m_authToken; }

    inline void SetRefreshConnectionEndpoint(const std::string &refreshConnectionEndpoint) { m_refreshConnectionEndpoint = refreshConnectionEndpoint; }
    inline void SetAuthToken(const std::string &authToken) { m_authToken = authToken; }

    inline RefreshConnectionMessage &WithRefreshConnectionEndpoint(const std::string &refreshConnectionEndpoint) {
        SetRefreshConnectionEndpoint(refreshConnectionEndpoint);
        return *this;
    }
    inline RefreshConnectionMessage &WithAuthToken(const std::string &authToken) {
        SetAuthToken(authToken);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const RefreshConnectionMessage &refreshConnectionMessage);

protected:
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    virtual bool Deserialize(const rapidjson::Value &obj);

private:
    static constexpr const char *REFRESH_CONNECTION = "RefreshConnection";
    static constexpr const char *REFRESH_CONNECTION_ENDPOINT = "RefreshConnectionEndpoint";
    static constexpr const char *AUTH_TOKEN = "AuthToken";

    std::string m_refreshConnectionEndpoint;
    std::string m_authToken;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws