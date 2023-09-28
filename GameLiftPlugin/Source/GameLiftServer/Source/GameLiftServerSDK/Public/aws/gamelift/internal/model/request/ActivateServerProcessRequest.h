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
#include <aws/gamelift/server/LogParameters.h>

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * ActivateServerProcess Request. This request is sent to the GameLift WebSocket during the
 * ProcessReady call
 */
class ActivateServerProcessRequest : public Message {
public:
    ActivateServerProcessRequest();
    ActivateServerProcessRequest(std::string sdkVersion, std::string sdkLanguage, int port, const Aws::GameLift::Server::LogParameters &logParameters);

    ActivateServerProcessRequest(const ActivateServerProcessRequest &) = default;
    ActivateServerProcessRequest(ActivateServerProcessRequest &&) = default;
    ActivateServerProcessRequest &operator=(const ActivateServerProcessRequest &) = default;
    ActivateServerProcessRequest &operator=(ActivateServerProcessRequest &&) = default;
    ~ActivateServerProcessRequest() = default;

    inline const std::string &GetSdkVersion() const { return m_sdkVersion; }

    inline const std::string &GetSdkLanguage() const { return m_sdkLanguage; }

    inline const int GetPort() const { return m_port; }

    inline const Aws::GameLift::Server::LogParameters GetLogParameters() const { return m_logParameters; }

    inline void SetSdkVersion(const std::string &sdkVersion) { m_sdkVersion = sdkVersion; }

    inline void SetSdkLanguage(const std::string &sdkLanguage) { m_sdkLanguage = sdkLanguage; }

    inline void SetPort(const int port) { m_port = port; }

    inline void SetLogParameters(const Aws::GameLift::Server::LogParameters &logParameters) { m_logParameters = logParameters; }

    inline ActivateServerProcessRequest &WithPort(const int port) {
        SetPort(port);
        return *this;
    }

    inline ActivateServerProcessRequest &WithLogParameters(const Aws::GameLift::Server::LogParameters &logParameters) {
        SetLogParameters(logParameters);
        return *this;
    }

    inline ActivateServerProcessRequest &WithSdkVersion(const std::string &sdkVersion) {
        SetSdkVersion(sdkVersion);
        return *this;
    }

    inline ActivateServerProcessRequest &WithSdkLanguage(const std::string &sdkLanguage) {
        SetSdkLanguage(sdkLanguage);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const ActivateServerProcessRequest &request);

protected:
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    bool Deserialize(const rapidjson::Value &value);

private:
    static constexpr const char *ACTIVATE_SERVER_PROCESS = "ActivateServerProcess";
    static constexpr const char *SDK_VERSION = "SdkVersion";
    static constexpr const char *SDK_LANGUAGE = "SdkLanguage";
    static constexpr const char *PORT = "Port";
    static constexpr const char *LOG_PATHS = "LogPaths";

    std::string m_sdkVersion;
    std::string m_sdkLanguage;
    int m_port;
    Aws::GameLift::Server::LogParameters m_logParameters;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
