// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once
// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string>

// AWS SDK
#include <aws/core/auth/AWSCredentials.h>
#include <aws/core/utils/json/JsonSerializer.h>

// GameLift
#include "errors.h"
#include "logging.h"

namespace GameLift
{
    class GameLiftFeature
    {
    protected:
        const char* m_featureName = nullptr;
        FuncLogCallback m_logCb = nullptr;
    public:
        GameLiftFeature() {};
        virtual ~GameLiftFeature() {};
    };
}
