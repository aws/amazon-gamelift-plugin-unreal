// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "IGameLiftCoreProc.h"
#include "IAWSScenariosDeployer.h"
#include "IAWSConfigFileProfile.h"
#include "IAWSBootstrapProfile.h"
#include "IGameLiftAnywhereHandler.h"
#include "GameLiftCoreConstants.h"

#include "Templates/SharedPointer.h"

/**
 * Interface for the ObjectBrowser module.
 */
class IGameLiftCoreModule : public IModuleInterface
{
public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IGameLiftCoreModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IGameLiftCoreModule>(Core::sGameLiftCoreName);
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded(Core::sGameLiftCoreName);
	}

public:

	virtual TSharedRef<IGameLiftCoreProc> MakeRunner() = 0;
	virtual IAWSScenariosDeployer& GetScenarioDeployer() = 0;
	virtual IAWSBootstrapProfile& GetProfileBootstrap() = 0;
	virtual IGameLiftAnywhereHandler& GetGameLiftAnywhereHandler() = 0;
	virtual TSharedRef<IAWSConfigFileProfile> MakeAWSConfigFileProfile() = 0;

	/**
	 * Virtual destructor
	 */
	virtual ~IGameLiftCoreModule() { }
};
