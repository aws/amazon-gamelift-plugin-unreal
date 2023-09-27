// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <regex>
#include <iostream>
#include <sstream>
#include <iomanip>

// GameLift
#include <aws/gamelift/core/api.h>

namespace GameLift
{
	namespace Utils
	{
		static const int MIN_URL_PARAM_CHARS = 1;
		static const int MAX_URL_PARAM_CHARS = 1023;
		static const int MIN_S3_PARAM_CHARS = 1;
		static const int MAX_S3_PARAM_CHARS = 1023;
		static const int MIN_PRIMARY_IDENTIFIER_CHARS = 1;
		static const int MAX_PRIMARY_IDENTIFIER_CHARS = 512;
		static const std::string PRIMARY_IDENTIFIER_REGEX = "[a-zA-Z0-9-_.]+";
		static const std::string PRIMARY_IDENTIFIER_REQUIREMENTS_TEXT = " must contain between "
			+ std::to_string(MIN_PRIMARY_IDENTIFIER_CHARS) + " and "
			+ std::to_string(MAX_PRIMARY_IDENTIFIER_CHARS) 
			+ " characters, and may only contain the characters \"a - z\" and \"A - Z\", the numbers \"0 - 9\", and symbols -_.]+";

		class GAMELIFT_API ValidationUtils
		{
		public:
			static std::string UrlEncode(const std::string& urlParameter);
			static std::string TruncateString(const std::string& str, const std::regex& pattern);
			static std::string TruncateAtLower(const std::string& str, const std::regex& pattern);
			static bool IsValidString(const std::string& str, const std::regex& pattern);
			static bool IsValidUrlParam(const std::string& urlParam);
			static bool IsValidS3KeyParam(const std::string& s3KeyParam);

			/**
			 * @brief Validates the given string as a primary identifier.
			 *
			 * @details A primary identifier is a string between 1 and 512 characters long, using alphanumeric characters, dashes (-),
			 * underscores (_), and periods (.). Primary identifiers are safe to use in path parameters without being encoded,
			 * DynamoDB partition and sort keys, and S3 object keys.
			 *
			 * @param identifier The identifier to validate.
			 * @returns True if the identifier is a valid primary identifier, false otherwise.
			 */
			static bool IsValidPrimaryIdentifier(const std::string& identifier);
		};
	}
}