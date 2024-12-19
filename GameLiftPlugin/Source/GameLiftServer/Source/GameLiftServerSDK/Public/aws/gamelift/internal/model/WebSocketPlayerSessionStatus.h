/*
 * All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
 * its licensors.
 *
 * For complete copyright and license terms please see the LICENSE at the root of this
 * distribution (the "License"). All use of this software is governed by the License,
 * or, if provided, by the license below or the license accompanying this file. Do not
 * remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#pragma once
#include <string>

namespace Aws {
namespace GameLift {
namespace Internal {

enum class WebSocketPlayerSessionStatus { NOT_SET, RESERVED, ACTIVE, COMPLETED, TIMEDOUT };

class WebSocketPlayerSessionStatusMapper {
public:
    inline static WebSocketPlayerSessionStatus GetStatusForName(const std::string &name) {
        if (name == RESERVED) {
            return WebSocketPlayerSessionStatus::RESERVED;
        }
        if (name == ACTIVE) {
            return WebSocketPlayerSessionStatus::ACTIVE;
        }
        if (name == COMPLETED) {
            return WebSocketPlayerSessionStatus::COMPLETED;
        }
        if (name == TIMEDOUT) {
            return WebSocketPlayerSessionStatus::TIMEDOUT;
        }
        return WebSocketPlayerSessionStatus::NOT_SET;
    }

    inline static std::string GetNameForStatus(WebSocketPlayerSessionStatus value) {
        switch (value) {
        case WebSocketPlayerSessionStatus::RESERVED:
            return RESERVED;
        case WebSocketPlayerSessionStatus::ACTIVE:
            return ACTIVE;
        case WebSocketPlayerSessionStatus::COMPLETED:
            return COMPLETED;
        case WebSocketPlayerSessionStatus::TIMEDOUT:
            return TIMEDOUT;
        default:
            return NOT_SET;
        }
    }

private:
    static constexpr const char *RESERVED = "RESERVED";
    static constexpr const char *ACTIVE = "ACTIVE";
    static constexpr const char *COMPLETED = "COMPLETED";
    static constexpr const char *TIMEDOUT = "TIMEDOUT";
    static constexpr const char *NOT_SET = "NOT_SET";
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws