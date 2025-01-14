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
#include <aws/gamelift/common/Outcome.h>
#include <aws/gamelift/internal/model/Uri.h>
#include <functional>
#include <string>

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * Interface for a class that wraps a websocket implementation.
 */
class IWebSocketClientWrapper {
public:
    virtual Aws::GameLift::GenericOutcome Connect(const Uri &uri) = 0;
    virtual Aws::GameLift::GenericOutcome SendSocketMessage(const std::string &requestId, const std::string &message) = 0;
    virtual void Disconnect() = 0;
    virtual void RegisterGameLiftCallback(const std::string &gameLiftEvent, const std::function<GenericOutcome(std::string)> &callback) = 0;
    virtual bool IsConnected() = 0;

    virtual ~IWebSocketClientWrapper() = default;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
