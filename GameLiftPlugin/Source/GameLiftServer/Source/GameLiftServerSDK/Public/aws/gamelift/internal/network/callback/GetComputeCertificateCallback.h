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
#include <aws/gamelift/internal/model/Message.h>

namespace Aws {
namespace GameLift {
namespace Internal {
/**
 * Class representing a default callback for GetComputeCertificate (action)
 */
class GetComputeCertificateCallback {
public:
    // Constructors
    GetComputeCertificateCallback(){};

    ~GetComputeCertificateCallback() = default;

    // Methods
    GenericOutcome OnGetComputeCertificateCallback(const std::string &data);

    static constexpr const char *GET_COMPUTE_CERTIFICATE = "GetComputeCertificate";
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws
