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

#include <aws/gamelift/common/GameLift_EXPORTS.h>

#if defined(_MSC_VER) && !defined(GAMELIFT_USE_STD)
#pragma warning(push)           // Save warning settings.
#pragma warning(disable : 4996) // Disable deprecated warning for strncpy
#endif

#ifndef MAX_ROLE_SESSION_NAME_LENGTH
#define MAX_ROLE_SESSION_NAME_LENGTH 64
#endif

#ifndef GAMELIFT_USE_STD

#ifndef MAX_ROLE_ARN_LENGTH
#define MAX_ROLE_ARN_LENGTH 2048
#endif

#endif

namespace Aws {
namespace GameLift {
namespace Server {
namespace Model {
class AWS_GAMELIFT_API GetFleetRoleCredentialsRequest {
#ifdef GAMELIFT_USE_STD
public:
    GetFleetRoleCredentialsRequest() = default;

    ~GetFleetRoleCredentialsRequest() = default;

    GetFleetRoleCredentialsRequest(const GetFleetRoleCredentialsRequest &other) { *this = other; }

    GetFleetRoleCredentialsRequest(GetFleetRoleCredentialsRequest &&other) noexcept { *this = std::move(other); }

    GetFleetRoleCredentialsRequest &operator=(const GetFleetRoleCredentialsRequest &other) = default;

    GetFleetRoleCredentialsRequest &operator=(GetFleetRoleCredentialsRequest &&other) noexcept {
        m_roleArn = std::move(other.m_roleArn);
        m_roleSessionName = std::move(other.m_roleSessionName);

        return *this;
    }

    inline const std::string &GetRoleArn() const { return m_roleArn; }

    inline void SetRoleArn(const std::string &value) { m_roleArn = value; }

    inline void SetRoleArn(std::string &&value) { m_roleArn = std::move(value); }

    inline void SetRoleArn(const char *value) { m_roleArn.assign(value); }

    inline GetFleetRoleCredentialsRequest &WithRoleArn(const std::string &value) {
        SetRoleArn(value);
        return *this;
    }

    inline GetFleetRoleCredentialsRequest &WithRoleArn(std::string &&value) {
        SetRoleArn(std::move(value));
        return *this;
    }

    inline GetFleetRoleCredentialsRequest &WithRoleArn(const char *value) {
        SetRoleArn(value);
        return *this;
    }

    inline const std::string &GetRoleSessionName() const { return m_roleSessionName; }

    inline void SetRoleSessionName(const std::string &value) { m_roleSessionName = value; }

    inline void SetRoleSessionName(std::string &&value) { m_roleSessionName = std::move(value); }

    inline void SetRoleSessionName(const char *value) { m_roleSessionName.assign(value); }

    inline GetFleetRoleCredentialsRequest &WithRoleSessionName(const std::string &value) {
        SetRoleSessionName(value);
        return *this;
    }

    inline GetFleetRoleCredentialsRequest &WithRoleSessionName(std::string &&value) {
        SetRoleSessionName(std::move(value));
        return *this;
    }

    inline GetFleetRoleCredentialsRequest &WithRoleSessionName(const char *value) {
        SetRoleSessionName(value);
        return *this;
    }

private:
    std::string m_roleArn;
    std::string m_roleSessionName;
#else
public:
    GetFleetRoleCredentialsRequest() : m_roleArn{'\0'}, m_roleSessionName{'\0'} {}

    ~GetFleetRoleCredentialsRequest() = default;

    GetFleetRoleCredentialsRequest(const GetFleetRoleCredentialsRequest &other) { *this = other; }

    GetFleetRoleCredentialsRequest(GetFleetRoleCredentialsRequest &&other) noexcept { *this = std::move(other); }

    GetFleetRoleCredentialsRequest &operator=(const GetFleetRoleCredentialsRequest &other) {
        strncpy(m_roleArn, other.m_roleArn, sizeof(m_roleArn));
        strncpy(m_roleSessionName, other.m_roleSessionName, sizeof(m_roleSessionName));

        m_roleArn[sizeof(m_roleArn) - 1] = '\0';
        m_roleSessionName[sizeof(m_roleSessionName) - 1] = '\0';

        return *this;
    }

    GetFleetRoleCredentialsRequest &operator=(GetFleetRoleCredentialsRequest &&other) noexcept {
        strncpy(m_roleArn, other.m_roleArn, sizeof(m_roleArn));
        strncpy(m_roleSessionName, other.m_roleSessionName, sizeof(m_roleSessionName));

        m_roleArn[sizeof(m_roleArn) - 1] = '\0';
        m_roleSessionName[sizeof(m_roleSessionName) - 1] = '\0';

        return *this;
    }

    inline const char *GetRoleArn() const { return m_roleArn; }

    inline void SetRoleArn(const char *value) {
        strncpy(m_roleArn, value, sizeof(m_roleArn));
        m_roleArn[sizeof(m_roleArn) - 1] = '\0';
    }

    inline GetFleetRoleCredentialsRequest &WithRoleArn(const char *value) {
        SetRoleArn(value);
        return *this;
    }

    inline const char *GetRoleSessionName() const { return m_roleSessionName; }

    inline void SetRoleSessionName(const char *value) {
        strncpy(m_roleSessionName, value, sizeof(m_roleSessionName));
        m_roleSessionName[sizeof(m_roleSessionName) - 1] = '\0';
    }

    inline GetFleetRoleCredentialsRequest &WithRoleSessionName(const char *value) {
        SetRoleSessionName(value);
        return *this;
    }

private:
    char m_roleArn[MAX_ROLE_ARN_LENGTH + 1];
    char m_roleSessionName[MAX_ROLE_SESSION_NAME_LENGTH + 1];
#endif
};
} // namespace Model
} // namespace Server
} // namespace GameLift
} // namespace Aws

#if defined(_MSC_VER) && !defined(GAMELIFT_USE_STD)
#pragma warning(pop) // Restore warnings to previous state.
#endif
