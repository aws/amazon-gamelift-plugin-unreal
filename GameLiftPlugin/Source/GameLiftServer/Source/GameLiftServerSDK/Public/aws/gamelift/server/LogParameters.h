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
#include <string.h>

#ifndef GAMELIFT_USE_STD
#ifndef MAX_LOG_PATHS
#define MAX_LOG_PATHS 10
#endif
#ifndef MAX_PATH_LENGTH
#define MAX_PATH_LENGTH 1024
#endif
#endif

namespace Aws {
namespace GameLift {
namespace Server {
class LogParameters {
#ifdef GAMELIFT_USE_STD
public:
    AWS_GAMELIFT_API LogParameters() {}
    AWS_GAMELIFT_API LogParameters(const std::vector<std::string> &logPaths) : m_logPaths(logPaths) {}

    // Copy constructor
    AWS_GAMELIFT_API LogParameters(const LogParameters &o) : m_logPaths(o.getLogPaths()) {}

    // Move Constructor
    AWS_GAMELIFT_API LogParameters(LogParameters &&o) : m_logPaths(std::move(o.getLogPaths())) {}

    AWS_GAMELIFT_API LogParameters &operator=(const LogParameters &o) {
        if (this != &o) {
            m_logPaths = o.getLogPaths();
        }

        return *this;
    }

    AWS_GAMELIFT_API LogParameters &operator=(LogParameters &&o) {
        if (this != &o) {
            m_logPaths = std::move(o.getLogPaths());
        }

        return *this;
    }

    AWS_GAMELIFT_API std::vector<std::string> getLogPaths() const { return m_logPaths; }

    AWS_GAMELIFT_API int getLogPathCount() const { return m_logPaths.size(); }

    AWS_GAMELIFT_API const char *getLogPath(int index) const { return index < m_logPaths.size() ? m_logPaths[index].c_str() : nullptr; }

    AWS_GAMELIFT_API bool operator==(const LogParameters &other) const { return getLogPaths() == other.getLogPaths(); }

private:
    std::vector<std::string> m_logPaths;
};
#else
public:
    AWS_GAMELIFT_API LogParameters() : m_count(0) { memset(m_logPaths, 0, sizeof(m_logPaths)); }

    AWS_GAMELIFT_API LogParameters(const char *const *logPaths, int count);

    AWS_GAMELIFT_API LogParameters(const LogParameters &o);

    AWS_GAMELIFT_API LogParameters &operator=(const LogParameters &o) {
        if (this == &o) {
            return *this;
        }

        int count = o.getLogPathCount();
        m_count = (count < MAX_LOG_PATHS) ? count : MAX_LOG_PATHS;
        for (int i = 0; i < m_count; ++i) {
#ifdef WIN32
            strcpy_s(m_logPaths[i], MAX_PATH_LENGTH, o.getLogPath(i));
#else
            strncpy(m_logPaths[i], o.getLogPath(i), MAX_PATH_LENGTH);
#endif
        }

        return *this;
    }

    AWS_GAMELIFT_API int getLogPathCount() const { return m_count; }

    AWS_GAMELIFT_API const char *getLogPath(int index) const { return index < m_count ? m_logPaths[index] : nullptr; }

    AWS_GAMELIFT_API bool operator==(const LogParameters &other) const {
        if (getLogPathCount() != other.getLogPathCount()) {
            return false;
        }

        for (size_t i = 0; i < getLogPathCount(); i++) {
            if (strcmp(getLogPath(i), other.getLogPath(i)) != 0) {
                return false;
            }
        }

        return true;
    }

private:
    char m_logPaths[MAX_LOG_PATHS][MAX_PATH_LENGTH];
    int m_count;
};
#endif
} // namespace Server
} // namespace GameLift
} // namespace Aws