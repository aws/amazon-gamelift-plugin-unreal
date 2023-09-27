// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftSettingsGameLiftMenu.h"

#include "ImageUtils.h"
#include "Interfaces/IPluginManager.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Text/STextBLock.h"

#include "GameLiftPlugin.h"
#include "GameLiftPluginStyle.h"
#include "GameLiftPluginConstants.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/STitleBlock.h"

#include "Settings/UGameLiftSettings.h"
#include "Types/EBootstrapMessageState.h"

#define LOCTEXT_NAMESPACE "SGameLiftSettingsGameLiftMenu"

void SGameLiftSettingsGameLiftMenu::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		// GameLift Intro
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top2x_Bottom + SPadding::Right2x)
		[
			MakeGameLiftIntroWidget()
		]
		// Get Started
		+ SVerticalBox::Slot()
		.Padding(SPadding::Top_Bottom2x + SPadding::Right2x)
		[
			MakeGetStartedWidget()
		]
	];
}

TSharedRef<SWidget> SGameLiftSettingsGameLiftMenu::MakeGameLiftIntroWidget() const
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(SPadding::Left_Right)
		[
			SNew(SBox)
			.WidthOverride(Style::Brush::kGameLiftLogoIconSize.X)
			.HeightOverride(Style::Brush::kGameLiftLogoIconSize.Y)
			[
				SNew(SImage)
				.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kGameLiftLogoIconName))
			]
		]
		+ SHorizontalBox::Slot()
		.Padding(SPadding::Left)
		.VAlign(VAlign_Center)
		[
			SNew(SRichTextBlock)
			.Text(Settings::GameLift::kGameLiftIntroDescriptionText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
			.DecoratorStyleSet(&FGameLiftPluginStyle::Get())
			.AutoWrapText(true)
		]
	;
}

TSharedRef<SWidget> SGameLiftSettingsGameLiftMenu::MakeGetStartedWidget() const
{
	FVector2D SampleGameImageSize(200, 100);

	TSharedRef<SSubtitleBlock> GetStartedTextBlock = SNew(SSubtitleBlock)
		.Text(Settings::GameLift::kGameLiftGetStartedTitleText);

	TSharedRef<SGridPanel> GetStartGridPanel = SNew(SGridPanel)
		// Anywhere
		+ SGridPanel::Slot(0, 1)
		.Padding(SPadding::Top_Bottom + SPadding::Right)
		[
			MakeSetUpAnywhereButtonSwicher()
		]
		+ SGridPanel::Slot(1, 1)
		.Padding(SPadding::Top_Bottom + SPadding::Left)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
			.Text(Settings::GameLift::kGameLiftSetUpAnywhereDescriptionText)
		]
		// EC2
		+ SGridPanel::Slot(0, 2)
		.Padding(SPadding::Top_Bottom + SPadding::Right)
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Text(Settings::GameLift::kGameLiftSetUpManagedEC2ButtonText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
			.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
			.OnClicked_Lambda([]
			{
				FGameLiftPluginModule* Module = FModuleManager::GetModulePtr<FGameLiftPluginModule>(Plugin::GameLiftPluginTabName);
				Module->DeployManagedEC2ButtonClicked();
				return FReply::Handled();
			})
		]
		+ SGridPanel::Slot(1, 2)
		.Padding(SPadding::Top_Bottom + SPadding::Left)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
			.Text(Settings::GameLift::kGameLiftSetUpManagedEC2DescriptionText)
		];
	
	// Combine widgets
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		[
			GetStartedTextBlock
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			GetStartGridPanel
		];
}

TSharedRef<SWidget> SGameLiftSettingsGameLiftMenu::MakeSetUpAnywhereButtonSwicher() const
{
	return SNew(SWidgetSwitcher)
		.WidgetIndex_Lambda([]
		{
			UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
			return EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::ActiveMessage ? 1 : 0;
		})
		+ SWidgetSwitcher::Slot()
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Text(Settings::GameLift::kGameLiftSetUpAnywhereButtonText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
			.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
			.OnClicked_Lambda([]
			{
				FGameLiftPluginModule* Module = FModuleManager::GetModulePtr<FGameLiftPluginModule>(Plugin::GameLiftPluginTabName);
				Module->DeployAnywhereButtonClicked();
				return FReply::Handled();
			})
		]
		+ SWidgetSwitcher::Slot()
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Text(Settings::GameLift::kGameLiftSetUpAnywhereButtonText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonLight)
			.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
			.OnClicked_Lambda([]
			{
				FGameLiftPluginModule* Module = FModuleManager::GetModulePtr<FGameLiftPluginModule>(Plugin::GameLiftPluginTabName);
				Module->DeployAnywhereButtonClicked();
				return FReply::Handled();
			})
		];
}

#undef LOCTEXT_NAMESPACE
