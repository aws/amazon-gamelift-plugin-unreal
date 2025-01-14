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

#include <aws/gamelift/server/LogParameters.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <vector>

namespace Aws {
namespace GameLift {
namespace Internal {

// Simple Utility Class with some methods to help with json parsing
class JsonHelper {
public:
    static std::string SafelyDeserializeString(const rapidjson::Value &value, const char *key);
    static void WriteNonEmptyString(rapidjson::Writer<rapidjson::StringBuffer> *writer, const char *key, const std::string &value);

    static int SafelyDeserializeInt(const rapidjson::Value &value, const char *key);
    static void WritePositiveInt(rapidjson::Writer<rapidjson::StringBuffer> *writer, const char *key, int value);

    static long SafelyDeserializeLong(const rapidjson::Value &value, const char *key);
    static void WritePositiveLong(rapidjson::Writer<rapidjson::StringBuffer> *writer, const char *key, long value);

    static Aws::GameLift::Server::LogParameters SafelyDeserializeLogParameters(const rapidjson::Value &value, const char *key);
    static void WriteLogParameters(rapidjson::Writer<rapidjson::StringBuffer> *writer, const char *key, const Aws::GameLift::Server::LogParameters &value);
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws