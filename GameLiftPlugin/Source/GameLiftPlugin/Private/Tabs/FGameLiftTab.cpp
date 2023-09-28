// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "FGameLiftTab.h"

#include "Widgets/Layout/SScrollBox.h"

TSharedRef<SDockTab> FGameLiftTab::MakeTab(const FSpawnTabArgs& SpawnTabArgs, TSharedRef<SWidget> Widget)
{
	TSharedRef<SDockTab> NewDockTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.ShouldAutosize(false)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				Widget
			]
		];
	return NewDockTab;
}
