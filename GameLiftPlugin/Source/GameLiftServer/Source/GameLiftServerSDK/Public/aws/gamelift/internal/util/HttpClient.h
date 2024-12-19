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

#include <string>
#include <tuple>

namespace Aws {
namespace GameLift {
namespace Internal {

class HttpResponse {
public:
    int statusCode;
    std::string body;

    bool IsSuccessfulStatusCode();
};

class HttpClient {

private:
    static std::tuple<std::string, int, std::string> GetHostAndPortAndPath(const std::string &url);

    static HttpResponse ParseHttpResponse(const std::string &response);

public:
    HttpClient() {};

    /**
     * Sends an HTTP GET request to the specified URL.
     * Note: This method does not support DNS Resolution nor HTTPS/TLS connections.
     * @param url The URL to send the GET request to.
     * @return An HttpResponse object containing the status code and body of the response.
     * @throws std::runtime_error if there are errors during socket operations or invalid responses.
     */
    virtual HttpResponse SendGetRequest(const std::string &url);
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
