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

#include <aws/gamelift/internal/retry/RetryStrategy.h>

namespace Aws {
namespace GameLift {
namespace Internal {
class JitteredGeometricBackoffRetryStrategy : public RetryStrategy {
public:
    JitteredGeometricBackoffRetryStrategy()
        : m_maxRetries(DEFAULT_MAX_RETRIES), m_initialRetryIntervalMs(DEFAULT_INITIAL_RETRY_INTERVAL_MS), m_retryFactor(DEFAULT_RETRY_FACTOR),
          m_minRetryDelayMs(DEFAULT_MIN_RETRY_DELAY_MS) {}

    void apply(const std::function<bool(void)> &callable) override;

private:
    static constexpr const int DEFAULT_MAX_RETRIES = 5;
    static constexpr const int DEFAULT_INITIAL_RETRY_INTERVAL_MS = 1000;
    static constexpr const int DEFAULT_MIN_RETRY_DELAY_MS = 100;
    static constexpr const int DEFAULT_RETRY_FACTOR = 2;

    int m_maxRetries;
    int m_initialRetryIntervalMs;
    int m_retryFactor;
    int m_minRetryDelayMs;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws