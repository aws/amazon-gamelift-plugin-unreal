// Copyright 2024 Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SCopyPasteTextBox.h"

#include "HAL/PlatformApplicationMisc.h"


#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

void SCopyPasteTextBox::Construct(const FArguments& InArgs)
{
	Text = InArgs._Text;

	ChildSlot
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(SPadding::Right)
				[
					SNew(SBox)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.WidthOverride(Style::kCopyPasteIconSize)
						.HeightOverride(Style::kCopyPasteIconSize)
						[
							SNew(SImage)
								.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kCopyPasteIconName))
						]
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
						.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
						.OnClicked_Raw(this, &SCopyPasteTextBox::OnClicked)
						[
							SAssignNew(TextBlock, STextBlock)
								.Text(Text)
								.AutoWrapText(true)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
						]
				]
		];
}

void SCopyPasteTextBox::SetText(FText NewText)
{
	TextBlock->SetText(NewText);
	Text = NewText;
}

FReply SCopyPasteTextBox::OnClicked() {
	FPlatformApplicationMisc::ClipboardCopy(*Text.ToString());
	return FReply::Handled();
}