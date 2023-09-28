// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <iostream>
#include <string>

// GameLift
#include <aws/gamelift/core/api.h>

namespace GameLift
{
    namespace Utils
    {
        static const int BASE_2 = 2;
        static const int BASE_16 = 16;
        static const int BASE_36 = 36;

        class GAMELIFT_API EncodingUtils
        {
        public:
            /**
            * @brief Decimal to provided base encoding.
            *
            * @details Converts an input base10 string and returns the equivalent string encoded to provided base value.
            *
            * @param decimalStr Input base10 in string form.
            * @param base Base to convert to.
            * @returns String representation of 'base' encoded decimalStr, return empty string on error.
            */
            static std::string DecimalToBase(const std::string& decimalStr, const int base);

            /**
            * @brief Encodes a string in Base64.
            * 
            * @details Converts the input string to a Base64 byte array, then converts the byte array to an ASCII compliant string.
            * 
            * @param str The input string to encode.
            * @returns Base64 encoded variant of the input string.
            */
            static std::string EncodeBase64(const std::string& str);

            /**
            * @brief Decodes a Base64 encoded string.
            * 
            * @details Decodes the input string into a byte array, then converts the byte array into a string.
            * 
            * @param encodedStr The input string to decode.
            * @returns Decoded variant of the Base64 encoded input string.
            */
            static std::string DecodeBase64(const std::string& encodedStr);
        };
    }
}