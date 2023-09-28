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
#include <vector>

namespace Aws {
namespace GameLift {
namespace Internal {
/**
 * WebSocketDescribePlayerSessionsRequest Response. This response is sent to the GameLift WebSocket
 * during a DescribePlayerSessions call
 */
class WebSocketGetComputeCertificateResponse : public Message {
public:
    WebSocketGetComputeCertificateResponse() { SetAction(ACTION); };
    WebSocketGetComputeCertificateResponse(const WebSocketGetComputeCertificateResponse &) = default;
    WebSocketGetComputeCertificateResponse(WebSocketGetComputeCertificateResponse &&) = default;
    WebSocketGetComputeCertificateResponse &operator=(const WebSocketGetComputeCertificateResponse &) = default;
    WebSocketGetComputeCertificateResponse &operator=(WebSocketGetComputeCertificateResponse &&) = default;
    ~WebSocketGetComputeCertificateResponse() = default;

    inline const std::string &GetComputeName() const { return m_computeName; }

    inline void SetComputeName(const std::string &computeName) { m_computeName = computeName; }

    inline WebSocketGetComputeCertificateResponse &WithComputeName(const std::string &computeName) {
        SetComputeName(computeName);
        return *this;
    }

    inline const std::string &GetCertificatePath() const { return m_certificatePath; }

    inline void SetCertificatePath(const std::string &certificatePath) { m_certificatePath = certificatePath; }

    inline WebSocketGetComputeCertificateResponse &WithCertificatePath(const std::string &certificatePath) {
        SetCertificatePath(certificatePath);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const WebSocketGetComputeCertificateResponse &webSocketGetComputeCertificateResponse);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const override;
    bool Deserialize(const rapidjson::Value &value) override;

private:
    static constexpr const char *ACTION = "GetComputeCertificate";

    static constexpr const char *COMPUTE_NAME = "ComputeName";
    static constexpr const char *CERTIFICATE_PATH = "CertificatePath";

    std::string m_computeName;
    std::string m_certificatePath;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws