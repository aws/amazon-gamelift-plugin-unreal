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

namespace Aws {
namespace GameLift {
namespace Internal {
class WebSocketGetFleetRoleCredentialsResponse : public Message {
public:
    WebSocketGetFleetRoleCredentialsResponse() : m_expiration(-1) { SetAction(ACTION); };

    WebSocketGetFleetRoleCredentialsResponse(const WebSocketGetFleetRoleCredentialsResponse &) = default;

    WebSocketGetFleetRoleCredentialsResponse(WebSocketGetFleetRoleCredentialsResponse &&) = default;

    WebSocketGetFleetRoleCredentialsResponse &operator=(const WebSocketGetFleetRoleCredentialsResponse &) = default;

    WebSocketGetFleetRoleCredentialsResponse &operator=(WebSocketGetFleetRoleCredentialsResponse &&) = default;

    ~WebSocketGetFleetRoleCredentialsResponse() = default;

    inline const std::string &GetAssumedRoleUserArn() const { return m_assumedRoleUserArn; }

    inline void SetAssumedRoleUserArn(const std::string &assumedRoleUserArn) { m_assumedRoleUserArn = assumedRoleUserArn; }

    inline WebSocketGetFleetRoleCredentialsResponse &WithAssumedRoleUserArn(const std::string &assumedRoleUserArn) {
        SetAssumedRoleUserArn(assumedRoleUserArn);
        return *this;
    }

    inline const std::string &GetAssumedRoleId() const { return m_assumedRoleId; }

    inline void SetAssumedRoleId(const std::string &assumedRoleId) { m_assumedRoleId = assumedRoleId; }

    inline WebSocketGetFleetRoleCredentialsResponse &WithAssumedRoleId(const std::string &assumedRoleId) {
        SetAssumedRoleId(assumedRoleId);
        return *this;
    }

    inline const std::string &GetAccessKeyId() const { return m_accessKeyId; }

    inline void SetAccessKeyId(const std::string &accessKeyId) { m_accessKeyId = accessKeyId; }

    inline WebSocketGetFleetRoleCredentialsResponse &WithAccessKeyId(const std::string &accessKeyId) {
        SetAccessKeyId(accessKeyId);
        return *this;
    }

    inline const std::string &GetSecretAccessKey() const { return m_secretAccessKey; }

    inline void SetSecretAccessKey(const std::string &secretAccessKey) { m_secretAccessKey = secretAccessKey; }

    inline WebSocketGetFleetRoleCredentialsResponse &WithSecretAccessKey(const std::string &secretAccessKey) {
        SetSecretAccessKey(secretAccessKey);
        return *this;
    }

    inline const std::string &GetSessionToken() const { return m_sessionToken; }

    inline void SetSessionToken(const std::string &sessionToken) { m_sessionToken = sessionToken; }

    inline WebSocketGetFleetRoleCredentialsResponse &WithSessionToken(const std::string &sessionToken) {
        SetSessionToken(sessionToken);
        return *this;
    }

    inline int64_t GetExpiration() const { return m_expiration; }

    inline void SetExpiration(int64_t expiration) { m_expiration = expiration; }

    inline WebSocketGetFleetRoleCredentialsResponse &WithExpiration(int64_t expiration) {
        SetExpiration(expiration);
        return *this;
    }

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const override;

    bool Deserialize(const rapidjson::Value &value) override;

private:
    static constexpr const char *ACTION = "GetFleetRoleCredentials";

    static constexpr const char *ASSUMED_ROLE_USER_ARN = "AssumedRoleUserArn";
    static constexpr const char *ASSUMED_ROLE_ID = "AssumedRoleId";
    static constexpr const char *ACCESS_KEY_ID = "AccessKeyId";
    static constexpr const char *SECRET_ACCESS_KEY = "SecretAccessKey";
    static constexpr const char *SESSION_TOKEN = "SessionToken";
    static constexpr const char *EXPIRATION = "Expiration";

    std::string m_assumedRoleUserArn;
    std::string m_assumedRoleId;
    std::string m_accessKeyId;
    std::string m_secretAccessKey;
    std::string m_sessionToken;
    int64_t m_expiration;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws