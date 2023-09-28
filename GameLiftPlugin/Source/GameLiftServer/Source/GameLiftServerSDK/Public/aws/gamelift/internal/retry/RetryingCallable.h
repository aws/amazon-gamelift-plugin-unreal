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

#include <aws/gamelift/internal/retry/RetryStrategy.h>

namespace Aws {
namespace GameLift {
namespace Internal {

class RetryingCallable {
public:
    class Builder {
    public:
        Builder &WithRetryStrategy(RetryStrategy *retryStrategy);
        Builder &WithCallable(const std::function<bool(void)> &callable);
        RetryingCallable Build() const;

    private:
        std::function<bool(void)> m_callable;
        // Note: The RetryStrategy is not owned by the builder or the RetryingCallable
        RetryStrategy *m_retryStrategy;
    };

    void call();

private:
    RetryingCallable(RetryStrategy &retryStrategy, std::function<bool(void)> callable);

    RetryStrategy &m_retryStrategy;
    std::function<bool(void)> m_callable;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
