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

#include <aws/gamelift/internal/GameLiftCommonState.h>
#include <aws/gamelift/internal/network/GameLiftWebSocketClientManager.h>
#include <aws/gamelift/internal/network/IGameLiftMessageHandler.h>
#include <aws/gamelift/internal/network/IWebSocketClientWrapper.h>
#include <aws/gamelift/internal/network/callback/CreateGameSessionCallback.h>
#include <aws/gamelift/internal/network/callback/DescribePlayerSessionsCallback.h>
#include <aws/gamelift/internal/network/callback/GetComputeCertificateCallback.h>
#include <aws/gamelift/internal/network/callback/GetFleetRoleCredentialsCallback.h>
#include <aws/gamelift/internal/network/callback/RefreshConnectionCallback.h>
#include <aws/gamelift/internal/network/callback/StartMatchBackfillCallback.h>
#include <aws/gamelift/internal/network/callback/TerminateProcessCallback.h>
#include <aws/gamelift/internal/network/callback/UpdateGameSessionCallback.h>
#include <aws/gamelift/server/GameLiftServerAPI.h>
#include <aws/gamelift/server/model/ServerParameters.h>
#include <aws/gamelift/server/model/StartMatchBackfillRequest.h>
#include <aws/gamelift/server/model/StopMatchBackfillRequest.h>
#include <aws/gamelift/server/model/UpdateGameSession.h>
#include <condition_variable>
#include <mutex>

namespace Aws {
namespace GameLift {
namespace Internal {
using namespace Aws::GameLift::Server::Model;

#ifndef GAMELIFT_USE_STD
typedef Outcome<GameLiftServerState *, GameLiftError> InitSDKOutcome;
#endif

class GameLiftServerState : public GameLiftCommonState, public IGameLiftMessageHandler {
public:
    static constexpr const char *LANGUAGE = "Cpp";

private:
    static constexpr const char *ENV_VAR_WEBSOCKET_URL = "GAMELIFT_SDK_WEBSOCKET_URL";
    static constexpr const char *ENV_VAR_COMPUTE_TYPE = "GAMELIFT_COMPUTE_TYPE";
    static constexpr const char *ENV_VAR_AUTH_TOKEN = "GAMELIFT_SDK_AUTH_TOKEN";
    static constexpr const char *ENV_VAR_PROCESS_ID = "GAMELIFT_SDK_PROCESS_ID";
    static constexpr const char *ENV_VAR_HOST_ID = "GAMELIFT_SDK_HOST_ID";
    static constexpr const char *ENV_VAR_FLEET_ID = "GAMELIFT_SDK_FLEET_ID";
    static constexpr const char *ENV_VAR_AWS_REGION = "GAMELIFT_REGION";
    static constexpr const char *ENV_VAR_ACCESS_KEY = "GAMELIFT_ACCESS_KEY";
    static constexpr const char *ENV_VAR_SECRET_KEY = "GAMELIFT_SECRET_KEY";
    static constexpr const char *ENV_VAR_SESSION_TOKEN = "GAMELIFT_SESSION_TOKEN";
    static constexpr const char *COMPUTE_TYPE_CONTAINER = "CONTAINER";
    static constexpr const char *AGENTLESS_CONTAINER_PROCESS_ID = "ManagedResource";

    static constexpr const int HEALTHCHECK_INTERVAL_MILLIS = 60 * 1000;
    static constexpr const int HEALTHCHECK_MAX_JITTER_MILLIS = 10 * 1000;
    static constexpr const int HEALTHCHECK_TIMEOUT_MILLIS = HEALTHCHECK_INTERVAL_MILLIS - HEALTHCHECK_MAX_JITTER_MILLIS;

    void GetOverrideParams(char **webSocketUrl,
                           char **authToken,
                           char **processId,
                           char **hostId,
                           char **fleetId,
                           char **computeType,
                           char **awsRegion,
                           char **accessKey,
                           char **secretKey,
                           char **sessionToken);
    Outcome<std::map<std::string, std::string>, std::string> GetSigV4QueryParameters(char *awsRegion,
                           char *accessKey,
                           char *secretKey,
                           char *sessionToken);
    void ReportHealth();
    void HealthCheck();
    int GetNextHealthCheckIntervalMillis();

#ifdef GAMELIFT_USE_STD
public:
    static Server::InitSDKOutcome CreateInstance(std::shared_ptr<IWebSocketClientWrapper> webSocketClientWrapper);

    virtual GAMELIFT_INTERNAL_STATE_TYPE GetStateType() override { return GAMELIFT_INTERNAL_STATE_TYPE::SERVER; };

    // Singleton constructors should be private, but we are using a custom allocator that needs to
    // be able to see them. Don't use these.
    GameLiftServerState();

    ~GameLiftServerState();

    GenericOutcome ProcessReady(const Aws::GameLift::Server::ProcessParameters &processParameters);

    GenericOutcome ProcessEnding();

    GenericOutcome InitializeNetworking(const Aws::GameLift::Server::Model::ServerParameters &serverParameters);

    GenericOutcome SendSocketMessageWithRetries(Message &message);

    GenericOutcome ActivateGameSession();

    GenericOutcome UpdatePlayerSessionCreationPolicy(PlayerSessionCreationPolicy newPlayerSessionPolicy);

    std::string GetGameSessionId() const;

    long GetTerminationTime() const;

    GenericOutcome AcceptPlayerSession(const std::string &playerSessionId);

    GenericOutcome RemovePlayerSession(const std::string &playerSessionId);

    DescribePlayerSessionsOutcome DescribePlayerSessions(const Aws::GameLift::Server::Model::DescribePlayerSessionsRequest &describePlayerSessionsRequest);

    StartMatchBackfillOutcome StartMatchBackfill(const Aws::GameLift::Server::Model::StartMatchBackfillRequest &startMatchBackfillRequest);

    GenericOutcome StopMatchBackfill(const Aws::GameLift::Server::Model::StopMatchBackfillRequest &stopMatchBackfillRequest);

    GetComputeCertificateOutcome GetComputeCertificate();

    bool IsProcessReady() const { return m_processReady; }

    // From Network::AuxProxyMessageHandler
    void OnStartGameSession(GameSession &gameSession) override;
    void OnUpdateGameSession(UpdateGameSession &gameSession) override;
    void OnTerminateProcess(long terminationTime) override;
    void OnRefreshConnection(const std::string &refreshConnectionEndpoint, const std::string &authToken) override;

private:
    std::function<void(Aws::GameLift::Server::Model::GameSession)> m_onStartGameSession;
    std::function<void(Aws::GameLift::Server::Model::UpdateGameSession)> m_onUpdateGameSession;
    std::function<void()> m_onProcessTerminate;
    std::function<bool()> m_onHealthCheck;
#else
public:
    template <class WrapperT> static Internal::InitSDKOutcome CreateInstance() { return ConstructInternal(std::make_shared<WrapperT>()); }
    template <class WrapperT, class ClientT> static Internal::InitSDKOutcome CreateInstance() {
        return ConstructInternal(std::make_shared<WrapperT>(std::make_shared<ClientT>()));
    }

    std::shared_ptr<IWebSocketClientWrapper> GetWebSocketClientWrapper() const;

    virtual GAMELIFT_INTERNAL_STATE_TYPE GetStateType() override { return GAMELIFT_INTERNAL_STATE_TYPE::SERVER; };

    // Singleton constructors should be private, but we are using a custom allocator that needs to
    // be able to see them. Don't use these.
    GameLiftServerState();

    ~GameLiftServerState();

    GenericOutcome ProcessReady(const Aws::GameLift::Server::ProcessParameters &processParameters);

    GenericOutcome ProcessEnding();

    GenericOutcome InitializeNetworking(const Aws::GameLift::Server::Model::ServerParameters &ServerParameters);

    GenericOutcome SendSocketMessageWithRetries(Message &message);

    GenericOutcome ActivateGameSession();

    GenericOutcome UpdatePlayerSessionCreationPolicy(PlayerSessionCreationPolicy newPlayerSessionPolicy);

    const char *GetGameSessionId();

    long GetTerminationTime();

    GenericOutcome AcceptPlayerSession(const std::string &playerSessionId);

    GenericOutcome RemovePlayerSession(const std::string &playerSessionId);

    DescribePlayerSessionsOutcome DescribePlayerSessions(const Aws::GameLift::Server::Model::DescribePlayerSessionsRequest &describePlayerSessionsRequest);

    StartMatchBackfillOutcome StartMatchBackfill(const Aws::GameLift::Server::Model::StartMatchBackfillRequest &request);

    GenericOutcome StopMatchBackfill(const Aws::GameLift::Server::Model::StopMatchBackfillRequest &request);

    GetComputeCertificateOutcome GetComputeCertificate();

    bool IsProcessReady() { return m_processReady; }

    // From Network::AuxProxyMessageHandler
    void OnStartGameSession(GameSession &gameSession) override;
    void OnUpdateGameSession(UpdateGameSession &gameSession) override;
    void OnTerminateProcess(long terminationTime) override;
    void OnRefreshConnection(const std::string &refreshConnectionEndpoint, const std::string &authToken) override;

private:
    std::function<void(Aws::GameLift::Server::Model::GameSession, void *)> m_onStartGameSession;
    std::function<void(Aws::GameLift::Server::Model::UpdateGameSession, void *)> m_onUpdateGameSession;
    std::function<void(void *)> m_onProcessTerminate;
    std::function<bool(void *)> m_onHealthCheck;

    void *m_startGameSessionState;
    void *m_updateGameSessionState;
    void *m_processTerminateState;
    void *m_healthCheckState;

    void *startGameSessionState;
    void *processTerminateState;
    void *healthCheckState;
    static Internal::InitSDKOutcome ConstructInternal(std::shared_ptr<IWebSocketClientWrapper> webSocketClientWrapper);
#endif
public:
    GetFleetRoleCredentialsOutcome GetFleetRoleCredentials(const Aws::GameLift::Server::Model::GetFleetRoleCredentialsRequest &request);

    // When within 15 minutes of expiration we retrieve new instance role credentials
    static constexpr const time_t INSTANCE_ROLE_CREDENTIAL_TTL_MIN = 60 * 15;

private:
    bool AssertNetworkInitialized();
    void SetUpCallbacks();

    bool m_processReady;

    // Only one game session per process.
    std::string m_gameSessionId;

    long m_terminationTime;

    GameLiftWebSocketClientManager *m_webSocketClientManager;
    std::shared_ptr<IWebSocketClientWrapper> m_webSocketClientWrapper;

    // Callbacks
    std::unique_ptr<CreateGameSessionCallback> m_createGameSessionCallback;
    std::unique_ptr<DescribePlayerSessionsCallback> m_describePlayerSessionsCallback;
    std::unique_ptr<GetComputeCertificateCallback> m_getComputeCertificateCallback;
    std::unique_ptr<GetFleetRoleCredentialsCallback> m_getFleetRoleCredentialsCallback;
    std::unique_ptr<TerminateProcessCallback> m_terminateProcessCallback;
    std::unique_ptr<UpdateGameSessionCallback> m_updateGameSessionCallback;
    std::unique_ptr<StartMatchBackfillCallback> m_startMatchBackfillCallback;
    std::unique_ptr<RefreshConnectionCallback> m_refreshConnectionCallback;

    std::string m_connectionEndpoint;
    std::string m_authToken;
    std::string m_fleetId;
    std::string m_hostId;
    std::string m_processId;
    // Assume we're on managed EC2, if GetFleetRoleCredentials fails we know to set this to false
    bool m_onManagedEC2 = true;
    std::map<std::string, GetFleetRoleCredentialsResult> m_instanceRoleResultCache;

    std::unique_ptr<std::thread> m_healthCheckThread;
    std::condition_variable m_healthCheckConditionVariable;
    std::mutex m_healthCheckMutex;
    bool m_healthCheckInterrupted;
};

} // namespace Internal
} // namespace GameLift
} // namespace Aws
