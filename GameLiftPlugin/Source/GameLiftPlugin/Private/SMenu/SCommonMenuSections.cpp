// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SCommonMenuSections.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"
#include "SGameLiftSettingsAwsAccountMenu.h"

#include "SWidgets/SNamedRow.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SPathInput.h"
#include "SWidgets/SSetupMessage.h"

#include "Settings/UGameLiftAnywhereStatus.h"
#include "Settings/UGameLiftSettings.h"
#include "Settings/UGameLiftDeploymentStatus.h"
#include "Types/EBootstrapMessageState.h"
#include "Types/EDeploymentMessageState.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

#include "Engine/Engine.h"
#include "IGameLiftCoreModule.h"
#include "ImageUtils.h"
#include "Interfaces/IPluginManager.h"
#include "GameLiftPlugin.h"

void SSetProfileSection::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SAssignNew(AwsAccountMenu, SGameLiftSettingsAwsAccountMenu)
		.ProfileManagementEnabled(false)
		.HideButtonsWhenBootstrapped(true)
		.ShowBootstrapStatusOnly(true)
		.ReadDeveloperGuideLink(InArgs._ReadDeveloperGuideLink)
	];
}

TSharedRef<SGameLiftSettingsAwsAccountMenu> SSetProfileSection::GetAwsAccountMenuRef()
{
	return AwsAccountMenu.ToSharedRef();
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
	HideBuildPathInput = InArgs._HideBuildPathInput;

	// Initialize the toggler early to hold a reference to it.

	SSectionStep::Construct(
		SSectionStep::FArguments()
		.HeaderTitle(Menu::DeployCommon::kIntegrateGameHeader)
		.HeaderDescription(HideBuildPathInput ? Menu::DeployCommon::kIntegrateGameEC2Description : Menu::DeployCommon::kIntegrateGameAnywhereDescription)
		.BodyContent()
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					CreateUnrealSourceWarningMessage()
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(SPadding::Top2x)
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
						.Visibility(HideBuildPathInput ? EVisibility::Collapsed : EVisibility::Visible)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				.Padding(SPadding::Top3x)
				[
					SAssignNew(SectionSwitcher, SWidgetSwitcher)
						+ SWidgetSwitcher::Slot()
						[
							CreateSubmissionButton()
						]
						+ SWidgetSwitcher::Slot()
						[
							CreateModifyButton()
						]
				]
		]);

	// Call once during startup.
	SetPaths();
	UpdateUIBasedOnCurrentState();
}

TSharedRef<SWidget> SIntegrateGameSection::CreateUnrealSourceWarningMessage()
{
	TSharedPtr<SVerticalBox> RowWidget = SNew(SVerticalBox);

	RowWidget->AddSlot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(2)
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				[
					SNew(SBox)
						.WidthOverride(Style::kMessageTextBoxWidth)
						[
							SNew(STextBlock)
								.Text(Menu::DeployCommon::kUnrealSourceWarningMessageText)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
								.AutoWrapText(true)
						]
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1)
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Center)
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(SPadding::Right2x)
						[
							SNew(SOnlineHyperlink)
								.Text(Menu::DeployCommon::kReadIntegrationGuideText)
								.Link(HowToIntegrateYourGameLinkUrl)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(SPadding::Right2x)
						[
							SNew(SButton)
								.Text(Menu::DeployCommon::kDownloadSourceText)
								.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
								.OnClicked_Lambda([]()
									{
										FPlatformProcess::LaunchURL(Url::kUnrealSourceUrl, NULL, NULL);
										return FReply::Handled();
									})
						]
				]
		];
		
	return SAssignNew(UnrealSourceWarningMessage, SSetupMessage)
		.WarningRowWidget(RowWidget)
		.WarningButtonStyle(Style::Button::kCloseButtonStyleName)
		.OnButtonClicked_Lambda([&]
			{
				UnrealSourceWarningMessage->SetVisibility(EVisibility::Collapsed);
			})
		.SetState(ESetupMessageState::WarningMessage);
}

TSharedRef<SWidget> SIntegrateGameSection::CreateSubmissionButton()
{
	return SAssignNew(SubmissionButton, SButton)
		.Text(HideBuildPathInput ? Menu::DeployManagedEC2::kConfirmIntegrationCompleteButtonText : Menu::DeployCommon::kSetServerBuildButtonText)
		.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
		.OnClicked_Raw(this, &SIntegrateGameSection::OnSubmissionButtonClicked)
		.IsEnabled_Lambda([&]
			{
				if (!HideBuildPathInput && GetGameServerPath().IsEmpty())
				{
					return false;
				}
				return true;
			});
}

TSharedRef<SWidget> SIntegrateGameSection::CreateModifyButton()
{
	return SAssignNew(ModifyButton, SButton)
		.Text(Menu::DeployAnywhere::kModifyPath)
		.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
		.OnClicked_Raw(this, &SIntegrateGameSection::OnModifyButtonClicked);
}

FReply SIntegrateGameSection::OnSubmissionButtonClicked()
{
	CompleteSection();
	StartNextSection();
	GameServerPathInput->SetReadonly(true);

	if (!HideBuildPathInput)
	{
		SectionSwitcher->SetActiveWidgetIndex(1);
	}

	SubmissionButton->SetVisibility(EVisibility::Collapsed);

	return FReply::Handled();
}

FReply SIntegrateGameSection::OnModifyButtonClicked()
{
	GameServerPathInput->SetReadonly(false);
	SectionSwitcher->SetActiveWidgetIndex(0);

	ResetAndCollapseNextSections();

	return FReply::Handled();
}

void SIntegrateGameSection::SetPaths()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	GameServerPathInput->SetSelectedPath(AnywhereStatus->PathToServerBuild);
}

void SIntegrateGameSection::UpdateUIBasedOnCurrentState()
{
	// TODO: Add state for each section completion
	UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();
	EDeploymentMessageState State = EDeploymentMessageStateFromString(DeploySettings->Status.ToString());

	if (State != EDeploymentMessageState::NoDeploymentMessage && HideBuildPathInput)
	{
		CompleteSection();
	}
	else if (!HideBuildPathInput && !GameServerPathInput->GetSelectedPath().IsEmpty())
	{
		OnSubmissionButtonClicked();
	}
	else 
	{
		StartSection();
	}
}

void SIntegrateGameSection::CompleteSection()
{
	SetPaths();
	SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressComplete);
	SubmissionButton->SetVisibility(EVisibility::Collapsed);
}

void SIntegrateGameSection::StartSection()
{
	SubmissionButton->SetVisibility(EVisibility::Visible);
}

const FString& SIntegrateGameSection::GetGameServerPath() const
{
	return GameServerPathInput->GetSelectedPath().ToString();
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
