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
class ResponseMessage : public Message {
public:
    ResponseMessage() : m_statusCode(-1), m_errorMessage("") {
        SetAction("");
        SetRequestId("");
    }

    ResponseMessage(const ResponseMessage &) = default;

    ResponseMessage(ResponseMessage &&) = default;

    ResponseMessage &operator=(const ResponseMessage &) = default;

    ResponseMessage &operator=(ResponseMessage &&) = default;

    ~ResponseMessage() = default;

    inline int GetStatusCode() const { return m_statusCode; }

    inline void SetStatusCode(const int statusCode) { m_statusCode = statusCode; }

    inline ResponseMessage &WithStatusCode(const long statusCode) {
        SetStatusCode(statusCode);
        return *this;
    }

    inline std::string GetErrorMessage() const { return m_errorMessage; }

    inline void SetErrorMessage(const std::string errorMessage) { m_errorMessage = errorMessage; }

    inline ResponseMessage &WithErrorMessage(const std::string errorMessage) {
        SetErrorMessage(errorMessage);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const ResponseMessage &responseMessage);

protected:
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;

    virtual bool Deserialize(const rapidjson::Value &obj);

private:
    static constexpr const char *STATUS_CODE = "StatusCode";
    static constexpr const char *ERROR_MESSAGE = "ErrorMessage";

    int m_statusCode;
    std::string m_errorMessage;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws