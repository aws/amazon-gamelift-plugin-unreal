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
		// Get Started
		+ SVerticalBox::Slot()
		.Padding(SPadding::Top_Bottom2x + SPadding::Right2x)
		[
			MakeGetStartedWidget()
		]
	];
}

TSharedRef<SWidget> SGameLiftSettingsGameLiftMenu::MakeGetStartedWidget() const
{

	TSharedRef<SSubtitleBlock> GetStartedTextBlock = SNew(SSubtitleBlock)
		.Text(Settings::GameLift::kGameLiftGetStartedTitleText);

	TSharedRef<STextBlock> GetStartedDescriptionBlock = SNew(STextBlock)
		.Text(Settings::GameLift::kGameLiftGetStartedDescriptionText)
		.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
		.AutoWrapText(true);

	TSharedRef<SWidget> AnywhereFleetCard = CreateFleetCard(
		Style::Brush::kGameLiftAnywhereIconName,
		Settings::GameLift::kGameLiftSetUpAnywhereTitleText,
		Settings::GameLift::kGameLiftSetUpAnywhereDescriptionText,
		MakeSetUpAnywhereButtonSwitcher()
	);

	TSharedRef<SWidget> ManagedEC2FleetCard = CreateFleetCard(
		Style::Brush::kGameLiftManagedEC2IconName,
		Settings::GameLift::kGameLiftSetUpManagedEC2TitleText,
		Settings::GameLift::kGameLiftSetUpManagedEC2DescriptionText,
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
    );

	TSharedRef<SWidget> ContainersFleetCard = CreateFleetCard(
		Style::Brush::kGameLiftContainersTabIconName,
		Settings::GameLift::kGameLiftSetUpContainersTitleText,
		Settings::GameLift::kGameLiftSetUpContainersDescriptionText,
		SNew(SButton)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Text(Settings::GameLift::kGameLiftSetUpContainersButtonText)
		.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
		.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
		.OnClicked_Lambda([]
			{
				FGameLiftPluginModule* Module = FModuleManager::GetModulePtr<FGameLiftPluginModule>(Plugin::GameLiftPluginTabName);
				Module->DeployContainersButtonClicked();
				return FReply::Handled();
			})
	);

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
		.Padding(SPadding::Top_Bottom2x)
		[
			GetStartedDescriptionBlock
		]
		+ SVerticalBox::Slot()
        .AutoHeight()
		.Padding(SPadding::Top2x_Bottom)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				AnywhereFleetCard
			]
			+ SHorizontalBox::Slot()
			[
				ManagedEC2FleetCard
			]
			+ SHorizontalBox::Slot()
			[
				ContainersFleetCard
			]
		];
}

TSharedRef<SWidget> SGameLiftSettingsGameLiftMenu::CreateFleetCard(const FString& IconName, const FText TitleText,
													const FText DescriptionText, TSharedRef<SWidget> ButtonWidget) const
{
	return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(SPadding::Right2x)
			[
				SNew(SBorder)
				.BorderImage(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kBorderImageName))
				.BorderBackgroundColor(FColor::Black)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(2)
				[
					SNew(SBorder)
					.BorderImage(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kBorderImageName))
					.BorderBackgroundColor(FGameLiftPluginStyle::Get().GetSlateColor(Style::Color::kCardBackground))
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Padding(SPadding::All2x)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Top)
						.Padding(SPadding::Bottom)
						[
							SNew(SBox)
							.WidthOverride(45)
							.HeightOverride(40)
							[
								SNew(SImage)
								.Image(FGameLiftPluginStyle::Get().GetBrush(FName(IconName)))
							]
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Left)
						.Padding(SPadding::Top_Bottom)
						[
							SNew(STextBlock)
							.Text(TitleText)
							.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kTitleStyleName)
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Left)
						.Padding(SPadding::Top + SPadding::Bottom2x)
						[
							SNew(SBox)
							.WidthOverride(310)
							[
								SNew(STextBlock)
								.Text(DescriptionText)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
								.AutoWrapText(true)
							]
						]
						+ SVerticalBox::Slot()
						.Padding(SPadding::Top_Bottom)
						.HAlign(HAlign_Center)
						[
							SNew(SBox)
							.WidthOverride(270)
							.HeightOverride(30)
							[
								ButtonWidget
							]
						]
					]
				]
			];
}

TSharedRef<SWidget> SGameLiftSettingsGameLiftMenu::MakeSetUpAnywhereButtonSwitcher() const
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
