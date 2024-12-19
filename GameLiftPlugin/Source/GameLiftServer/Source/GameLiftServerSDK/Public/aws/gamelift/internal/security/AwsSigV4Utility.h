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
#include <ctime>
#include <aws/gamelift/internal/security/SigV4Parameters.h>
#include <aws/gamelift/common/Outcome.h>

namespace Aws {
namespace GameLift {
namespace Internal {

class AwsSigV4Utility {
public:
    static Aws::GameLift::Outcome<std::map<std::string, std::string>, std::string> GenerateSigV4QueryParameters(const SigV4Parameters &parameters);

private:
    static void ValidateParameters(const SigV4Parameters &parameters);

    static std::string GenerateSignature(
            const std::string &region,
            const std::string &secretKey,
            const std::string &formattedRequestDateTime,
            const std::string &serviceName,
            const std::string &stringToSign);

    static std::map<std::string, std::string> GenerateSigV4QueryParameters(
            const std::string &credential,
            const std::string &formattedRequestDateTime,
            const std::string &sessionToken,
            const std::string &signature);

    static std::string ToSortedEncodedQueryString(const std::map <std::string, std::string> &queryParameters);

    /**
     * @brief This method uses OpenSSL EVP interface to compute the SHA-256 hash of the input string.
     *
     * References:
     * - AWS SigV4 Documentation: https://docs.aws.amazon.com/IAM/latest/UserGuide/create-signed-request.html
     * - OpenSSL: https://docs.openssl.org/3.1/man3/EVP_DigestInit/
     * - SHA-256: https://datatracker.ietf.org/doc/html/rfc4634
     *
     * @param data The input string to be hashed.
     * @return std::string The hexadecimal string representing the SHA-256 hash of the input.
     */
    static std::string ComputeSha256Hash(const std::string &data);

    /**
     * @brief This method uses OpenSSL EVP_MAC interface to compute the HMAC (Hash-based Message Authentication Code) using the SHA-256 algorithm.
     *
     * References:
     * - AWS SigV4: Documentation: https://docs.aws.amazon.com/IAM/latest/UserGuide/create-signed-request.html
     * - OpenSSL: https://docs.openssl.org/3.1/man3/EVP_DigestInit/
     * - HMAC: https://datatracker.ietf.org/doc/html/rfc2104
     * - SHA-256: https://datatracker.ietf.org/doc/html/rfc4634
     *
     * @param key The secret key used for the HMAC operation.
     * @param data The input data to be authenticated.
     * @return std::vector<uint8_t> The computed HMAC-SHA256 as a byte vector.
     */
    static std::vector <uint8_t> ComputeHmacSha256(const std::vector <uint8_t> &key, const std::string &data);

    static std::string ToHex(const std::vector <uint8_t> &hashBytes);

    static constexpr const char *DateFormat = "%Y%m%d";
    static constexpr const char *DateTimeFormat = "%Y%m%dT%H%M%SZ";
    static constexpr const char *ServiceName = "gamelift";
    static constexpr const char *TerminationString = "aws4_request";
    static constexpr const char *SignatureSecretKeyPrefix = "AWS4";
    static constexpr const char *Algorithm = "AWS4-HMAC-SHA256";
    static constexpr const char *AuthorizationKey = "Authorization";
    static constexpr const char *AuthorizationValue = "SigV4";
    static constexpr const char *AmzAlgorithmKey = "X-Amz-Algorithm";
    static constexpr const char *AmzCredentialKey = "X-Amz-Credential";
    static constexpr const char *AmzDateKey = "X-Amz-Date";
    static constexpr const char *AmzSecurityTokenHeadersKey = "X-Amz-Security-Token";
    static constexpr const char *AmzSignatureKey = "X-Amz-Signature";
};
} // namespace Internal
} // namespace GameLift
} // namespace Aws
