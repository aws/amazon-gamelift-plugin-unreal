// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "FGameLiftDeployContainersTab.h"

#include <Widgets/Layout/SScrollBox.h>

#include "GameLiftPluginConstants.h"

#include "SMenu/Containers/SGameLiftDeployContainersMenu.h"

#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "FGameLiftDeployContainersTab"

void FGameLiftDeployContainersTab::Register()
{
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FTabName(),
                                                      FOnSpawnTab::CreateRaw(this, &FGameLiftDeployContainersTab::HandleSpawnTab))
            .SetDisplayName(Tabs::kDeployContainersTabTitle)
            .SetTooltipText(Tabs::kDeployContainersTabTooltip)
            .SetIcon(FSlateIcon(FGameLiftPluginStyle::Get().GetStyleSetName(), Style::Brush::kGameLiftContainersTabIconName))
            .SetMenuType(ETabSpawnerMenuType::Hidden);
}

TSharedRef<SDockTab> FGameLiftDeployContainersTab::HandleSpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
    return MakeTab(SpawnTabArgs, SNew(SGameLiftDeployContainersMenu));
}

#undef LOCTEXT_NAMESPACE
