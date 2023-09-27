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
 * Message from GameLift/Customer reporting process health.
 */
class HeartbeatServerProcessRequest : public Message {
public:
    HeartbeatServerProcessRequest() : m_healthy(true) { SetAction(HEARTBEAT_SERVER_PROCESS); };
    HeartbeatServerProcessRequest(const HeartbeatServerProcessRequest &) = default;
    HeartbeatServerProcessRequest(HeartbeatServerProcessRequest &&) = default;
    HeartbeatServerProcessRequest &operator=(const HeartbeatServerProcessRequest &) = default;
    HeartbeatServerProcessRequest &operator=(HeartbeatServerProcessRequest &&) = default;
    ~HeartbeatServerProcessRequest() = default;

    inline const bool GetHealthy() const { return m_healthy; }

    inline void SetHealthy(const bool healthy) { m_healthy = healthy; }

    inline HeartbeatServerProcessRequest &WithHealthy(const bool healthy) {
        SetHealthy(healthy);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const HeartbeatServerProcessRequest &HeartbeatServerProcessRequest);

protected:
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    virtual bool Deserialize(const rapidjson::Value &obj);

private:
    static constexpr const char *HEARTBEAT_SERVER_PROCESS = "HeartbeatServerProcess";
    static constexpr const char *HEALTH_STATUS = "HealthStatus";

    bool m_healthy;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
