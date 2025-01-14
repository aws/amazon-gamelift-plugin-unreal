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

#include <map>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <vector>

namespace Aws {
namespace GameLift {
namespace Internal {

enum class WebSocketAttrType { NONE, STRING, DOUBLE, STRING_LIST, STRING_DOUBLE_MAP };

class WebSocketAttributeValue {
public:
    WebSocketAttributeValue() : m_attrType(WebSocketAttrType::NONE){};
    WebSocketAttributeValue(const WebSocketAttributeValue &) = default;
    WebSocketAttributeValue(WebSocketAttributeValue &&) = default;
    WebSocketAttributeValue &operator=(const WebSocketAttributeValue &) = default;
    WebSocketAttributeValue &operator=(WebSocketAttributeValue &&) = default;
    ~WebSocketAttributeValue() = default;

    inline const WebSocketAttrType &GetAttributeType() const { return m_attrType; }

    inline void SetAttributeType(const WebSocketAttrType &attrType) { m_attrType = attrType; }

    inline WebSocketAttributeValue &WithAttributeType(const WebSocketAttrType &attrType) {
        SetAttributeType(attrType);
        return *this;
    }

    inline const std::string GetAttributeTypeAsString() const {
        switch (m_attrType) {
        case WebSocketAttrType::STRING:
            return std::string(STRING);
        case WebSocketAttrType::DOUBLE:
            return std::string(DOUBLE);
        case WebSocketAttrType::STRING_LIST:
            return std::string(STRING_LIST);
        case WebSocketAttrType::STRING_DOUBLE_MAP:
            return std::string(STRING_DOUBLE_MAP);
        default:
            return std::string(NONE);
        }
    }

    inline void SetAttributeType(const std::string &attrType) {
        if (strcmp(attrType.c_str(), STRING) == 0) {
            m_attrType = WebSocketAttrType::STRING;
        } else if (strcmp(attrType.c_str(), DOUBLE) == 0) {
            m_attrType = WebSocketAttrType::DOUBLE;
        } else if (strcmp(attrType.c_str(), STRING_LIST) == 0) {
            m_attrType = WebSocketAttrType::STRING_LIST;
        } else if (strcmp(attrType.c_str(), STRING_DOUBLE_MAP) == 0) {
            m_attrType = WebSocketAttrType::STRING_DOUBLE_MAP;
        } else {
            m_attrType = WebSocketAttrType::NONE;
        }
    }

    inline const std::string &GetS() const { return m_S; }

    inline void SetS(const std::string &s) { m_S = s; }

    inline WebSocketAttributeValue &WithS(const std::string &s) {
        SetS(s);
        return *this;
    }

    inline const double &GetN() const { return m_N; }

    inline void SetN(const double &n) { m_N = n; }

    inline WebSocketAttributeValue &WithN(const double &n) {
        SetN(n);
        return *this;
    }

    inline const std::vector<std::string> &GetSL() const { return m_SL; }

    inline void SetSL(const std::vector<std::string> &sl) { m_SL = sl; }

    inline WebSocketAttributeValue &WithSL(const std::vector<std::string> &sl) {
        SetSL(sl);
        return *this;
    }

    inline const std::map<std::string, double> &GetSDM() const { return m_SDM; }

    inline void SetSDM(const std::map<std::string, double> &sdm) { m_SDM = sdm; }

    inline WebSocketAttributeValue &WithSDM(const std::map<std::string, double> &sdm) {
        SetSDM(sdm);
        return *this;
    }

    std::string Serialize() const;
    bool Deserialize(const std::string &jsonString);
    bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const;
    bool Deserialize(const rapidjson::Value &value);

private:
    static constexpr const char *ATTR_TYPE = "AttrType";
    static constexpr const char *S = "S";
    static constexpr const char *N = "N";
    static constexpr const char *SL = "SL";
    static constexpr const char *SDM = "SDM";

    static constexpr const char *NONE = "NONE";
    static constexpr const char *STRING = "STRING";
    static constexpr const char *DOUBLE = "DOUBLE";
    static constexpr const char *STRING_LIST = "STRING_LIST";
    static constexpr const char *STRING_DOUBLE_MAP = "STRING_DOUBLE_MAP";

    WebSocketAttrType m_attrType;
    std::string m_S;
    double m_N;
    std::vector<std::string> m_SL;
    std::map<std::string, double> m_SDM;
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws