// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <algorithm>
#include <string>
#include <deque>
#include <map>
#include <chrono>
#include <sstream>
#include <iostream>

// AWS SDK
#include <aws/core/http/HttpClient.h>
#include <aws/core/http/HttpRequest.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/core/utils/StringUtils.h>

// GameLift
#include <aws/gamelift/core/awsclients/api_initializer.h>
#include <aws/gamelift/core/awsclients/default_clients.h>
#include <aws/gamelift/core/errors.h>
#include <aws/gamelift/core/logging.h>
#include <aws/gamelift/core/utils/ticker.h>

using namespace GameLift::Logger;

#define OPERATION_ATTEMPTS_NO_LIMIT 0

namespace GameLift
{
    namespace Utils
    {
        namespace Serialization
        {
            template <typename T, size_t N>
            GAMELIFT_API std::ostream& BinWrite(std::ostream& os, const T (&t)[N])
            {
                size_t length = N;
                os.write((char*)&length, sizeof(size_t));
                os.write((char*)t, N);

                return os;
            }

            template <typename T>
            GAMELIFT_API std::ostream& BinWrite(std::ostream& os, const T& t)
            {
                os.write((char*)&t, sizeof(T));

                return os;
            }

            template <>
            GAMELIFT_API std::ostream& BinWrite<std::string>(std::ostream& os, const std::string& s);

            template <typename T>
            GAMELIFT_API std::istream& BinRead(std::istream& is, T& t)
            {
                is.read((char*)&t, sizeof(T));

                return is;
            }

            template <>
            GAMELIFT_API std::istream& BinRead<std::string>(std::istream& is, std::string& s);

            GAMELIFT_API unsigned int GetCRC(const std::string& s);

            GAMELIFT_API unsigned int GetCRC(const char* s, size_t length);
        }

        namespace HttpClient
        {
            typedef void* NETWORK_STATE_RECEIVER_HANDLE;
            typedef void(*NetworkStatusChangeCallback)(NETWORK_STATE_RECEIVER_HANDLE dispatchReceiver, bool isConnectionOk, const char* connectionClient);
            typedef void* CACHE_PROCESSED_RECEIVER_HANDLE;
            typedef void(*CacheProcessedCallback)(CACHE_PROCESSED_RECEIVER_HANDLE dispatchReceiver, bool isCacheProcessed);

            // Wildcard object for response callback context
            typedef void* CallbackContext;

            // Callback to be called when a request has received a response.
            typedef std::function<void(CallbackContext requestContext, std::shared_ptr<Aws::Http::HttpResponse>)> ResponseCallback;

            // Callback to be called before sending a request. Used to update/modify request headers such as authorization.
            typedef std::function<void(std::shared_ptr<Aws::Http::HttpRequest>)> RequestModifier;

            GAMELIFT_API bool TrySerializeRequestBinary(std::ostream& os, const std::shared_ptr<Aws::Http::HttpRequest> request, FuncLogCallback logCb = nullptr);
            GAMELIFT_API bool TryDeserializeRequestBinary(std::istream& is, std::shared_ptr<Aws::Http::HttpRequest>& outRequest, FuncLogCallback logCb = nullptr);

            // Base struct for retryable client operations
            struct GAMELIFT_API IOperation
            {
                const std::chrono::milliseconds Timestamp;
                unsigned int Attempts;
                const unsigned int MaxAttempts;
                bool Discard;
                bool FromCache = false;

                std::shared_ptr<Aws::Http::HttpRequest> Request;
                const Aws::Http::HttpResponseCode ExpectedSuccessCode;
                
                CallbackContext CallbackContext;
                ResponseCallback SuccessCallback;
                ResponseCallback FailureCallback;

                IOperation(unsigned int maxAttempts, 
                    bool discard, 
                    std::shared_ptr<Aws::Http::HttpRequest> request, 
                    const Aws::Http::HttpResponseCode expectedCode, 
                    std::chrono::milliseconds timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()))
                    : Attempts(0), 
                    MaxAttempts(maxAttempts), 
                    Discard(discard), 
                    Request(request), 
                    ExpectedSuccessCode(expectedCode), 
                    CallbackContext(nullptr), 
                    SuccessCallback(nullptr), 
                    FailureCallback(nullptr),
                    Timestamp(timestamp)
                {}
            };

            typedef std::deque<std::shared_ptr<IOperation>> OperationQueue;

            // Types of request results
            enum class RequestResultType
            {
                RequestMadeSuccess = 0,
                RequestMadeFailure,
                RequestDropped,
                RequestEnqueued,
                RequestAttemptedAndEnqueued
            };

            std::string GAMELIFT_API RequestResultTypeToString(RequestResultType resultType);

            // Result of a client request
            struct GAMELIFT_API RequestResult
            {
                RequestResult(RequestResultType type, std::shared_ptr<Aws::Http::HttpResponse> response)
                    : ResultType(type), Response(response)
                {}

                RequestResultType ResultType;
                std::shared_ptr<Aws::Http::HttpResponse> Response;

                std::string ToString() const;

                unsigned int ToErrorCode() const;
            };

            // Base interface for retry strategies
            class GAMELIFT_API IRetryStrategy
            {
            public:
                IRetryStrategy() {}
                virtual ~IRetryStrategy() {}

                virtual void IncreaseCounter() = 0;
                virtual bool ShouldRetry() = 0;
                virtual void Reset() = 0;
            };

            // Constant Interval Strategy. With this strategy, operations are always retried in each interval.
            class GAMELIFT_API ConstantIntervalStrategy : public IRetryStrategy
            {
            public:
                ConstantIntervalStrategy() {}
                virtual ~ConstantIntervalStrategy() {}

                virtual void IncreaseCounter() override { /* No-op by design */ };
                virtual bool ShouldRetry() override { /* Always true by design */  return true; };
                virtual void Reset() override { /* No-op by design */ };
            };

            // Binary Exponential Backoff Strategy. With this strategy, retries are spaced out at exponential intervals.
            class GAMELIFT_API ExponentialBackoffStrategy : public IRetryStrategy
            {
            private:
                unsigned int counter;
                unsigned int maxAttempts;
                unsigned int currentStep;
                unsigned int retryThreshold;
                FuncLogCallback logCb = nullptr;

            public:
                ExponentialBackoffStrategy(unsigned int maxAttempts, FuncLogCallback logCb = nullptr);
                virtual ~ExponentialBackoffStrategy();

                virtual void IncreaseCounter() override;
                virtual bool ShouldRetry() override;
                virtual void Reset() override;
            };

            enum class StrategyType
            {
                ExponentialBackoff = 0,
                ConstantInterval
            };
        }
    }
}
