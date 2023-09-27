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
class WebSocketGetFleetRoleCredentialsRequest : public Message {
public:
    WebSocketGetFleetRoleCredentialsRequest() { SetAction(ACTION); };

    WebSocketGetFleetRoleCredentialsRequest(const WebSocketGetFleetRoleCredentialsRequest &) = default;

    WebSocketGetFleetRoleCredentialsRequest(WebSocketGetFleetRoleCredentialsRequest &&) = default;

    WebSocketGetFleetRoleCredentialsRequest &operator=(const WebSocketGetFleetRoleCredentialsRequest &) = default;

    WebSocketGetFleetRoleCredentialsRequest &operator=(WebSocketGetFleetRoleCredentialsRequest &&) = default;

    ~WebSocketGetFleetRoleCredentialsRequest() = default;

    inline const std::string &GetRoleArn() const { return m_roleArn; }

    inline void SetRoleArn(const std::string &value) { m_roleArn = value; }

    inline WebSocketGetFleetRoleCredentialsRequest &WithRoleArn(const std::string &value) {
        SetRoleArn(value);
        return *this;
    }

    inline const std::string &GetRoleSessionName() const { return m_roleSessionName; }

    inline void SetRoleSessionName(const std::string &value) { m_roleSessionName = value; }

    inline WebSocketGetFleetRoleCredentialsRequest &WithRoleSessionName(const std::string &value) {
        SetRoleSessionName(value);
        return *this;
    }

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const override;

    bool Deserialize(const rapidjson::Value &value) override;

private:
    static constexpr const char *ACTION = "GetFleetRoleCredentials";

    static constexpr const char *ROLE_ARN = "RoleArn";
    static constexpr const char *ROLE_SESSION_NAME = "RoleSessionName";

    std::string m_roleArn;
    std::string m_roleSessionName;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws