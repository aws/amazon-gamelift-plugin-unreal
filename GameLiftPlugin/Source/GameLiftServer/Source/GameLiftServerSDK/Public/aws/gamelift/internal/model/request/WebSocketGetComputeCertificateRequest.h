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
/**
 * WebSocketGetComputeCertificateRequest Request. This request is sent to the GameLift WebSocket
 * during a DescribePlayerSessions call
 */
class WebSocketGetComputeCertificateRequest : public Message {
public:
    WebSocketGetComputeCertificateRequest() { SetAction(ACTION); };
    WebSocketGetComputeCertificateRequest(const WebSocketGetComputeCertificateRequest &) = default;
    WebSocketGetComputeCertificateRequest(WebSocketGetComputeCertificateRequest &&) = default;
    WebSocketGetComputeCertificateRequest &operator=(const WebSocketGetComputeCertificateRequest &) = default;
    WebSocketGetComputeCertificateRequest &operator=(WebSocketGetComputeCertificateRequest &&) = default;
    ~WebSocketGetComputeCertificateRequest() = default;

    friend std::ostream &operator<<(std::ostream &os, const WebSocketGetComputeCertificateRequest &describePlayerSessionsRequest);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const override;
    bool Deserialize(const rapidjson::Value &value) override;

private:
    static constexpr const char *ACTION = "GetComputeCertificate";
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws