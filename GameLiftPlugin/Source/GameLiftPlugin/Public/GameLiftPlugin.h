// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Tabs/FGameLiftTab.h"

DECLARE_LOG_CATEGORY_EXTERN(GameLiftPluginLog, Log, All);

class FToolBarBuilder;
class FMenuBuilder;

class FGameLiftPluginModule : public IModuleInterface
{
public:
	FGameLiftPluginModule();

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void DeployAnywhereButtonClicked();
	void DeployManagedEC2ButtonClicked();
	void OpenSettingsButtonClicked();
	
private:
	static void GenerateWindowMenu(UToolMenu* InToolMenu, TSharedRef<FUICommandList> InCommandList);
	static TSharedRef<SWidget> GenerateToolBarMenu(TSharedRef<FUICommandList> InCommandList);	
		
	static void GenerateMainMenu(UToolMenu* Menu);
	static void GenerateHelpMenu(UToolMenu* Menu);	

	void OnPostEngineInit();
	void RegisterMenus();
	void RegisterMenuExtensions();
	void RegisterLevelEditorExtensions();
	void RegisterToolBarMenu();

	void RestoreAccount();
	void ResetDeploymentStatus();

private:
	TSharedPtr<FUICommandList> PluginCommands;

	TSharedPtr<FGameLiftTab> DeployAnywhereTab;
	TSharedPtr<FGameLiftTab> DeployManagedEC2Tab;
	TSharedPtr<FGameLiftTab> OpenSettings;
};
