// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "IGameLiftCoreModule.h"

const FName GameLiftCoreTabName{ Core::sGameLiftPluginName };

/**
* Implements the GameLiftCore module.
*/
class FGameLiftCoreModule : public IGameLiftCoreModule
{
public:
	FGameLiftCoreModule();	

	//~ Begin IModuleInterface Interface

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override;

	//~ End IModuleInterface Interface

	//~ Begin IGameLiftCoreModule Interface

	virtual TSharedRef<IGameLiftCoreProc> MakeRunner() override;
	virtual IAWSScenariosDeployer& GetScenarioDeployer() override;
	virtual IGameLiftAnywhereHandler& GetGameLiftAnywhereHandler() override;
	virtual IGameLiftContainersHandler& GetGameLiftContainersHandler() override;

	//~ End IGameLiftCoreModule Interface

	virtual IAWSBootstrapProfile& GetProfileBootstrap() override;
	
	//~ End IModuleInterface Interface

	TSharedRef<IAWSConfigFileProfile> MakeAWSConfigFileProfile() override;

private:

	//Stored slate widget that was loaded
	class UUserWidget* CreatedWidget;

private:
	TSharedRef<IAWSScenariosDeployer> Deployer;
	TSharedRef<IAWSBootstrapProfile> ProfileBootstrap;
	TSharedRef<IGameLiftAnywhereHandler> AnywhereHandler;
	TSharedRef<IGameLiftContainersHandler> ContainersHandler;

	bool bShowDetails;
};
