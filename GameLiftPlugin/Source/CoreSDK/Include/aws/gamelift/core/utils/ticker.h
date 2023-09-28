// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <functional>
#include <chrono>
#include <future>
#include <cstdio>

// GameLift
#include <aws/gamelift/core/api.h>
#include <aws/gamelift/core/logging.h>

namespace GameLift
{
    namespace Utils
    {
        /**
        * @brief Utility class that calls a function in its own background thread at defined intervals.
        */
        class GAMELIFT_API Ticker
        {
        private:
            static const int TICKER_PULSE = 250;

            std::mutex m_tickerMutex;
            std::condition_variable m_completedVar;
            std::thread::id m_threadId;
            std::thread m_funcThread;
            int m_interval = 0;
            std::function<void()> m_tickFunc;
            FuncLogCallback m_logCb;
            bool m_isRunning;
            bool m_aborted;
            bool m_isCompleted;

        public:
            /**
            * @brief Create a new instance of this class.
            * @param interval The interval in seconds.
            * @param tickFunc The function to call.
            * @param logCb The log callback function.
            */
            Ticker(int interval, std::function<void()> tickFunc, FuncLogCallback logCb);

            /**
            * 
            */
            ~Ticker();

            /**
            * @brief Start the ticker loop in a background thread.
            */
            void Start();

            /**
            * @brief Stop the ticker.
            */
            void Stop();

            /**
            * @brief Get the running state of the ticker loop.
            * @return True if the ticker is running, false otherwise.
            */
            bool IsRunning() const;

            /**
            * @brief Abort the loop. This should be called inside the tick function.
            */
            void AbortLoop();

            /**
            * @brief Rechedule the loop to a new intertval. This should be called inside the tick function.
            * @param newInterval The new interval in seconds.
            */
            void RescheduleLoop(int newInterval);
        };

    }
}
