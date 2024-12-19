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
#include <ctime>
#include <string.h>

#if defined(_MSC_VER) && !defined(GAMELIFT_USE_STD)
#pragma warning(push)           // Save warning settings.
#pragma warning(disable : 4996) // Disable deprecated warning for strncpy
#endif

#ifndef GAMELIFT_USE_STD

#ifndef MAX_ASSUMED_USER_ROLE_ARN_LENGTH
#define MAX_ASSUMED_USER_ROLE_ARN_LENGTH 2048
#endif
#ifndef MAX_ASSUMED_ROLE_ID_LENGTH
#define MAX_ASSUMED_ROLE_ID_LENGTH 2048
#endif
#ifndef MAX_ACCESS_KEY_ID_LENGTH
#define MAX_ACCESS_KEY_ID_LENGTH 128
#endif
#ifndef MAX_SECRET_ACCESS_KEY_LENGTH
#define MAX_SECRET_ACCESS_KEY_LENGTH 128
#endif

#endif

namespace Aws {
namespace GameLift {
namespace Server {
namespace Model {
class AWS_GAMELIFT_API GetFleetRoleCredentialsResult {
#ifdef GAMELIFT_USE_STD
public:
    GetFleetRoleCredentialsResult() : m_expiration({0}) {}

    ~GetFleetRoleCredentialsResult() = default;

    GetFleetRoleCredentialsResult(const GetFleetRoleCredentialsResult &other) { *this = other; }

    GetFleetRoleCredentialsResult(GetFleetRoleCredentialsResult &&other) noexcept { *this = std::move(other); }

    GetFleetRoleCredentialsResult &operator=(const GetFleetRoleCredentialsResult &other) = default;

    GetFleetRoleCredentialsResult &operator=(GetFleetRoleCredentialsResult &&other) noexcept {
        m_assumedUserRoleArn = std::move(other.m_assumedUserRoleArn);
        m_assumedRoleId = std::move(other.m_assumedRoleId);
        m_accessKeyId = std::move(other.m_accessKeyId);
        m_secretAccessKey = std::move(other.m_secretAccessKey);
        m_sessionToken = std::move(other.m_sessionToken);
        m_expiration = other.m_expiration;

        return *this;
    }

    inline const std::string &GetAssumedUserRoleArn() const { return m_assumedUserRoleArn; }

    inline void SetAssumedUserRoleArn(const std::string &value) { m_assumedUserRoleArn = value; }

    inline void SetAssumedUserRoleArn(std::string &&value) { m_assumedUserRoleArn = std::move(value); }

    inline void SetAssumedUserRoleArn(const char *value) { m_assumedUserRoleArn.assign(value); }

    inline GetFleetRoleCredentialsResult &WithAssumedUserRoleArn(const std::string &value) {
        SetAssumedUserRoleArn(value);
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithAssumedUserRoleArn(std::string &&value) {
        SetAssumedUserRoleArn(std::move(value));
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithAssumedUserRoleArn(const char *value) {
        SetAssumedUserRoleArn(value);
        return *this;
    }

    inline const std::string &GetAssumedRoleId() const { return m_assumedRoleId; }

    inline void SetAssumedRoleId(const std::string &value) { m_assumedRoleId = value; }

    inline void SetAssumedRoleId(std::string &&value) { m_assumedRoleId = std::move(value); }

    inline void SetAssumedRoleId(const char *value) { m_assumedRoleId.assign(value); }

    inline GetFleetRoleCredentialsResult &WithAssumedRoleId(const std::string &value) {
        SetAssumedRoleId(value);
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithAssumedRoleId(std::string &&value) {
        SetAssumedRoleId(std::move(value));
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithAssumedRoleId(const char *value) {
        SetAssumedRoleId(value);
        return *this;
    }

    inline const std::string &GetAccessKeyId() const { return m_accessKeyId; }

    inline void SetAccessKeyId(const std::string &value) { m_accessKeyId = value; }

    inline void SetAccessKeyId(std::string &&value) { m_accessKeyId = std::move(value); }

    inline void SetAccessKeyId(const char *value) { m_accessKeyId.assign(value); }

    inline GetFleetRoleCredentialsResult &WithAccessKeyId(const std::string &value) {
        SetAccessKeyId(value);
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithAccessKeyId(std::string &&value) {
        SetAccessKeyId(std::move(value));
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithAccessKeyId(const char *value) {
        SetAccessKeyId(value);
        return *this;
    }

    inline const std::string &GetSecretAccessKey() const { return m_secretAccessKey; }

    inline void SetSecretAccessKey(const std::string &value) { m_secretAccessKey = value; }

    inline void SetSecretAccessKey(std::string &&value) { m_secretAccessKey = std::move(value); }

    inline void SetSecretAccessKey(const char *value) { m_secretAccessKey.assign(value); }

    inline GetFleetRoleCredentialsResult &WithSecretAccessKey(const std::string &value) {
        SetSecretAccessKey(value);
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithSecretAccessKey(std::string &&value) {
        SetSecretAccessKey(std::move(value));
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithSecretAccessKey(const char *value) {
        SetSecretAccessKey(value);
        return *this;
    }

    inline const std::string &GetSessionToken() const { return m_sessionToken; }

    inline void SetSessionToken(const std::string &value) { m_sessionToken = value; }

    inline void SetSessionToken(std::string &&value) { m_sessionToken = std::move(value); }

    inline void SetSessionToken(const char *value) { m_sessionToken.assign(value); }

    inline GetFleetRoleCredentialsResult &WithSessionToken(const std::string &value) {
        SetSessionToken(value);
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithSessionToken(std::string &&value) {
        SetSessionToken(std::move(value));
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithSessionToken(const char *value) {
        SetSessionToken(value);
        return *this;
    }

    inline const std::tm &GetExpiration() const { return m_expiration; }

    inline void SetExpiration(const std::tm &value) { m_expiration = value; }

    inline void SetExpiration(std::tm &&value) { m_expiration = value; }

    inline void SetExpiration(const time_t &epochTime) {
#ifdef WIN32
        gmtime_s(&m_expiration, &epochTime);
#else
        gmtime_r(&epochTime, &m_expiration);
#endif
    }

    inline GetFleetRoleCredentialsResult &WithExpiration(const std::tm &value) {
        SetExpiration(value);
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithExpiration(const std::tm &&value) {
        SetExpiration(value);
        return *this;
    }

    inline GetFleetRoleCredentialsResult &WithExpiration(const time_t &epochTime) {
        SetExpiration(epochTime);
        return *this;
    }

private:
    std::string m_assumedUserRoleArn;
    std::string m_assumedRoleId;
    std::string m_accessKeyId;
    std::string m_secretAccessKey;
    std::string m_sessionToken;
    std::tm m_expiration;
#else
public:
    GetFleetRoleCredentialsResult()
        : m_assumedUserRoleArn{'\0'}, m_assumedRoleId{'\0'}, m_accessKeyId{'\0'}, m_secretAccessKey{'\0'}, m_sessionToken(new char[1]{'\0'}), m_expiration(0) {}

    ~GetFleetRoleCredentialsResult() {
        delete[] m_sessionToken;
        m_sessionToken = nullptr;
    }

    GetFleetRoleCredentialsResult(const GetFleetRoleCredentialsResult &other) : m_sessionToken(nullptr) { *this = other; }

    GetFleetRoleCredentialsResult(GetFleetRoleCredentialsResult &&other) noexcept : m_sessionToken(nullptr) { *this = std::move(other); }

    GetFleetRoleCredentialsResult &operator=(const GetFleetRoleCredentialsResult &other) {
        // Don't allow self-assignment
        if (this != &other) {
            strncpy(m_assumedUserRoleArn, other.m_assumedUserRoleArn, sizeof(m_assumedUserRoleArn));
            strncpy(m_assumedRoleId, other.m_assumedRoleId, sizeof(m_assumedRoleId));
            strncpy(m_accessKeyId, other.m_accessKeyId, sizeof(m_accessKeyId));
            strncpy(m_secretAccessKey, other.m_secretAccessKey, sizeof(m_secretAccessKey));

            m_assumedUserRoleArn[sizeof(m_assumedUserRoleArn) - 1] = '\0';
            m_assumedRoleId[sizeof(m_assumedRoleId) - 1] = '\0';
            m_accessKeyId[sizeof(m_accessKeyId) - 1] = '\0';
            m_secretAccessKey[sizeof(m_secretAccessKey) - 1] = '\0';

            m_expiration = other.m_expiration;

            delete[] m_sessionToken;
            m_sessionToken = nullptr;
            if (other.m_sessionToken != nullptr) {
                m_sessionToken = new char[strlen(other.m_sessionToken) + 1];
                strcpy(m_sessionToken, other.m_sessionToken);
            }
        }

        return *this;
    }

    GetFleetRoleCredentialsResult &operator=(GetFleetRoleCredentialsResult &&other) noexcept {
        strncpy(m_assumedUserRoleArn, other.m_assumedUserRoleArn, sizeof(m_assumedUserRoleArn));
        strncpy(m_assumedRoleId, other.m_assumedRoleId, sizeof(m_assumedRoleId));
        strncpy(m_accessKeyId, other.m_accessKeyId, sizeof(m_accessKeyId));
        strncpy(m_secretAccessKey, other.m_secretAccessKey, sizeof(m_secretAccessKey));

        m_assumedUserRoleArn[sizeof(m_assumedUserRoleArn) - 1] = '\0';
        m_assumedRoleId[sizeof(m_assumedRoleId) - 1] = '\0';
        m_accessKeyId[sizeof(m_accessKeyId) - 1] = '\0';
        m_secretAccessKey[sizeof(m_secretAccessKey) - 1] = '\0';

        m_expiration = other.m_expiration;

        delete[] m_sessionToken;
        m_sessionToken = nullptr;
        if (other.m_sessionToken != nullptr) {
            m_sessionToken = new char[strlen(other.m_sessionToken) + 1];
            strcpy(m_sessionToken, other.m_sessionToken);
        }

        return *this;
    }

    inline const char *GetAssumedUserRoleArn() const { return m_assumedUserRoleArn; }

    inline void SetAssumedUserRoleArn(const char *value) {
        strncpy(m_assumedUserRoleArn, value, sizeof(m_assumedUserRoleArn));
        m_assumedUserRoleArn[sizeof(m_assumedUserRoleArn) - 1] = '\0';
    }

    inline GetFleetRoleCredentialsResult &WithAssumedUserRoleArn(const char *value) {
        SetAssumedUserRoleArn(value);
        return *this;
    }

    inline const char *GetAssumedRoleId() const { return m_assumedRoleId; }

    inline void SetAssumedRoleId(const char *value) {
        strncpy(m_assumedRoleId, value, sizeof(m_assumedRoleId));
        m_assumedRoleId[sizeof(m_assumedRoleId) - 1] = '\0';
    }

    inline GetFleetRoleCredentialsResult &WithAssumedRoleId(const char *value) {
        SetAssumedRoleId(value);
        return *this;
    }

    inline const char *GetAccessKeyId() const { return m_accessKeyId; }

    inline void SetAccessKeyId(const char *value) {
        strncpy(m_accessKeyId, value, sizeof(m_accessKeyId));
        m_accessKeyId[sizeof(m_accessKeyId) - 1] = '\0';
    }

    inline GetFleetRoleCredentialsResult &WithAccessKeyId(const char *value) {
        SetAccessKeyId(value);
        return *this;
    }

    inline const char *GetSecretAccessKey() const { return m_secretAccessKey; }

    inline void SetSecretAccessKey(const char *value) {
        strncpy(m_secretAccessKey, value, sizeof(m_secretAccessKey));
        m_secretAccessKey[sizeof(m_secretAccessKey) - 1] = '\0';
    }

    inline GetFleetRoleCredentialsResult &WithSecretAccessKey(const char *value) {
        SetSecretAccessKey(value);
        return *this;
    }

    inline const char *GetSessionToken() const { return m_sessionToken; }

    inline void SetSessionToken(const char *value) {
        delete[] m_sessionToken;
        m_sessionToken = nullptr;
        if (value != nullptr) {
            m_sessionToken = new char[strlen(value) + 1];
            strcpy(m_sessionToken, value);
        }
    }

    inline GetFleetRoleCredentialsResult &WithSessionToken(const char *value) {
        SetSessionToken(value);
        return *this;
    }

    inline time_t GetExpiration() const { return m_expiration; }

    inline void SetExpiration(const time_t value) { m_expiration = value; }

    inline GetFleetRoleCredentialsResult &WithExpiration(const time_t value) {
        SetExpiration(value);
        return *this;
    }

private:
    char m_assumedUserRoleArn[MAX_ASSUMED_USER_ROLE_ARN_LENGTH + 1];
    char m_assumedRoleId[MAX_ASSUMED_ROLE_ID_LENGTH + 1];
    char m_accessKeyId[MAX_ACCESS_KEY_ID_LENGTH + 1];
    char m_secretAccessKey[MAX_SECRET_ACCESS_KEY_LENGTH + 1];
    // Can't pre-allocate a buffer since AWS docs say:
    // -> We strongly recommend that you make no assumptions about the maximum [session token] size
    char *m_sessionToken;
    time_t m_expiration;
#endif
};
} // namespace Model
} // namespace Server
} // namespace GameLift
} // namespace Aws

#if defined(_MSC_VER) && !defined(GAMELIFT_USE_STD)
#pragma warning(pop) // Restore warnings to previous state.
#endif
