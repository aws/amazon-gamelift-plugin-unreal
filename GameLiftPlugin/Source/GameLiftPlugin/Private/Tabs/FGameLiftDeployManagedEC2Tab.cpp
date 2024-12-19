// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "Tabs/FGameLiftDeployManagedEC2Tab.h"

#include "SMenu/EC2/SGameLiftDeployManagedEC2Menu.h"
#include "GameLiftPluginConstants.h"

#include <Widgets/Layout/SScrollBox.h>

#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "FGameLiftDeployManagedEC2Tab"

void FGameLiftDeployManagedEC2Tab::Register()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FTabName(),
		FOnSpawnTab::CreateRaw(this, &FGameLiftDeployManagedEC2Tab::HandleSpawnTab))
		.SetDisplayName(Tabs::kDeployManagedEC2TabTitle)
		.SetTooltipText(Tabs::kDeployManagedEC2TabTooltip)
		.SetIcon(FSlateIcon(FGameLiftPluginStyle::Get().GetStyleSetName(), Style::Brush::kGameLiftManagedEC2IconName))
		//.SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory());
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

TSharedRef<SDockTab> FGameLiftDeployManagedEC2Tab::HandleSpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return MakeTab(SpawnTabArgs, SNew(SGameLiftDeployManagedEC2Menu));
}

#undef LOCTEXT_NAMESPACE
