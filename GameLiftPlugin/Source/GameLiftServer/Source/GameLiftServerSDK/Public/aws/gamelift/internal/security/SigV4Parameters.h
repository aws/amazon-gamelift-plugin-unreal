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
#include <map>
#include <aws/gamelift/internal/security/AwsCredentials.h>

namespace Aws {
namespace GameLift {
namespace Internal {

struct SigV4Parameters {
    std::string AwsRegion;
    AwsCredentials Credentials;
    std::map <std::string, std::string> QueryParams;
    std::tm RequestTime;

    SigV4Parameters(const std::string &awsRegion, const class AwsCredentials &awsCredentials,
                    const std::map <std::string, std::string> &queryParams, const tm &requestTime)
            :
            AwsRegion(awsRegion), Credentials(awsCredentials), QueryParams(queryParams),
            RequestTime(requestTime) {}
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws
