// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <string>
#include <sstream>
#include <thread>

// GameLift
#include "api.h"

extern "C"
{
    typedef void(*FuncLogCallback)(unsigned int level, const char* message, int size);
}

namespace GameLift
{
    namespace Logger
    {
        enum Level : unsigned int
        {
            None = 0,
            Verbose = 1,
            Info = 2,
            Warning = 3,
            Error = 4
        };

        class GAMELIFT_API Logging
        {
        public:
            static void Log(FuncLogCallback cb, Level level, const char* message);
            static void Log(FuncLogCallback cb, Level level, const char* message, const void* context);
        };
    }
}
