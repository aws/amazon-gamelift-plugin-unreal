// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftSettingsUseCaseMenu.h"

#include "ImageUtils.h"
#include "Interfaces/IPluginManager.h"
#include "Widgets/Text/SRichTextBlock.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"
#include "SWidgets/SOnlineHyperlink.h"

#define LOCTEXT_NAMESPACE "SGameLiftSettingsUseCaseMenu"

void SGameLiftSettingsUseCaseMenu::Construct(const FArguments& InArgs)
{
	LoadImages();
}

void SGameLiftSettingsUseCaseMenu::LoadImages()
{
	// Stub for future development.
}

TSharedRef<SWidget> SGameLiftSettingsUseCaseMenu::MakeUseCaseWidget(const FText& GameName, const FText& DeveloperName, const FString& BlogLink, const FSlateBrush* ImageBrush, FVector2D ImageSize) const
{
	return SNew(SVerticalBox)
		// Image
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.WidthOverride(ImageSize.X)
			.HeightOverride(ImageSize.Y)
			[
				SNew(SImage)
				.Image(ImageBrush)
			]
		]
		// Title
		+ SVerticalBox::Slot()
		.Padding(SPadding::Top + SPadding::Left_Right)
		.FillHeight(1.0)
		[
			SNew(SRichTextBlock)
			.Text(FText::Format(Settings::UseCase::kUseCaseTitleFormatText, DeveloperName, GameName))
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
			.DecoratorStyleSet(&FGameLiftPluginStyle::Get())
			.AutoWrapText(true)
		]
		// Blog link
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Left)
		.Padding(SPadding::All)
		.AutoHeight()
		[
			SNew(SOnlineHyperlink)
			.Text(Settings::UseCase::kUseCaseLearnMoreText)
			.Link(BlogLink)
		]
	;
}

#undef LOCTEXT_NAMESPACE
