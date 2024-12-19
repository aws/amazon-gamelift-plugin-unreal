// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SWidgets/SProgressBar.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "GL_SProgressBar"

void SProgressBar::Construct(const FArguments& InArgs) {
	ContextWindow = InArgs._ContextWindow;
	IsLastComponent = InArgs._IsLastComponent;

	ChildSlot
		[
			SAssignNew(ProgressBarWidgetSwitcher, SWidgetSwitcher)
				+ SWidgetSwitcher::Slot()
				[
					CreateProgressBarUI(Style::Brush::kProgressIncompleteIconName, Style::Brush::kProgressIncompleteBarName)
				]
				+ SWidgetSwitcher::Slot()
				[
					CreateProgressBarUI(Style::Brush::kInProgressIconName, Style::Brush::kProgressIncompleteBarName)
				]
				+ SWidgetSwitcher::Slot()
				[
					CreateProgressBarUI(Style::Brush::kProgressCompleteIconName, Style::Brush::kProgressCompleteBarName)
				]
				+ SWidgetSwitcher::Slot()
				[
					CreateProgressBarUI(Style::Brush::kProgressWarningIconName, Style::Brush::kProgressIncompleteBarName)
				]
				+ SWidgetSwitcher::Slot()
				[
					CreateProgressBarUI(Style::Brush::kProgressErrorIconName, Style::Brush::kProgressIncompleteBarName)
				]
		];
}

void SProgressBar::ChangeProgressBarUIState(EProgressBarUIState InState)
{
	ProgressBarWidgetSwitcher->SetActiveWidgetIndex(ProgressUIStateToInt(InState));
}

TSharedRef<SWidget> SProgressBar::CreateProgressBarUI(const char* ProgressIcon, const char* BarIcon)
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SImage).Image(FGameLiftPluginStyle::Get().GetBrush(ProgressIcon))
		]

		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.Padding(SPadding::ProgressBarPadding)
		[
			SNew(SBox)
				.Visibility_Lambda([&]()
					{
						return IsLastComponent ? EVisibility::Collapsed : EVisibility::Visible;
					})
				[
					SNew(SImage).Image(FGameLiftPluginStyle::Get().GetBrush(BarIcon))
				]
		];
}

void SProgressBar::SetAsLastComponent(bool IsLast)
{
	IsLastComponent = IsLast;
}

#undef LOCTEXT_NAMESPACE
