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

#include <map>
#include <string>

namespace Aws {
namespace GameLift {
namespace Internal {

/**
 * Class modeling universal resource identifier. Member variables for this class can only be set via
 * Builder.
 */
class Uri final {
public:
    class UriBuilder {
    public:
        /**
         *  Add query parameters to the UriBuilder.
         */
        UriBuilder &AddQueryParam(const std::string &key, const std::string &value);

        /**
         * Add the base URL. This includes any part of the URI except the query string.
         */
        UriBuilder &WithBaseUri(const std::string &baseUriString);

        /**
         * Build the URI
         */
        Uri Build() const;

    private:
        std::string m_baseUriString;
        std::map<std::string, std::string> m_queryParams;
    };

    Uri() = default;
    Uri(const Uri &) = default;
    Uri(Uri &&) = default;
    Uri &operator=(const Uri &) = default;
    Uri &operator=(Uri &&) = default;
    ~Uri() = default;

    /**
     * Gets the full URI as a String (including query parameters)
     */
    inline const std::string &GetUriString() const { return m_uriString; }

    /**
     * Get the URI as a string (all except the query parameters)
     */
    inline const std::string &GetBaseUriString() const { return m_baseUriString; }

    /**
     * Gets the Map of query params (keys to values)
     */
    inline const std::map<std::string, std::string> &GetQueryMap() const { return m_queryMap; }

    inline bool operator==(const Uri &other) const { return other.GetUriString() == GetUriString(); }

    friend std::ostream &operator<<(std::ostream &os, const Uri &uri);

private:
    Uri(const std::string &baseUriString, const std::map<std::string, std::string> &queryMap);

    void SetQueryString(const std::map<std::string, std::string> &queryMap);

    std::string m_uriString;
    std::string m_baseUriString;
    std::string m_queryString;
    std::map<std::string, std::string> m_queryMap;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws