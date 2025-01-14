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
#include <iostream>

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * Message from GameLift initializing GameSession Creation
 */
class TerminateProcessMessage : public Message {
public:
    TerminateProcessMessage() : m_terminationTime(-1) { SetAction(TERMINATE_PROCESS); };
    TerminateProcessMessage(const TerminateProcessMessage &) = default;
    TerminateProcessMessage(TerminateProcessMessage &&) = default;
    TerminateProcessMessage &operator=(const TerminateProcessMessage &) = default;
    TerminateProcessMessage &operator=(TerminateProcessMessage &&) = default;
    ~TerminateProcessMessage() = default;

    inline long GetTerminationTime() const { return m_terminationTime; }

    inline void SetTerminationTime(const long terminationTime) { m_terminationTime = terminationTime; }

    inline TerminateProcessMessage &WithTerminationTime(const long terminationTime) {
        SetTerminationTime(terminationTime);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const TerminateProcessMessage &terminateProcessMessage);

protected:
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    virtual bool Deserialize(const rapidjson::Value &obj);

private:
    static constexpr const char *TERMINATE_PROCESS = "TerminateProcess";
    static constexpr const char *TERMINATION_TIME = "TerminationTime";

    long m_terminationTime;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
