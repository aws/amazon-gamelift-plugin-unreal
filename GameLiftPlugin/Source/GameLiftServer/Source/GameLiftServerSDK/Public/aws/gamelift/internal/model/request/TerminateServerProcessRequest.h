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
 * TerminateServerProcess Request. This request is sent to the GameLift WebSocket during the
 * ProcessEnding call
 */
class TerminateServerProcessRequest : public Message {
public:
    TerminateServerProcessRequest();

    TerminateServerProcessRequest(const TerminateServerProcessRequest &) = default;
    TerminateServerProcessRequest(TerminateServerProcessRequest &&) = default;
    TerminateServerProcessRequest &operator=(const TerminateServerProcessRequest &) = default;
    TerminateServerProcessRequest &operator=(TerminateServerProcessRequest &&) = default;
    ~TerminateServerProcessRequest() = default;

private:
    static constexpr const char *TERMINATE_SERVER_PROCESS = "TerminateServerProcess";
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws