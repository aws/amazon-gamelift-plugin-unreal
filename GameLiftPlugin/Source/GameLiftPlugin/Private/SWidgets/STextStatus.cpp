// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "STextStatus.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SThrobber.h"
#include <Widgets/Layout/SWidgetSwitcher.h>

#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "GL_STextStatus"

void STextStatus::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	
	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(SPadding::Right)
		[
			SNew(SWidgetSwitcher)
			.WidgetIndex(this, &STextStatus::GetIconStateAsInt)
			// Inactive
			+ SWidgetSwitcher::Slot()
			.HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SNew(SBox).WidthOverride(Style::kStatusIconSize).HeightOverride(Style::kStatusIconSize).VAlign(VAlign_Center)
				[
					SNew(SImage)
					.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kStatusInactiveIconName))
					.ColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kInactive))
				]
			]
			// Success
			+ SWidgetSwitcher::Slot()
			.HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SNew(SBox).WidthOverride(Style::kStatusIconSize).HeightOverride(Style::kStatusIconSize).VAlign(VAlign_Center)
				[
					SNew(SImage)
					.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kStatusSuccessIconName))
					.ColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kSuccess))
				]
			]
			// Error
			+ SWidgetSwitcher::Slot()
			.HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SNew(SBox).WidthOverride(Style::kStatusIconSize).HeightOverride(Style::kStatusIconSize).VAlign(VAlign_Center)
				[
					SNew(SImage)
					.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kStatusErrorIconName))
					.ColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kError))
				]
			]
			// Loading
			+ SWidgetSwitcher::Slot()
			.HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SNew(SCircularThrobber)
				.Radius(Style::kLoadingIconSize / 2)
				.NumPieces(3)
				.ColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kLoading))
			]
		]
		+ SHorizontalBox::Slot()
		[
			SAssignNew(StatusTextBlock, STextBlock)
			.Text(InArgs._StatusText)
			.TextStyle(FGameLiftPluginStyle::Get(), InArgs._StatusTextStyle)
			.AutoWrapText(true)
		]
	];

	SetIconState(InArgs._IconState);
}

void STextStatus::SetIconState(EIconState IconState)
{
	CurrentIconState = IconState;
}

void STextStatus::SetStatusText(const FText& StatusText)
{
	StatusTextBlock->SetText(StatusText);
}

void STextStatus::SetStatusTextColor(const FSlateColor& StatusColor)
{
	StatusTextBlock->SetColorAndOpacity(StatusColor);
}

int32 STextStatus::GetIconStateAsInt() const
{
	return (int32)CurrentIconState;
}

#undef LOCTEXT_NAMESPACE
