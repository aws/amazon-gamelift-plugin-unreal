// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "Tabs/FGameLiftDeployContainerTab.h"

#include "SMenu/SGameLiftDeployContainerMenu.h"
#include "GameLiftPluginConstants.h"

#include <Widgets/Layout/SScrollBox.h>

#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "FGameLiftDeployContainerTab"

void FGameLiftDeployContainerTab::Register()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FTabName(),
		FOnSpawnTab::CreateRaw(this, &FGameLiftDeployContainerTab::HandleSpawnTab))
		.SetDisplayName(Tabs::kDeployContainerTabTitle)
		.SetTooltipText(Tabs::kDeployContainerTabTooltip)
		.SetIcon(FSlateIcon(FGameLiftPluginStyle::Get().GetStyleSetName(), Style::Brush::kGameLiftTabIconName))
		//.SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory());
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

TSharedRef<SDockTab> FGameLiftDeployContainerTab::HandleSpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return MakeTab(SpawnTabArgs, SNew(SGameLiftDeployContainerMenu));
}

#undef LOCTEXT_NAMESPACE
