// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SNamedRow.h"

#define LOCTEXT_NAMESPACE "GL_SNamedRow"

#include "GameLiftPluginStyle.h"

void SNamedRow::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	RowWidget = InArgs._RowWidget;

	// Set a minimum row height since the row widget can have different heights (e.g. STextBlock versus SButton).
	const int MinimumRowHeight = 22;

	const FMargin SpaceBeforeTooltip = FMargin(6, 0, 0, 0);
	const FMargin ExtraSpaceBeforeSecondaryColumnForTextWidgets = FMargin(3, 0, 0, 0);

	TSharedRef<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(InArgs._NameText)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kField)
		];
	
	if (!InArgs._NameTooltipText.IsEmpty())
	{
		HorizontalBox->AddSlot()
			.AutoWidth()
			.Padding(SpaceBeforeTooltip)
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)
				.WidthOverride(Style::kTooltipIconSize)
				.HeightOverride(Style::kTooltipIconSize)
				[
					SNew(SImage)
					.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kTooltipIconName))
					.ColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kTooltip))
					.ToolTipText(InArgs._NameTooltipText)
				]
			];
	}

	ChildSlot
	[
		SNew(SHorizontalBox)
		// Primary column
		+ SHorizontalBox::Slot()
		.VAlign(InArgs._FirstColumnVAlignTop ? VAlign_Top : VAlign_Center)
		.AutoWidth()
		[
			SNew(SBox)
			.VAlign(VAlign_Center)
			.WidthOverride(InArgs._PrimaryColumnWidthOverride)
			.MinDesiredHeight(MinimumRowHeight)
			[
				HorizontalBox
			]
		]
		// Secondary column
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Fill)
		.Padding(InArgs._SecondaryColumnLeftPadding ? ExtraSpaceBeforeSecondaryColumnForTextWidgets : FMargin())
		[
			SNew(SBox)
			.VAlign(VAlign_Center)
			.WidthOverride(InArgs._SecondaryColumnWidthOverride)
			.MinDesiredHeight(MinimumRowHeight)
			[
				RowWidget.ToSharedRef()
			]
		]
	];
}

TSharedRef<SWidget> SNamedRow::GetRowWidget()
{
	return RowWidget.ToSharedRef();
}

#undef LOCTEXT_NAMESPACE
