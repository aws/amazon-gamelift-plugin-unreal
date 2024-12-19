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

#if defined(_MSC_VER) && !defined(GAMELIFT_USE_STD)
#pragma warning(push)           // Save warning settings.
#pragma warning(disable : 4996) // Disable deprecated warning for strncpy
#endif

#include <aws/gamelift/common/GameLift_EXPORTS.h>
#ifndef GAMELIFT_USE_STD
#include "string.h"
#endif

namespace Aws {
namespace GameLift {
enum class AWS_GAMELIFT_API GAMELIFT_ERROR_TYPE {
    ALREADY_INITIALIZED,             // The GameLift Server or Client has already been initialized with
                                     // Initialize().
    FLEET_MISMATCH,                  // The target fleet does not match the fleet of a gameSession or playerSession.
    GAMELIFT_CLIENT_NOT_INITIALIZED, // The GameLift client has not been initialized.
    GAMELIFT_SERVER_NOT_INITIALIZED, // The GameLift server has not been initialized.
    GAME_SESSION_ENDED_FAILED,       // The GameLift Server SDK could not contact the service to report
                                     // the game session ended.
    GAME_SESSION_NOT_READY,          // The GameLift Server Game Session was not activated.
    GAME_SESSION_READY_FAILED,       // The GameLift Server SDK could not contact the service to report
                                     // the game session is ready.
    GAME_SESSION_ID_NOT_SET,         // No game sessions are bound to this process.
    INITIALIZATION_MISMATCH,         // A client method was called after Server::Initialize(), or vice
                                     // versa.
    NOT_INITIALIZED,                 // The GameLift Server or Client has not been initialized with Initialize().
    NO_TARGET_ALIASID_SET,           // A target aliasId has not been set.
    NO_TARGET_FLEET_SET,             // A target fleet has not been set.
    PROCESS_ENDING_FAILED,           // The GameLift Server SDK could not contact the service to report the
                                     // process is ending.
    PROCESS_NOT_ACTIVE,              // The server process is not yet active, not bound to a GameSession, and
                                     // cannot accept or process PlayerSessions.
    PROCESS_NOT_READY,               // The server process is not yet ready to be activated.
    PROCESS_READY_FAILED,            // The GameLift Server SDK could not contact the service to report the
                                     // process is ready.
    SDK_VERSION_DETECTION_FAILED,    // SDK version detection failed.
    SERVICE_CALL_FAILED,             // A call to an AWS service has failed.
    STX_CALL_FAILED,                 // A call to the XStx server backend component has failed.
    STX_INITIALIZATION_FAILED,       // The XStx server backend component has failed to initialize.
    UNEXPECTED_PLAYER_SESSION,       // An unregistered player session was encountered by the server.
    BAD_REQUEST_EXCEPTION,
    INTERNAL_SERVICE_EXCEPTION,
    WEBSOCKET_CONNECT_FAILURE,                // Failure to connect to the GameLift Service WebSocket
    WEBSOCKET_CONNECT_FAILURE_FORBIDDEN,      // Access denied, e.g. auth token has expired
    WEBSOCKET_CONNECT_FAILURE_INVALID_URL,    // End point URL is invalid
    WEBSOCKET_CONNECT_FAILURE_TIMEOUT,        // Timeout
    WEBSOCKET_RETRIABLE_SEND_MESSAGE_FAILURE, // Retriable failure to send message to the GameLift
                                              // Service WebSocket
    WEBSOCKET_SEND_MESSAGE_FAILURE            // Failure to send message to the GameLift Service WebSocket

};

class AWS_GAMELIFT_API GameLiftError {
#ifdef GAMELIFT_USE_STD
public:
    GAMELIFT_ERROR_TYPE GetErrorType() const { return m_errorType; }

    const std::string &GetErrorName() const { return m_errorName; }
    void SetErrorName(const std::string &errorName) { m_errorName = errorName; }

    const std::string &GetErrorMessage() const { return m_errorMessage; }
    void SetErrorMessage(const std::string &errorMessage) { m_errorMessage = errorMessage; }

    GameLiftError() : m_errorType(){};

    ~GameLiftError(){};

    GameLiftError(const int statusCode, const std::string &message) : GameLiftError(GetErrorTypeForStatusCode(statusCode), message){};

    GameLiftError(GAMELIFT_ERROR_TYPE errorType)
        : m_errorType(errorType), m_errorName(Aws::GameLift::GameLiftError::GetDefaultNameForErrorType(errorType)),
          m_errorMessage(Aws::GameLift::GameLiftError::GetDefaultMessageForErrorType(errorType)){};

    GameLiftError(GAMELIFT_ERROR_TYPE errorType, const std::string &errorName, const std::string &message)
        : m_errorType(errorType), m_errorName(errorName), m_errorMessage(message){};

    GameLiftError(GAMELIFT_ERROR_TYPE errorType, const std::string &message)
        : m_errorType(errorType), m_errorName(Aws::GameLift::GameLiftError::GetDefaultNameForErrorType(errorType)), m_errorMessage(message){};

    GameLiftError(const GameLiftError &rhs) : m_errorType(rhs.GetErrorType()), m_errorName(rhs.GetErrorName()), m_errorMessage(rhs.GetErrorMessage()){};

    bool operator==(const GameLiftError other) const {
        return other.GetErrorType() == GetErrorType() && other.GetErrorName() == GetErrorName() && other.GetErrorMessage() == GetErrorMessage();
    }

private:
    GAMELIFT_ERROR_TYPE m_errorType;
    std::string m_errorName;
    std::string m_errorMessage;
#else
public:
    const GAMELIFT_ERROR_TYPE GetErrorType() const { return m_errorType; }

    const char *GetErrorName() const { return m_errorName; }
    void SetErrorName(const char *errorName) {
        strncpy(m_errorName, errorName, sizeof(m_errorName));
        m_errorName[sizeof(m_errorName) - 1] = 0;
    }

    const char *GetErrorMessage() const { return m_errorMessage; }
    void SetErrorMessage(const char *errorMessage) {
        strncpy(m_errorMessage, errorMessage, sizeof(m_errorMessage));
        m_errorMessage[sizeof(m_errorMessage) - 1] = 0;
    }

    GameLiftError() {
        memset(m_errorName, 0, sizeof(m_errorName));
        memset(m_errorMessage, 0, sizeof(m_errorMessage));
    };

    ~GameLiftError(){};

    GameLiftError(const int statusCode, const char *message) : GameLiftError(GetErrorTypeForStatusCode(statusCode), message){};

    void Init(GAMELIFT_ERROR_TYPE errorType, const char *errorName, const char *message) {
        m_errorType = errorType;
        SetErrorName(errorName);
        SetErrorMessage(message);
    };

    GameLiftError(GAMELIFT_ERROR_TYPE errorType) {
        Init(errorType, Aws::GameLift::GameLiftError::GetDefaultNameForErrorType(errorType).c_str(),
             Aws::GameLift::GameLiftError::GetDefaultMessageForErrorType(errorType).c_str());
    };

    GameLiftError(GAMELIFT_ERROR_TYPE errorType, const char *errorName, const char *message) : m_errorType(errorType) {
        this->SetErrorName(errorName);
        this->SetErrorMessage(message);
    };

    GameLiftError(GAMELIFT_ERROR_TYPE errorType, const char *message) {
        Init(errorType, Aws::GameLift::GameLiftError::GetDefaultNameForErrorType(errorType).c_str(), message);
    };

    GameLiftError(const GameLiftError &rhs) { Init(rhs.GetErrorType(), rhs.GetErrorName(), rhs.GetErrorMessage()); };

    bool operator==(const GameLiftError other) const {
        return other.GetErrorType() == GetErrorType() && strcmp(other.GetErrorName(), GetErrorName()) == 0 &&
               strcmp(other.GetErrorMessage(), GetErrorMessage()) == 0;
    }

private:
    GAMELIFT_ERROR_TYPE m_errorType;
    char m_errorName[256];
    char m_errorMessage[1024];
#endif
    static GAMELIFT_ERROR_TYPE GetErrorTypeForStatusCode(const int statusCode) {
        if (statusCode >= 400 && statusCode < 500) {
            // Map all 4xx requests to bad request exception. We don't have an error type for all
            // 100 client errors
            return GAMELIFT_ERROR_TYPE::BAD_REQUEST_EXCEPTION;
        } else {
            // The websocket can return other error types, in this case classify it as an internal
            // service exception
            return GAMELIFT_ERROR_TYPE::INTERNAL_SERVICE_EXCEPTION;
        }
    }

    static std::string GetDefaultNameForErrorType(GAMELIFT_ERROR_TYPE errorType) {
        switch (errorType) {
            case GAMELIFT_ERROR_TYPE::ALREADY_INITIALIZED:
                return "Already Initialized";
            case GAMELIFT_ERROR_TYPE::FLEET_MISMATCH:
                return "Fleet mismatch.";
            case GAMELIFT_ERROR_TYPE::GAMELIFT_CLIENT_NOT_INITIALIZED:
                return "GameLift client not initialized.";
            case GAMELIFT_ERROR_TYPE::GAMELIFT_SERVER_NOT_INITIALIZED:
                return "GameLift server not initialized.";
            case GAMELIFT_ERROR_TYPE::GAME_SESSION_ENDED_FAILED:
                return "Game session failed.";
            case GAMELIFT_ERROR_TYPE::GAME_SESSION_NOT_READY:
                return "Game session not activated.";
            case GAMELIFT_ERROR_TYPE::GAME_SESSION_READY_FAILED:
                return "Game session failed.";
            case GAMELIFT_ERROR_TYPE::GAME_SESSION_ID_NOT_SET:
                return "GameSession id is not set.";
            case GAMELIFT_ERROR_TYPE::INITIALIZATION_MISMATCH:
                return "Initialization mismatch.";
            case GAMELIFT_ERROR_TYPE::NOT_INITIALIZED:
                return "Not Initialized";
            case GAMELIFT_ERROR_TYPE::NO_TARGET_ALIASID_SET:
                return "No target aliasId set.";
            case GAMELIFT_ERROR_TYPE::NO_TARGET_FLEET_SET:
                return "No target fleet set.";
            case GAMELIFT_ERROR_TYPE::PROCESS_ENDING_FAILED:
                return "Process ending failed.";
            case GAMELIFT_ERROR_TYPE::PROCESS_NOT_ACTIVE:
                return "Process not activated.";
            case GAMELIFT_ERROR_TYPE::PROCESS_NOT_READY:
                return "Process not ready.";
            case GAMELIFT_ERROR_TYPE::PROCESS_READY_FAILED:
                return "Process ready failed.";
            case GAMELIFT_ERROR_TYPE::SDK_VERSION_DETECTION_FAILED:
                return "Could not detect SDK version.";
            case GAMELIFT_ERROR_TYPE::SERVICE_CALL_FAILED:
                return "Service call failed.";
            case GAMELIFT_ERROR_TYPE::STX_CALL_FAILED:
                return "STX call failed.";
            case GAMELIFT_ERROR_TYPE::STX_INITIALIZATION_FAILED:
                return "STX Initialization Failed.";
            case GAMELIFT_ERROR_TYPE::UNEXPECTED_PLAYER_SESSION:
                return "Unexpected player session.";
            case GAMELIFT_ERROR_TYPE::BAD_REQUEST_EXCEPTION:
                return "Bad request exception.";
            case GAMELIFT_ERROR_TYPE::INTERNAL_SERVICE_EXCEPTION:
                return "Internal service exception.";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_CONNECT_FAILURE:
                return "WebSocket Connection Failed.";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_CONNECT_FAILURE_FORBIDDEN:
                return "WebSocket Connection Denied.";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_CONNECT_FAILURE_INVALID_URL:
                return "WebSocket Connection has invalid URL.";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_CONNECT_FAILURE_TIMEOUT:
                return "WebSocket Connection has timed out.";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_SEND_MESSAGE_FAILURE:
                return "WebSocket Send Message Failed.";
            default:
                return "Unknown Error";
        }
    }

    static std::string GetDefaultMessageForErrorType(GAMELIFT_ERROR_TYPE errorType) {
        switch (errorType) {
            case GAMELIFT_ERROR_TYPE::ALREADY_INITIALIZED:
                return "GameLift has already been initialized. You must call Destroy() before "
                       "reinitializing the client or server.";
            case GAMELIFT_ERROR_TYPE::FLEET_MISMATCH:
                return "The Target fleet does not match the request fleet. Make sure GameSessions and "
                       "PlayerSessions belong to your target fleet.";
            case GAMELIFT_ERROR_TYPE::GAMELIFT_CLIENT_NOT_INITIALIZED:
                return "The GameLift client has not been initialized. Please call SetTargetFleet or "
                       "SetTArgetAliasId.";
            case GAMELIFT_ERROR_TYPE::GAMELIFT_SERVER_NOT_INITIALIZED:
                return "The GameLift server has not been initialized. Please call InitSDK.";
            case GAMELIFT_ERROR_TYPE::GAME_SESSION_ENDED_FAILED:
                return "The GameSessionEnded invocation failed.";
            case GAMELIFT_ERROR_TYPE::GAME_SESSION_NOT_READY:
                return "The Game session associated with this server was not activated.";
            case GAMELIFT_ERROR_TYPE::GAME_SESSION_READY_FAILED:
                return "The GameSessionReady invocation failed.";
            case GAMELIFT_ERROR_TYPE::GAME_SESSION_ID_NOT_SET:
                return "No game sessions are bound to this process.";
            case GAMELIFT_ERROR_TYPE::INITIALIZATION_MISMATCH:
                return "The current call does not match the initialization state. Client calls require "
                       "a call to Client::Initialize(), and Server calls require Server::Initialize(). "
                       "Only one may be active at a time.";
            case GAMELIFT_ERROR_TYPE::NOT_INITIALIZED:
                return "GameLift has not been initialized! You must call Client::Initialize() or "
                       "Server::InitSDK() before making GameLift calls.";
            case GAMELIFT_ERROR_TYPE::NO_TARGET_ALIASID_SET:
                return "The aliasId has not been set. Clients should call SetTargetAliasId() before "
                       "making calls that require an alias.";
            case GAMELIFT_ERROR_TYPE::NO_TARGET_FLEET_SET:
                return "The target fleet has not been set. Clients should call SetTargetFleet() before "
                       "making calls that require a fleet.";
            case GAMELIFT_ERROR_TYPE::PROCESS_ENDING_FAILED:
                return "ProcessEnding call to GameLift failed.";
            case GAMELIFT_ERROR_TYPE::PROCESS_NOT_ACTIVE:
                return "The process has not yet been activated.";
            case GAMELIFT_ERROR_TYPE::PROCESS_NOT_READY:
                return "The process has not yet been activated by calling ProcessReady(). Processes in "
                       "standby cannot receive StartGameSession callbacks.";
            case GAMELIFT_ERROR_TYPE::PROCESS_READY_FAILED:
                return "ProcessReady call to GameLift failed.";
            case GAMELIFT_ERROR_TYPE::SDK_VERSION_DETECTION_FAILED:
                return "Could not detect SDK version.";
            case GAMELIFT_ERROR_TYPE::SERVICE_CALL_FAILED:
                return "An AWS service call has failed. See the root cause error for more information.";
            case GAMELIFT_ERROR_TYPE::STX_CALL_FAILED:
                return "An internal call to the STX server backend component has failed.";
            case GAMELIFT_ERROR_TYPE::STX_INITIALIZATION_FAILED:
                return "The STX server backend component has failed to initialize.";
            case GAMELIFT_ERROR_TYPE::UNEXPECTED_PLAYER_SESSION:
                return "The player session was not expected by the server. Clients wishing to connect "
                       "to a server must obtain a PlayerSessionID from GameLift by creating a player "
                       "session on the desired server's game instance.";
            case GAMELIFT_ERROR_TYPE::BAD_REQUEST_EXCEPTION:
                return "Bad request exception.";
            case GAMELIFT_ERROR_TYPE::INTERNAL_SERVICE_EXCEPTION:
                return "Internal service exception.";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_CONNECT_FAILURE:
                return "Connection to the GameLift Service WebSocket has failed";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_CONNECT_FAILURE_FORBIDDEN:
                return "Handshake with GameLift websocket server failed. Please verify that values of ServerParameters "
                       "in InitSDK() are correct. For example, process ID needs to be unique between executions, and "
                       "the authentication token needs to be correct and unexpired.";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_CONNECT_FAILURE_INVALID_URL:
                return "Connection to GameLift websocket server failed due to invalid websocket URL. Please verify that "
                       "websocketUrl in InitSDK() is correct and matches the GameLiftServiceSdkEndpoint output from "
                       "AWS::GameLift::RegisterCompute().";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_CONNECT_FAILURE_TIMEOUT:
                return "Connection to the GameLift Service WebSocket Connection has timed out.";
            case GAMELIFT_ERROR_TYPE::WEBSOCKET_SEND_MESSAGE_FAILURE:
                return "Sending Message to the GameLift Service WebSocket has failed.";
            default:
                return "An unexpected error has occurred.";
        }
    }
};
} // namespace GameLift
} // namespace Aws

#if defined(_MSC_VER) && !defined(GAMELIFT_USE_STD)
#pragma warning(pop) // Restore warnings to previous state.
#endif