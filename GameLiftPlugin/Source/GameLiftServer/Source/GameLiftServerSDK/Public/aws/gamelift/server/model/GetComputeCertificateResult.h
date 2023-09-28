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

#ifndef GAMELIFT_USE_STD
#ifndef MAX_CERT_PATH_LENGTH
#define MAX_CERT_PATH_LENGTH 1024
#endif
#ifndef MAX_COMPUTE_NAME_LENGTH
#define MAX_COMPUTE_NAME_LENGTH 1024
#endif
#endif

namespace Aws {
namespace GameLift {
namespace Server {
namespace Model {
/**
 * <p>Represents the returned data in response to a request action.</p>
 */
class AWS_GAMELIFT_API GetComputeCertificateResult {
#ifdef GAMELIFT_USE_STD
public:
    GetComputeCertificateResult() {}

    /**
     * <p>Destructor.</p>
     */
    ~GetComputeCertificateResult() {}

    /**
     * <p>Copy Constructor.</p>
     */
    GetComputeCertificateResult(const GetComputeCertificateResult &other) : m_certificate_path(other.m_certificate_path), m_computeName(other.m_computeName) {}

    /**
     * <p>Move Constructor.</p>
     */
    GetComputeCertificateResult(GetComputeCertificateResult &&other) { *this = std::move(other); }

    /**
     * <p>Copy assignment Constructor.</p>
     */
    GetComputeCertificateResult &operator=(const GetComputeCertificateResult &other) {
        m_certificate_path = other.m_certificate_path;
        m_computeName = other.m_computeName;
        return *this;
    }

    /**
     * <p>Move assignment Constructor.</p>
     */
    GetComputeCertificateResult &operator=(GetComputeCertificateResult &&other) {
        m_certificate_path = std::move(other.m_certificate_path);
        m_computeName = std::move(other.m_computeName);
        return *this;
    }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline const std::string &GetCertificatePath() const { return m_certificate_path; }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline void SetCertificatePath(const std::string &value) { m_certificate_path = value; }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline void SetCertificatePath(std::string &&value) { m_certificate_path = std::move(value); }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline void SetCertificatePath(const char *value) { m_certificate_path.assign(value); }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline GetComputeCertificateResult &WithCertificatePath(const std::string &value) {
        SetCertificatePath(value);
        return *this;
    }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline GetComputeCertificateResult &WithCertificatePath(const std::string &&value) {
        SetCertificatePath(value);
        return *this;
    }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline GetComputeCertificateResult &WithCertificatePath(const char *value) {
        SetCertificatePath(value);
        return *this;
    }

    /**
     * <p>Compute name of this instance</p>
     */
    inline const std::string &GetComputeName() const { return m_computeName; }

    /**
     * <p>Compute name of this instance</p>
     */
    inline void SetComputeName(const std::string &value) { m_computeName = value; }

    /**
     * <p>Compute name of this instance</p>
     */
    inline void SetComputeName(std::string &&value) { m_computeName = std::move(value); }

    /**
     * <p>Compute name of this instance</p>
     */
    inline void SetComputeName(const char *value) { m_computeName.assign(value); }

    /**
     * <p>Compute name of this instance</p>
     */
    inline GetComputeCertificateResult &WithComputeName(const std::string &value) {
        SetComputeName(value);
        return *this;
    }

    /**
     * <p>Compute name of this instance</p>
     */
    inline GetComputeCertificateResult &WithComputeName(const std::string &&value) {
        SetComputeName(value);
        return *this;
    }

    /**
     * <p>Compute name of this instance</p>
     */
    inline GetComputeCertificateResult &WithComputeName(const char *value) {
        SetComputeName(value);
        return *this;
    }

private:
    std::string m_certificate_path;
    std::string m_computeName;
#else
public:
    GetComputeCertificateResult() {
        memset(m_certificate_path, 0, sizeof(m_certificate_path));
        memset(m_computeName, 0, sizeof(m_computeName));
    }

    /**
     * <p>Destructor.</p>
     */
    ~GetComputeCertificateResult() {}

    /**
     * <p>Copy Constructor.</p>
     */
    GetComputeCertificateResult(const GetComputeCertificateResult &other) {
        strncpy(m_certificate_path, other.m_certificate_path, sizeof(other.m_certificate_path));
        strncpy(m_computeName, other.m_computeName, sizeof(other.m_computeName));
    }

    /**
     * <p>Move Constructor.</p>
     */
    GetComputeCertificateResult(GetComputeCertificateResult &&other) { *this = std::move(other); }

    /**
     * <p>Copy assignment Constructor.</p>
     */
    GetComputeCertificateResult &operator=(const GetComputeCertificateResult &other) {
        strncpy(m_certificate_path, other.m_certificate_path, sizeof(other.m_certificate_path));
        strncpy(m_computeName, other.m_computeName, sizeof(other.m_computeName));

        return *this;
    }

    /**
     * <p>Move assignment Constructor.</p>
     */
    GetComputeCertificateResult &operator=(GetComputeCertificateResult &&other) {
        strncpy(m_certificate_path, other.m_certificate_path, sizeof(other.m_certificate_path));
        strncpy(m_computeName, other.m_computeName, sizeof(other.m_computeName));

        memset(other.m_certificate_path, 0, sizeof(other.m_certificate_path));
        memset(other.m_computeName, 0, sizeof(other.m_computeName));

        return *this;
    }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline const char *GetCertificatePath() const { return m_certificate_path; }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline void SetCertificatePath(const char *value) {
        strncpy(m_certificate_path, value, sizeof(m_certificate_path));
        m_certificate_path[sizeof(m_certificate_path) - 1] = '\0';
    }

    /**
     * <p>Certificate PEM file path.</p>
     */
    inline GetComputeCertificateResult &WithCertificatePath(const char *value) {
        SetCertificatePath(value);
        return *this;
    }

    /**
     * <p>Compute name of this instance.</p>
     */
    inline const char *GetComputeName() const { return m_computeName; }

    /**
     * <p>Compute name of this instance.</p>
     */
    inline void SetComputeName(const char *value) {
        strncpy(m_computeName, value, sizeof(m_computeName));
        m_computeName[sizeof(m_computeName) - 1] = '\0';
    }

    /**
     * <p>Compute name of this instance.</p>
     */
    inline GetComputeCertificateResult &WithComputeName(const char *value) {
        SetComputeName(value);
        return *this;
    }

private:
    char m_certificate_path[MAX_CERT_PATH_LENGTH];
    char m_computeName[MAX_COMPUTE_NAME_LENGTH];
#endif
};

} // namespace Model
} // namespace Server
} // namespace GameLift
} // namespace Aws

#if defined(_MSC_VER) && !defined(GAMELIFT_USE_STD)
#pragma warning(pop) // Restore warnings to previous state.
#endif