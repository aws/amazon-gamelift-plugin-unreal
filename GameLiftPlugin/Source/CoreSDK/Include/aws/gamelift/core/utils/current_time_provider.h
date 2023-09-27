// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// AWS SDK
#include <aws/core/utils/DateTime.h>

// GameLift
#include <aws/gamelift/core/api.h>

namespace GameLift
{
    namespace Utils
    {
        /**
         * This class provides a wrapper over the static functions in Aws::Utils::DateTime to enable these functions to be mocked with GTest.
         *
         * See: https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_utils_1_1_date_time.html
         * See: http://google.github.io/googletest/gmock_cook_book.html#mocking-free-functions
         */
        class GAMELIFT_API ICurrentTimeProvider
        {
        public:
            ICurrentTimeProvider() {}
            virtual ~ICurrentTimeProvider() {}

            /**
             * Get the number of milliseconds since epoch representing this very instant.
             */
            virtual int64_t GetCurrentTimeMilliseconds() const = 0;
        };

        /**
         * Implementation that directly calls the corresponding static methods in Aws::Utils::DateTime:
         * https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_utils_1_1_date_time.html
         */
        class GAMELIFT_API AwsCurrentTimeProvider : public ICurrentTimeProvider
        {
        public:

            int64_t GetCurrentTimeMilliseconds() const override
            {
                return Aws::Utils::DateTime::CurrentTimeMillis();
            }
        };
    }
}