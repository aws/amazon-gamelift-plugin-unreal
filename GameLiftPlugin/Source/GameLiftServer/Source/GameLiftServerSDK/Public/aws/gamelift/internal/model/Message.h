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

#include <aws/gamelift/internal/model/ISerializable.h>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <string>

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * Base Message class representing a message that is sent to and from the GameLift WebSocket. All
 * messages have a request ID, which represents the following:
 * - For outgoing messages: A randomly generated ID
 * - For incoming messages: The ID of the outgoing message which triggered the incoming
 * messages/response
 */
class Message : public ISerializable {
public:
    Message() : m_requestId(Message::GenerateRandomRequestId()) {}
    Message(const Message &) = default;
    Message(Message &&) = default;
    Message &operator=(const Message &) = default;
    Message &operator=(Message &&) = default;
    ~Message() = default;

    inline const std::string &GetAction() const { return m_action; }

    inline const std::string &GetRequestId() const { return m_requestId; }

    inline void SetAction(const std::string &action) { m_action = action; }

    inline void SetRequestId(const std::string &requestId) { m_requestId = requestId; }

    inline Message &WithAction(const std::string &action) {
        SetAction(action);
        return *this;
    }

    inline Message &WithRequestId(const std::string &requestId) {
        SetRequestId(requestId);
        return *this;
    }

    /**
     * Serialize the Message into Json and return the value.
     */
    std::string Serialize() const override;

    /**
     * Deserialize the given json string and populate the member variables.
     */
    bool Deserialize(const std::string &jsonString) override;

    friend std::ostream &operator<<(std::ostream &os, const Message &message);

protected:
    /**
     * Write this message's member variables to the stringBuffer using the provided writer
     * Subclasses of Message should override this function in order to allow for polymorphic
     * serialization.
     */
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;

    /**
     * Given RapidJson Value deserialize and populate this message's member variables.
     * Subclasses of Message should override this function in order to allow for polymorphic
     * deserialization.
     */
    virtual bool Deserialize(const rapidjson::Value &obj);

private:
    static constexpr const char *ACTION = "Action";
    static constexpr const char *REQUEST_ID = "RequestId";

    std::string m_action;
    std::string m_requestId;

    static std::string GenerateRandomRequestId();
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
