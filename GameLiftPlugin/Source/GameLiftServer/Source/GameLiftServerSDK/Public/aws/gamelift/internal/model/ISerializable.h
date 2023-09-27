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

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * Interface for objects that are json serializable (i.e. the Message class).
 */
class ISerializable {
protected:
    /**
     * Serialize the object into Json and return the value.
     */
    virtual std::string Serialize() const = 0;

    /**
     * Given a JSON string deserialize the value and populate the member variables.
     */
    virtual bool Deserialize(const std::string &jsonString) = 0;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
