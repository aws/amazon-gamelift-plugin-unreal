// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

/** @file
 * @brief The C interface for the Config library.
 */

#pragma once
#include <aws/gamelift/core/logging.h>

 /**
  * @brief GameLiftConfigManager instance handle created by calling #GameLiftConfigManagerInstanceCreate()
 */
typedef void* GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE;

/**
 * @brief A pointer to an instance of a class that can receive a callback.
 *
 * @details The callback method signature is specified by each API which uses a DISPATCH_RECEIVER_HANDLE.
 */
typedef void* DISPATCH_RECEIVER_HANDLE;

extern "C"
{
    /**
     * @brief A static dispatcher function pointer that receives a character array.
     *
     * @param dispatchReceiver A pointer to an instance of a class where the results will be dispatched to.
     * This instance must have a method signature of void ReceiveResult(const char* charPtr);
     * @param charPtr The character array pointer that the callback function receives.
    */
    typedef void(*CharPtrCallback)(DISPATCH_RECEIVER_HANDLE dispatchReceiver, const char* charPtr);

    /**
     * @brief A static dispatcher function pointer that receives key/value pairs, one invocation at a time.
     *
     * @param dispatchReceiver A pointer to an instance of a class where the results will be dispatched to.
     * This instance must have have a method signature of void ReceiveResult(const char* charKey, const char* charValue);
     * @param charKey The key that the callback function receives.
     * @param charValue The value that the callback function receives.
    */
    typedef void(*KeyValueCharPtrCallbackDispatcher)(DISPATCH_RECEIVER_HANDLE dispatchReceiver, const char* charKey, const char* charValue);
}

extern "C"
{
    /**
     * @brief Create a GameLiftConfigManager instance, which can be used to access the Core Config API.
     *
     * @details Make sure to call GameLiftConfigManagerInstanceRelease() to destroy the returned object when finished with it.
     *
     * @param logCb Callback function for logging information and errors.
     * @return Pointer to the new GameLiftConfigManager instance.
     */
    GAMELIFT_API GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE GameLiftConfigManagerInstanceCreate(FuncLogCallback logCb);

    /**
     * @brief Destroy the provided GameLiftConfigManager instance.
     *
     * @param configManagerInstance Pointer to GameLiftConfigManager instance created with GameLiftConfigManagerInstanceCreate().
     */
    GAMELIFT_API void GameLiftConfigManagerInstanceRelease(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance);

    /**
     * @brief Get number of profiles.
     *
     * @param configManagerInstance Pointer to GameLiftConfigManager instance created with GameLiftConfigManagerInstanceCreate().
     * @param dispatchReceiver Pointer to the caller object (object that will handle the callback function).
     * @param resultCb Pointer to the callback function to invoke on completion.
     * @return The result code of the operation. GAMELIFT_SUCCESS if successful, else a non-zero value in case of error. Consult errors.h file for details.
     */
    GAMELIFT_API unsigned int GameLiftConfigManagerGetProfileNames(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, DISPATCH_RECEIVER_HANDLE caller, CharPtrCallback resultCallback);

    GAMELIFT_API unsigned int GameLiftConfigManagerCreateProfile(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName);
    GAMELIFT_API unsigned int GameLiftConfigManagerRenameProfile(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName, const char* newProfileName);

    GAMELIFT_API const char*  GameLiftConfigManagerGetAccessKey(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName);
    GAMELIFT_API unsigned int GameLiftConfigManagerSetAccessKey(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName, const char* accessKey);
    
    GAMELIFT_API const char*  GameLiftConfigManagerGetSecretAccessKey(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName);
    GAMELIFT_API unsigned int GameLiftConfigManagerSetSecretAccessKey(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName, const char* secretAccessKey);

    GAMELIFT_API const char*  GameLiftConfigManagerGetSessionToken(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName);
    GAMELIFT_API unsigned int GameLiftConfigManagerSetSessionToken(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName, const char* sessionToken);

    GAMELIFT_API const char*  GameLiftConfigManagerGetRegion(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName);
    GAMELIFT_API unsigned int GameLiftConfigManagerSetRegion(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance, const char* profileName, const char* region);

    GAMELIFT_API unsigned int GameLiftConfigManagerSave(GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE configManagerInstance);
}
