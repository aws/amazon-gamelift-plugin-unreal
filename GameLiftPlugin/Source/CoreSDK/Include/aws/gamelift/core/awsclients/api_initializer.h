// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once
// Standard Library
#include <memory>
#include <mutex>

// GameLift
#include <aws/gamelift/core/api.h>
#include <aws/gamelift/core/logging.h>

// Forward declarations
namespace Aws { struct SDKOptions; }

namespace GameLift
{
    // This singleton class helps ensure that the AWS SDK InitAPI and ShutdownAPI methods are only called once
    class GAMELIFT_API AwsApiInitializer
    {
    private:
        static std::mutex m_mutex;
        static bool m_isAwsSdkInitialized;
        static std::unique_ptr<Aws::SDKOptions> m_awsSdkOptions;
        static int m_count;

    public:
        // Calls Aws::InitAPI()
        static void Initialize(FuncLogCallback log = nullptr, const void* caller = nullptr);

        // Calls Aws::ShutdownAPI()
        static void Shutdown(FuncLogCallback log = nullptr, const void* caller = nullptr);

        static bool IsInitialized();
    };
}
