// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "FGameLiftDeployAnywhereTab.h"

#include <Widgets/Layout/SScrollBox.h>

#include "GameLiftPluginConstants.h"

#include "SMenu/SGameLiftDeployAnywhereMenu.h"

#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "FGameLiftDeployAnywhereTab"

void FGameLiftDeployAnywhereTab::Register() 
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FTabName(),
		FOnSpawnTab::CreateRaw(this, &FGameLiftDeployAnywhereTab::HandleSpawnTab))
		.SetDisplayName(Tabs::kDeployAnywhereTabTitle)
		.SetTooltipText(Tabs::kDeployAnywhereTabTooltip)
		.SetIcon(FSlateIcon(FGameLiftPluginStyle::Get().GetStyleSetName(), Style::Brush::kGameLiftTabIconName))
		//.SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory());
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

TSharedRef<SDockTab> FGameLiftDeployAnywhereTab::HandleSpawnTab(const FSpawnTabArgs& SpawnTabArgs) 
{
	return MakeTab(SpawnTabArgs, SNew(SGameLiftDeployAnywhereMenu));
}

#undef LOCTEXT_NAMESPACE
