// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SCommonMenuSections.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"
#include "SGameLiftSettingsAwsAccountMenu.h"

#include "SWidgets/SNamedRow.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SPathInput.h"

#include "Settings/UGameLiftAnywhereStatus.h"
#include "Settings/UGameLiftSettings.h"
#include "Types/EBootstrapMessageState.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Text/SRichTextBlock.h"

#include "Engine/Engine.h"
#include "IGameLiftCoreModule.h"
#include "ImageUtils.h"
#include "Interfaces/IPluginManager.h"
#include "GameLiftPlugin.h"

void SSetProfileSection::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SGameLiftSettingsAwsAccountMenu)
		.ProfileManagementEnabled(false)
		.HideButtonsWhenBootstrapped(true)
		.ShowBootstrapStatusOnly(true)
	];
}

SSectionsWithHeaders::FSectionInfo SSetProfileSection::GetSectionInfo()
{
	SSectionsWithHeaders::FSectionInfo OutSectionInfo;
	OutSectionInfo.HeaderTitle = Menu::DeployCommon::kSetProfileHeader;
	OutSectionInfo.Body = SharedThis(this);
	OutSectionInfo.IsCollapsed = false;

	return OutSectionInfo;
}

void SIntegrateGameSection::Construct(const FArguments& InArgs)
{
	HowToIntegrateYourGameLinkUrl = InArgs._HowToIntegrateYourGameLinkUrl;

	LoadImages();

	// Initialize the toggler early to hold a reference to it.
	TogglerButtonsBox = SNew(SHorizontalBox);
	TogglerContentBox = SNew(SVerticalBox);
	GenerateTogglerButtons();
	GenerateTogglerContent();

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(0,0,0))
			[
				SNew(SBorder)
				.BorderBackgroundColor(FGameLiftPluginStyle::Get().GetSlateColor(Style::Color::kCardBackground))
				.BorderImage(FGameLiftPluginStyle::GetAppStyle().GetBrush("WhiteTexture"))
				.Padding(SPadding::Top2x_Bottom2x + SPadding::Left2x_Right2x)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						TogglerButtonsBox.ToSharedRef()
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						TogglerContentBox.ToSharedRef()
					]
				]
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top2x_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployCommon::kGameServerPathTitle)
			.RowWidget(
				SAssignNew(GameServerPathInput, SPathInput)
				.Title(Menu::DeployCommon::kGameServerPathTitle)
				.PathHint(Menu::DeployCommon::kGameServerPathHint)
				.IsFileSelection(true)
				.ToolTipText(Menu::DeployCommon::kGameServerPathTooltip)
				.OnPathUpdated_Raw(this, &SIntegrateGameSection::OnServerPathInputUpdated)
			)
			.Visibility(InArgs._HideBuildPathInput ? EVisibility::Collapsed : EVisibility::Visible)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployCommon::kGameClientPathTitle)
			.RowWidget(
				SAssignNew(GameClientPathInput, SPathInput)
				.Title(Menu::DeployCommon::kGameClientPathTitle)
				.PathHint(Menu::DeployCommon::kGameClientPathHint)
				.IsFileSelection(true)
				.ToolTipText(Menu::DeployCommon::kGameClientPathTooltip)
				.OnPathUpdated_Raw(this, &SIntegrateGameSection::OnClientPathInputUpdated)
			)
			.Visibility(InArgs._HideBuildPathInput ? EVisibility::Collapsed : EVisibility::Visible)
		]
	];

	// Call once during startup.
	UpdateUI();
}

SSectionsWithHeaders::FSectionInfo SIntegrateGameSection::GetSectionInfo()
{
	SSectionsWithHeaders::FSectionInfo OutSectionInfo;
	OutSectionInfo.HeaderTitle = Menu::DeployCommon::kIntegrateGameHeader;
	OutSectionInfo.Body = SharedThis(this);
	OutSectionInfo.IsCollapsed = false;

	return OutSectionInfo;
}

void SIntegrateGameSection::UpdateUI()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	GameServerPathInput->SetSelectedPath(AnywhereStatus->PathToServerBuild);
	GameClientPathInput->SetSelectedPath(AnywhereStatus->PathToClientBuild);
}

const FString& SIntegrateGameSection::GetGameServerPath() const
{
	return GameServerPathInput->GetSelectedPath().ToString();
}

const FString& SIntegrateGameSection::GetGameClientPath() const
{
	return GameClientPathInput->GetSelectedPath().ToString();
}

void SIntegrateGameSection::LoadImages()
{
	// Stub for future development.
}

void SIntegrateGameSection::GenerateTogglerButtons()
{
	// Stub for future development.
}

TSharedRef<SWidget> SIntegrateGameSection::MakeTogglerButtonWidget(const FText& SectionName, const FSlateBrush* ImageBrush, FVector2D ImageSize, int index)
{	
	const FSlateBrush* TogglerBrush = (ActiveTogglerTab == index) ? FGameLiftPluginStyle::GetAppStyle().GetBrush("WhiteTexture") : nullptr;

	return
		SNew(SButton)
		.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kFlatButtonStyleName)
		.OnClicked(this, &SIntegrateGameSection::SwitchActiveToggler, index)
		.ContentPadding(FMargin(0.0f, 0.0f))
		.Content()
		[
			SNew(SBorder)
			.BorderBackgroundColor(FGameLiftPluginStyle::Get().GetSlateColor(Style::Color::kTogglerBorder))
			.BorderImage(TogglerBrush)
			.Padding(1.0f)
			[
				SNew(SBorder)
				.BorderBackgroundColor(FGameLiftPluginStyle::Get().GetSlateColor(Style::Color::kTogglerBackground))
				.BorderImage(TogglerBrush)
				.Padding(SPadding::All)
				.Cursor(EMouseCursor::Hand)
				[
					SNew(SVerticalBox)
					// Image
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
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
					.Padding(SPadding::All + SPadding::Top)
					.AutoHeight()
					[
						SNew(SRichTextBlock)
						.Text(SectionName)
					]
				]
			]
		]
	;
}


void SIntegrateGameSection::GenerateTogglerContent()
{
	const FSlateBrush* BoxBrush = FGameLiftPluginStyle::GetAppStyle().GetBrush("WhiteTexture");

	const int PrimaryColumnWidthOverride = 280;

	TogglerContentBox->ClearChildren();

	//if (ActiveTogglerTab == 0)
	{
		TogglerContentBox->AddSlot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.Padding(SPadding::Top_Bottom)
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderBackgroundColor(FGameLiftPluginStyle::Get().GetSlateColor(Style::Color::kTogglerBackground))
				.BorderImage(BoxBrush)
				.Padding(SPadding::All + SPadding::Left_Right + SPadding::Top)
				[
					SNew(STextBlock)
					.Text(Menu::DeployCommon::kIntegrateGameDescription)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
					.AutoWrapText(true)
					.LineHeightPercentage(1.25f)
				]
			]
			+ SVerticalBox::Slot()
			.Padding(SPadding::All)
			.AutoHeight()
			[
				SNew(SNamedRow)
				.NameText(Menu::DeployCommon::kNewProjectStep1)
				.PrimaryColumnWidthOverride(PrimaryColumnWidthOverride)
				.SecondaryColumnLeftPadding(true)
				.RowWidget(
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Left)
					[
						SNew(SOnlineHyperlink)
						.Text(Menu::DeployCommon::kNewProjectStep1_Button)
						.Link(Menu::DeployCommon::kNewProjectStep1_Url)
					]
				)
			]
			+ SVerticalBox::Slot()
			.Padding(SPadding::All)
			.AutoHeight()
			[
				SNew(SNamedRow)
				.NameText(Menu::DeployCommon::kNewProjectStep2)
				.PrimaryColumnWidthOverride(PrimaryColumnWidthOverride)
				.RowWidget(
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Left)
					[
						SNew(SButton)
						.Text(Menu::DeployCommon::kNewProjectStep2_Button)
						.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
						.OnClicked_Lambda([]() {
							FPlatformProcess::LaunchURL(Menu::DeployCommon::kNewProjectStep2_Url, NULL, NULL);
							return FReply::Handled();
						})
					]
				)
			]
			+ SVerticalBox::Slot()
			.Padding(SPadding::All)
			.AutoHeight()
			[
				SNew(SNamedRow)
				.NameText(Menu::DeployCommon::kNewProjectStep3)
				.PrimaryColumnWidthOverride(PrimaryColumnWidthOverride)
				.SecondaryColumnLeftPadding(true)
				.RowWidget(
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Left)
					[
						SNew(SOnlineHyperlink)
						.Text(Menu::DeployCommon::kNewProjectStep3_Button)
						.Link(HowToIntegrateYourGameLinkUrl)
					]
				)
			]
		];
	}
}

FReply SIntegrateGameSection::SwitchActiveToggler(int index)
{
	ActiveTogglerTab = index;
	GenerateTogglerButtons();
	GenerateTogglerContent();
	return FReply::Handled();
}

void SIntegrateGameSection::OnServerPathInputUpdated(const FString& NewPath)
{
	if (!NewPath.IsEmpty())
	{
		UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
		AnywhereStatus->PathToServerBuild = NewPath;
		AnywhereStatus->SaveConfig();
	}
}

void SIntegrateGameSection::OnClientPathInputUpdated(const FString& NewPath)
{
	if (!NewPath.IsEmpty())
	{
		UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
		AnywhereStatus->PathToClientBuild = NewPath;
		AnywhereStatus->SaveConfig();
	}
}
