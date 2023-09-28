// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <algorithm>
#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

// AWS SDK
#include <aws/core/http/HttpClient.h>
#include <aws/core/http/HttpRequest.h>
#include <aws/core/http/HttpResponse.h>

// GameLift
#include <aws/gamelift/core/errors.h>
#include <aws/gamelift/core/logging.h>
#include <aws/gamelift/core/awsclients/api_initializer.h>
#include <aws/gamelift/core/awsclients/default_clients.h>
#include <aws/gamelift/core/utils/gamelift_httpclient_types.h>
#include <aws/gamelift/core/utils/ticker.h>

using namespace GameLift::Logger;

#define OPERATION_ATTEMPTS_NO_LIMIT 0

namespace GameLift
{
    namespace Utils
    {
        namespace HttpClient
        {
            // Base Http Client with retry capability with an internal request queue.
            class GAMELIFT_API BaseHttpClient
            {
            private:
                std::string m_clientName;
                bool m_isConnectionOk;
                size_t m_maxPendingQueueSize;
                unsigned int m_attempsCount;
                unsigned int m_secondsInterval;
                GameLift::Utils::Ticker m_requestPump;
                bool m_abortProcessingRequested;
                std::shared_ptr<Aws::Http::HttpClient> m_httpClient;
                std::shared_ptr<IRetryStrategy> m_retryStrategy;
                OperationQueue m_activeQueue; // this queue is only r/w in the background thread
                OperationQueue m_pendingQueue; // this queue is always r/w under mutex
                std::mutex m_processMutex;
                NETWORK_STATE_RECEIVER_HANDLE m_stateReceiverHandle;
                NetworkStatusChangeCallback m_statusCb;
                CACHE_PROCESSED_RECEIVER_HANDLE m_cachedProcessedReceiverHandle;
                CacheProcessedCallback m_cachedProcessedCb;

                bool enqueuePending(std::shared_ptr<IOperation> operation);
                void preProcessQueue();
                void processActiveQueue();

            protected:
                FuncLogCallback m_logCb = nullptr;
                RequestModifier m_authorizationHeaderSetter;
                bool m_stopProcessingOnError;
                bool m_errorDuringProcessing;

                size_t m_cachedOperationsRemaining = 0;
                bool m_skipCacheProcessedCallback = false;

                void notifyNetworkStateChange() const;
                void notifyCachedOperationsProcessed(bool cacheProcessingSucceeded) const;
                void setStopProcessingOnError(bool stopProcessingOnError);

                // Determine whether an operation is retryable based on its properties and the response
                virtual bool isOperationRetryable(const std::shared_ptr<IOperation> operation, std::shared_ptr<const Aws::Http::HttpResponse> response) const = 0;

                // Determine whether an operation should be enqueued when the client is in Unhealthy mode
                virtual bool shouldEnqueueWithUnhealthyConnection(const std::shared_ptr<IOperation> operation) const = 0;

                // Logic to filter the internal queue before operations are processed.
                // Precondition: queue has items, filtered is empty.
                // Postcondition: filtered has items to keep.
                virtual void filterQueue(OperationQueue* queue, OperationQueue* filtered) = 0;

                void removeCachedFromQueue(OperationQueue* queue, OperationQueue* filtered) const;

                static bool isResponseCodeRetryable(Aws::Http::HttpResponseCode responseCode);

                bool isPendingQueueBelowLimit() const;

                // Sends a request for the given operation and enqueues it for retry in case of failure. 
                // In case the client has lost connectivity, events are enqueued for later retry.
                RequestResult makeOperationRequest(std::shared_ptr<IOperation> operation, bool isAsyncOperation, bool overrideConnectionStatus);

            public:
                BaseHttpClient(const std::string& clientName, std::shared_ptr<Aws::Http::HttpClient> client, RequestModifier authSetter, unsigned int retryIntervalSeconds, std::shared_ptr<IRetryStrategy> retryStrategy, size_t maxPendingQueueSize, FuncLogCallback logCb);
                virtual ~BaseHttpClient();

                void SetNetworkChangeCallback(NETWORK_STATE_RECEIVER_HANDLE receiverHandle, NetworkStatusChangeCallback statusChangeCallback);
                void SetCacheProcessedCallback(CACHE_PROCESSED_RECEIVER_HANDLE receiverHandle, CacheProcessedCallback cacheProcessedCallback);
                void StartRetryBackgroundThread();
                void StopRetryBackgroundThread();

                // PersistQueue should be among the last methods to be called in a client. This is to ensure that all data that a player has in the queue has been saved to the cache.
                bool PersistQueue(const std::string& file, std::function<bool(std::ostream&, const std::shared_ptr<IOperation>, FuncLogCallback)> serializer, bool clearQueue = true);

                // LoadQueue should be among the first methods to be called in a client. This is to ensure the cache has been read into the queue so they can be processed for the player.
                bool LoadQueue(const std::string& file, std::function<bool(std::istream&, std::shared_ptr<IOperation>&, FuncLogCallback)> deserializer, bool clearFile = true);

                // Helper to clear the offline cache from the queues, there is no need to clear the local file.
                // LoadQueue moves all cached operations from the local file to the queue and clears the local file.
                void DropAllCachedEvents();

                // Set the low level HTTP Client. Use only for testing.
                void SetLowLevelHttpClient(std::shared_ptr<Aws::Http::HttpClient> client);
            };
        }
    }
}
