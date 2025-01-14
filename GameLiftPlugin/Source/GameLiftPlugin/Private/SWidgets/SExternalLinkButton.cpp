// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SExternalLinkButton.h"

#include <Widgets/SBoxPanel.h>
#include <Widgets/Text/STextBlock.h>

#include "GameLiftPluginConstants.h"
#include "GameLiftPlugin.h"
#include "GameLiftPluginStyle.h"

#include "Utils/Misc.h"

#define LOCTEXT_NAMESPACE "GL_SExternalLinkButton"

void SExternalLinkButton::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	Link = InArgs._Link;
	FilePath = InArgs._FilePath;
	FolderPath = InArgs._FolderPath;

	ChildSlot
		[
			SNew(SButton)
				.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
				.OnClicked_Raw(this, &SExternalLinkButton::OnClicked)
				.ToolTipText(InArgs._ButtonTooltipText)
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
								.Text(InArgs._Text)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(SPadding::Left)
						.VAlign(VAlign_Center)
						[
							SNew(SBox)
								.VAlign(VAlign_Center)
								.HAlign(HAlign_Center)
								.WidthOverride(Style::kLinkIconSize)
								.HeightOverride(Style::kLinkIconSize)
								[
									SNew(SImage)
										.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kExternalLinkIconName))
								]
						]
				]
		];
}

FReply SExternalLinkButton::OnClicked()
{
	if (Link.IsSet()) {
		UE_LOG(GameLiftPluginLog, Log, TEXT("opening link: %s"), *Link.Get());
		FPlatformProcess::LaunchURL(*(Link.Get()), nullptr, nullptr);
	}
	else if (FilePath.IsSet()) {
		UE_LOG(GameLiftPluginLog, Log, TEXT("opening file: %s"), *FilePath.Get());
		if (FPaths::FileExists(FilePath.Get())) {
			FPlatformProcess::LaunchFileInDefaultExternalApplication(*FilePath.Get());
		}
	}
	else if (FolderPath.IsSet()) {
		UE_LOG(GameLiftPluginLog, Log, TEXT("opening folder: %s"), *FolderPath.Get());
		if (FPaths::DirectoryExists(FolderPath.Get())) {
			FPlatformProcess::ExploreFolder(*FolderPath.Get());
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
