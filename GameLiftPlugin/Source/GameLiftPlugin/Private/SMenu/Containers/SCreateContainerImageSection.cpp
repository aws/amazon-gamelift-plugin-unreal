// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SCreateContainerImageSection.h"
#include "SWidgets/SExternalLinkButton.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

#include "SWidgets/SNamedRow.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SPathInput.h"
#include "SWidgets/STextSeparator.h"
#include "SWidgets/SSetupMessage.h"
#include "SMenu/Containers/SControlBarSection.h"
#include "Utils/StringPaths.h"

#include <GameLiftPluginConstants.h>
#include <GameLiftPluginStyle.h>
#include <IGameLiftCoreModule.h>
#include <Settings/UGameLiftContainersStatus.h>

#define LOCTEXT_NAMESPACE "SCreateContainerImageSection"

void SCreateContainerImageSection::Construct(const FArguments& InArgs)
{
	OnContainersImageUpdateDelegate = InArgs._OnContainersImageUpdateDelegate;
	DockerFileTemplatePath = FPaths::Combine(*Paths::DefaultContainerImagePath(), TEXT("Dockerfile"));
	ChildSlot
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(SPadding::Right2x)
			.AutoWidth()
			[
				SAssignNew(ProgressBar, SProgressBar)
			]

			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.Padding(SPadding::Bottom5x + SPadding::Right2x)
			[
				SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(SPadding::SectionTitleTopPadding)
					[
						SNew(STextBlock)
							.Text(Menu::DeployContainers::kCreateContainerImageHeader)
							.AutoWrapText(true)
							.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kTitleStyleName)
					]

					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(SPadding::Top3x)
					[
						SNew(STextBlock)
							.Text(FText::FromString(FString::Format(Menu::DeployContainers::kCreateContainerImageDescription, { DockerFileTemplatePath })))
							.AutoWrapText(true)
							.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
					]
					// External links
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(SPadding::Top2x)
					[
						SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.HAlign(HAlign_Left)
							[
								SNew(SOnlineHyperlink)
									.Text(Menu::DeployContainers::kWhatIsDockerLinkLabel)
									.Link(Url::kWhatIsDockerLinkUrl)
							]
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.HAlign(HAlign_Center)
							[
								SNew(STextSeparator).Separator(TEXT("|"))
							]
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.HAlign(HAlign_Left)
							[
								SNew(SOnlineHyperlink)
									.Text(Menu::DeployContainers::kDockerDocumentationLinkLabel)
									.Link(Url::kDockerInstallGuideLinkUrl)
							]
					]
					// Error text box
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(SPadding::Top2x)
					[
						CreateShowErrorUI()
					]
					// Game server build and executable rows
					+ SVerticalBox::Slot()
							.AutoHeight()
							.Padding(SPadding::Top2x)
							[
								SAssignNew(GameServerBuildRow, SNamedRow)
									.NameText(Menu::DeployContainers::kGameServerBuildLabel)
									.RowWidget(
										SAssignNew(GameServerBuildTextBlock, STextBlock)
										.AutoWrapText(true)
										.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
									)
							]
							+ SVerticalBox::Slot()
							.AutoHeight()
							.Padding(SPadding::Top2x)
							[
								SAssignNew(GameServerExecutableRow, SNamedRow)
									.NameText(Menu::DeployContainers::kGameServerExecutableLabel)
									.RowWidget(
										SAssignNew(GameServerExecutableTextBlock, STextBlock)
										.AutoWrapText(true)
										.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
									)
							]
					// View dockerfile template button
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Left)
					.Padding(SPadding::Top3x)
					[
						SNew(SExternalLinkButton)
							.Text(Menu::DeployContainers::kViewDockerfileTemplateButtonLabel)
							.FilePath(DockerFileTemplatePath)
							.Visibility_Lambda([&]() -> EVisibility
								{
									UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
									return ContainersStatus->IsContainerFolderSetup ? EVisibility::Visible : EVisibility::Collapsed;
								})
					]
					// Retry button
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Left)
					.Padding(SPadding::Top3x)
					[
						SNew(SButton)
							.OnClicked_Lambda([&]()
								{
									ResetUIToNotStarted();
									StartSectionWorkflow();
									return FReply::Handled();
								})
							.Visibility_Lambda([&]() -> EVisibility
								{
									UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
									return ContainersStatus->ErrorCreatingContainerImage ? EVisibility::Visible : EVisibility::Collapsed;
								})
							.Content()
							[
								SNew(SBox)
									.HAlign(HAlign_Center)
									[
										SNew(SHorizontalBox)
											+ SHorizontalBox::Slot()
											.AutoWidth()
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.Padding(SPadding::Right)
											[
												SNew(SBox)
													.WidthOverride(Style::kResetIconSize)
													.HeightOverride(Style::kResetIconSize)
													[
														SNew(SImage)
															.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kResetIconName))
													]
											]
											+ SHorizontalBox::Slot()
											.AutoWidth()
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											[
												SNew(STextBlock)
													.Text(Menu::DeployContainers::kRetryButtonLabel)
													.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
											]
									]
							]
					]
			]
		];
	UpdateUIBasedOnCurrentState();
}

void SCreateContainerImageSection::ResetUIToNotStarted() {
	FText EmptyStatus = FText::FromString("-");
	ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::NotStart);
	GameServerBuildTextBlock->SetText(EmptyStatus);
	GameServerExecutableTextBlock->SetText(EmptyStatus);
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	ContainersStatus->ErrorCreatingContainerImage = false;
	ContainersStatus->SaveConfig();
}

void SCreateContainerImageSection::UpdateUIBasedOnCurrentState()
{
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	if (ContainersStatus -> ErrorCreatingContainerImage) {
		ErrorTextBlock->SetText(ContainersStatus->ErrorMessageCreatingContainerImage);
		ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressError);
	}
	else if (ContainersStatus->IsContainerFolderSetup) {
		GameServerBuildTextBlock->SetText(FText::FromString(ContainersStatus->GameServerBuildPath));
		GameServerExecutableTextBlock->SetText(FText::FromString(ContainersStatus->GameServerExecutablePath));
		ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressComplete);
	}
	else
	{
		ResetUIToNotStarted();
	}
}

TSharedRef<SWidget> SCreateContainerImageSection::CreateShowErrorUI()
{
	TSharedPtr<SHorizontalBox> RowWidget = SNew(SHorizontalBox);
	RowWidget->AddSlot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
				.WidthOverride(Style::kMessageTextBoxWidth)
				[
					SAssignNew(ErrorTextBlock, STextBlock)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
						.AutoWrapText(true)
				]
		];

	return SNew(SSetupMessage)
		.Visibility_Lambda([&]() -> EVisibility
			{
				UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
				return ContainersStatus->ErrorCreatingContainerImage ? EVisibility::Visible : EVisibility::Collapsed;
			})
		.FailureRowWidget(RowWidget)
		.SetState(ESetupMessageState::FailureMessage);
}

FReply SCreateContainerImageSection::StartSectionWorkflow()
{
	UpdateUIToInProgress();
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	FString ContainerPath = Paths::DefaultContainerImagePath();

	// Extracting paths from inputs. Display errors if file does not exist
	FString BuildSource = ContainersStatus->GameServerBuildPath;
	if (!FPaths::DirectoryExists(*BuildSource))
	{
		ErrorTextBlock->SetText(FText::FromString("Game server build directory does not exist: " + BuildSource));
		ContainersStatus->ErrorCreatingContainerImage = true;
		ContainersStatus->IsContainerFolderSetup = false;
		ContainersStatus->ErrorMessageCreatingContainerImage = FText::FromString("Game server build directory does not exist: " + BuildSource);
		ContainersStatus->SaveConfig();
		ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressError);
		return FReply::Handled();
	}
	FString ExecutablePath = ContainersStatus->GameServerExecutablePath;
	if (!FPaths::FileExists(*ExecutablePath))
	{
		ErrorTextBlock->SetText(FText::FromString("Game server build executable does not exist: " + ExecutablePath));
		ContainersStatus->ErrorCreatingContainerImage = true;
		ContainersStatus->IsContainerFolderSetup = false;
		ContainersStatus->ErrorMessageCreatingContainerImage = FText::FromString("Game server build executable does not exist: " + ExecutablePath);
		ContainersStatus->SaveConfig();
		ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressError);
		return FReply::Handled();
	}
	FString BuildSourceWithBackSlash = BuildSource + "/";
	if (!ExecutablePath.StartsWith(BuildSourceWithBackSlash))
	{
		ErrorTextBlock->SetText(FText::FromString("Game server build executable is not a file under game server build directory."));
		ContainersStatus->ErrorCreatingContainerImage = true;
		ContainersStatus->IsContainerFolderSetup = false;
		ContainersStatus->ErrorMessageCreatingContainerImage = FText::FromString("Game server build executable is not a file under Game server build directory.");
		ContainersStatus->SaveConfig();
		ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressError);
		return FReply::Handled();
	}
	ContainersStatus->ErrorCreatingContainerImage = false;
	FString GameExecutable = ContainersStatus->GameServerExecutablePath;

	// Setup directory
	IGameLiftContainersHandler& Handler = IGameLiftCoreModule::Get().GetGameLiftContainersHandler();
	Handler.SetupContainersDirectory(BuildSource, GameExecutable, ContainerPath);

	// Saving the data to Unreal config
	ContainersStatus->IsContainerFolderSetup = true;
	ContainersStatus->SaveConfig();

	ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressComplete);
	// Kick off workflow in the next section
	OnContainersImageUpdateDelegate.ExecuteIfBound();
	return FReply::Handled();
}

void SCreateContainerImageSection::UpdateUIToInProgress() {
	ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::InProgress);
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	GameServerBuildTextBlock->SetText(FText::FromString(ContainersStatus->GameServerBuildPath));
	GameServerExecutableTextBlock->SetText(FText::FromString(ContainersStatus->GameServerExecutablePath));
}

#undef LOCTEXT_NAMESPACE