// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SBuildAndPushToECRSection.h"
#include "SWidgets/SOnlineHyperlink.h"

#include "Widgets/Layout/SWidgetSwitcher.h"
#include "SWidgets/SExternalLinkButton.h"
#include "SWidgets/SCopyPasteTextBox.h"
#include "SWidgets/STextStatus.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SSetupMessage.h"
#include "IGameLiftCoreModule.h"
#include "SMenu/Containers/SControlBarSection.h"

#include <GenericPlatform/GenericPlatformMisc.h>
#include "Editor/EditorEngine.h"

#include "Settings/UGameLiftContainersStatus.h"
#include "Settings/UGameLiftSettings.h"
#include "Types/EContainersDeploymentScenario.h"

#include <GameLiftPluginConstants.h>
#include <GameLiftPluginStyle.h>
#include "GameLiftPlugin.h"
#include <Settings/UGameLiftContainersStatus.h>
#include "Settings/UGameLiftSettings.h"
#include "Utils/StringPaths.h"
#include "Misc/FileHelper.h"
#include "Widgets/Layout/SExpandableArea.h"

#define LOCTEXT_NAMESPACE "SBuildAndPushToECRSection"

static bool isDockerSetup;

void SBuildAndPushToECRSection::SetCommandText() {
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	FString ECRRepoUri = ContainersStatus->ECRRepoUri;
	FString ECRRegistryUrl;
	FString RepoName;
	ECRRepoUri.Split(TEXT("/"), &ECRRegistryUrl, &RepoName);
	

	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	FText AWS_REGION = Settings->AwsRegion;

	FText STEP_1_COMMAND = FText::Format(FText::FromString("aws ecr get-login-password --region {0} | docker login --username AWS --password-stfin {1}"), AWS_REGION, FText::FromString(ECRRegistryUrl));
	FText STEP_2_COMMAND = FText::Format(LOCTEXT("BuildAndPushToECrStep2Command", "docker build -t {0} ."), FText::FromString(RepoName));
	FText STEP_3_COMMAND = FText::Format(LOCTEXT("BuildAndPushToECrStep3Command", "docker tag {0}:latest {1}:latest"), FText::FromString(RepoName), FText::FromString(ECRRepoUri));
	FText STEP_4_COMMAND = FText::Format(LOCTEXT("BuildAndPushToECrStep4Command", "docker push {0}:latest"), FText::FromString(ECRRepoUri));
	Command1Box->SetText(STEP_1_COMMAND);
	Command2Box->SetText(STEP_2_COMMAND);
	Command3Box->SetText(STEP_3_COMMAND);
	Command4Box->SetText(STEP_4_COMMAND);
}

void SBuildAndPushToECRSection::Construct(const FArguments& InArgs)
{
	isDockerSetup = FPlatformMisc::OsExecute(TEXT("open"), TEXT("docker"), TEXT("-v"));
	OnBuildAndPushFinishedDelegate = InArgs._OnBuildAndPushFinishedDelegate;

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
			.Padding(SPadding::Bottom5x + SPadding::Right2x)
			.FillWidth(1.0f)
			[
				SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(SPadding::SectionTitleTopPadding)
					[
						SNew(STextBlock)
							.Text(Menu::DeployContainers::kBuildAndPushToECRHeader)
							.AutoWrapText(true)
							.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kTitleStyleName)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(SPadding::Top3x)
					[
						SNew(STextBlock)
							.Text(Menu::DeployContainers::kBuildAndPushToECRDescription)
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
									.Text(Menu::DeployContainers::kLearnMoreAboutPrivateRepositoryLabel)
									.Link(Url::kAmazonECRUserGuideLinkUrl)
							]
					]
					// Show commands 
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(SPadding::Top2x)
					[
						SNew(SBox)
							.Visibility_Lambda([&]()
								{
									return isDockerSetup ? EVisibility::Collapsed : EVisibility::Visible;
								})
							[
								CreateShowCommandsUI()
							]
					]
					// Error text box
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(SPadding::Top2x)
					[
						CreateShowErrorUI()
					]
					// Image tag row
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.Padding(SPadding::Top2x)
					[
						SAssignNew(ImageTagRow, SNamedRow)
							.NameText(Menu::DeployContainers::kImageTagText)
							.RowWidget(
								SAssignNew(ImageTagTextBlock, STextBlock)
								.Text(Menu::DeployContainers::kSetupECRRepositoryDescription)
								.AutoWrapText(true)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
							)
							.SecondaryColumnLeftPadding(true)
							.Visibility(EVisibility::Collapsed)
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
									return ContainersStatus->ErrorRunningBuildAndPushScript ? EVisibility::Visible : EVisibility::Collapsed;
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

// UI to show error message
TSharedRef<SWidget> SBuildAndPushToECRSection::CreateShowErrorUI()
{
	FString LogFilePath = Paths::ContainersPushScriptLogPath();
	TSharedPtr<SHorizontalBox> RowWidget = SNew(SHorizontalBox);
	RowWidget->AddSlot()
		.FillWidth(1)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
				.WidthOverride(Style::kMessageTextBoxWidth)
				[
					SNew(STextBlock)
						.Text(FText::Format(LOCTEXT("BuildAndPushToECrScriptError", "An error occurred or timed out when running build and push image script. Please check log file at {0}."), FText::FromString(LogFilePath)))
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
						.AutoWrapText(true)
				]
		];

	RowWidget->AddSlot()
		.AutoWidth()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(SPadding::All)
		[
			SAssignNew(ViewLogsButton, SExternalLinkButton)
				.Text(Menu::DeployContainers::kViewLogButtonText)
				.FilePath(Paths::ContainersPushScriptLogPath())
				.Visibility_Lambda([&]
					{
						return FPaths::FileExists(*Paths::ContainersPushScriptLogPath()) ? EVisibility::Visible : EVisibility::Collapsed;
					})
		];

	return SNew(SSetupMessage)
		.Visibility_Lambda([&]() -> EVisibility
			{
				UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
				return ContainersStatus->ErrorRunningBuildAndPushScript ? EVisibility::Visible : EVisibility::Collapsed;
			})
		.FailureRowWidget(RowWidget)
		.SetState(ESetupMessageState::FailureMessage);
}

void SBuildAndPushToECRSection::UpdateUIBasedOnCurrentState()
{
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	if (ContainersStatus->ErrorRunningBuildAndPushScript) {
		ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressError);
	}
	else if (ContainersStatus->IsContainerImagePushed)
	{
		if (isDockerSetup)
		{
			ImageTagTextBlock->SetText(ContainersStatus->ImageTag);
			ImageTagRow->SetVisibility(EVisibility::Visible);
		}
		else
		{
			ContinueButton->SetVisibility(EVisibility::Collapsed);
		}
		
		ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressComplete);
	}
	else if (ShouldStartSectionWorkflow()) {
		ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::InProgress);
	}
	else
	{
		ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::NotStart);
	}
}

bool SBuildAndPushToECRSection::ShouldStartSectionWorkflow() {
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	if (ContainersStatus->ContainerFleetDeploymentStatus == (int)EContainerFleetDeploymentStatus::DeploymentInProgress && !ContainersStatus->IsContainerImagePushed && ContainersStatus->IsSetupECRRepoStepFinished) {
		return true;
	}
	return false;
}

FReply SBuildAndPushToECRSection::StartSectionWorkflow()
{
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	SetCommandText();
	ContainersStatus->IsContainerImagePushed = false;
	ContainersStatus->SaveConfig();
	ImageTagTextBlock->SetText(ContainersStatus->ImageTag);
	UpdateUIBasedOnCurrentState();
	ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::InProgress);
	if (!isDockerSetup) {
		return FReply::Handled();
	}
	ImageTagRow->SetVisibility(EVisibility::Visible);
	Async(EAsyncExecution::Thread,
		[this]()
		{
			bool succeeded = RunScript();
			Async(EAsyncExecution::TaskGraphMainThread,
				[this, succeeded = MoveTemp(succeeded)]
				{
					UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
					if (ContainersStatus->ContainerFleetDeploymentStatus == (int)EContainerFleetDeploymentStatus::DeploymentNotStart) {
						ResetUIToNotStarted();
						return;
					}
					if (succeeded) {
						HandleBuildAndPushSucceed();
					}
					else {
						HandleBuildAndPushFailed();
					}
				});
		});
	return FReply::Handled();
}

void SBuildAndPushToECRSection::HandleBuildAndPushSucceed() {
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	ImageTagTextBlock->SetText(ContainersStatus->ImageTag);
	ImageTagRow->SetVisibility(EVisibility::Visible);
	ContainersStatus->IsContainerImagePushed = true;
	ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressComplete);
	ContainersStatus->ErrorRunningBuildAndPushScript = false;
	ContainersStatus->SaveConfig();
	OnBuildAndPushFinishedDelegate.ExecuteIfBound();
}

void SBuildAndPushToECRSection::HandleBuildAndPushFailed() {
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	ImageTagTextBlock->SetText(ContainersStatus->ImageTag);
	ImageTagRow->SetVisibility(EVisibility::Visible);
	ContainersStatus->IsContainerImagePushed = false;
	ContainersStatus->ErrorRunningBuildAndPushScript = true;
	ContainersStatus->SaveConfig();
	ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::ProgressError);
}

bool SBuildAndPushToECRSection::RunScript()
{
	// Prepare powershell script
	FString SampleScriptPath = GetScriptPath();
	FString ResultScriptString;
	FFileHelper::LoadFileToString(ResultScriptString, *SampleScriptPath);

	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	FString ECRRepoUri = ContainersStatus->ECRRepoUri;
	FString ECRRegistryUrl;
	FString RepoName;
	ECRRepoUri.Split(TEXT("/"), &ECRRegistryUrl, &RepoName);
	FString ImageID = ContainersStatus->ImageID.ToString();
	FString ImageTag = ContainersStatus->ImageTag.ToString();

	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	FString AwsRegion = Settings->AwsRegion.ToString();
	FString ProfileName = Settings->CurrentProfileName;

	FString GameExecutable = ContainersStatus->GameServerExecutablePath;
	FString BuildPath = ContainersStatus->GameServerBuildPath;
	FString BuildDirectoryName = FPaths::GetCleanFilename(BuildPath);
	BuildPath += TEXT("/");
	if (!FPaths::MakePathRelativeTo(GameExecutable, *BuildPath)) {
		UE_LOG(GameLiftPluginLog, Display, TEXT("Failed to make game executable path relateive to game directory"));
		return false;
	}
	ResultScriptString = ResultScriptString.Replace(TEXT("{{REGION}}"), *AwsRegion);
	ResultScriptString = ResultScriptString.Replace(TEXT("{{PROFILE_NAME}}"), *ProfileName);
	ResultScriptString = ResultScriptString.Replace(TEXT("{{IMAGE_ID}}"), *ImageID);
	ResultScriptString = ResultScriptString.Replace(TEXT("{{IMAGE_PATH}}"), *Paths::DefaultContainerImagePath());
	ResultScriptString = ResultScriptString.Replace(TEXT("{{ECR_REGISTRY_URL}}"), *ECRRegistryUrl);
	ResultScriptString = ResultScriptString.Replace(TEXT("{{IMAGE_TAG}}"), *ImageTag);
	ResultScriptString = ResultScriptString.Replace(TEXT("{{ECR_REPO_URI}}"), *ECRRepoUri);
	ResultScriptString = ResultScriptString.Replace(TEXT("{{REPO_NAME}}"), *RepoName);
	ResultScriptString = ResultScriptString.Replace(TEXT("{{GAME_BUILD_DIRECTORY}}"), *BuildDirectoryName);
	ResultScriptString = ResultScriptString.Replace(TEXT("{{GAME_EXECUTABLE}}"), *GameExecutable);

	// Save script
	FString PowerShellScriptPath = Paths::ContainersPushScriptPath();
	FString LogFilePath = Paths::ContainersPushScriptLogPath();
	FFileHelper::SaveStringToFile(ResultScriptString, *PowerShellScriptPath);
	// Run commands
	FString CommandParameter = FString::Printf(TEXT("powershell -File '%s' 2>&1 | tee -filePath '%s'"), *PowerShellScriptPath, *LogFilePath);
	FPlatformMisc::OsExecute(TEXT("open"), TEXT("powershell"), *CommandParameter);
	// 30 minutes of timeout for running script
	for (int i = 0; i < WaitTimesCount; ++i) {
		FPlatformProcess::Sleep(WaitIntervalSeconds);
		FString RanScriptResultString;
		FFileHelper::LoadFileToString(RanScriptResultString, *LogFilePath);
		if (RanScriptResultString.Contains("ECR Container image setup succeeded.")) {
			return true;
		}
		else if (RanScriptResultString.Contains("has failed.")) {
			return false;
		}
	}
	return false;
}

FString SBuildAndPushToECRSection::GetScriptPath() {
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	if (ContainersStatus->DeploymentScenario == (int)EContainersDeploymentScenario::HaveContainerImageInDocker) {
		return Paths::PushExistingImageToECRPath();
	}
	else {
		return Paths::ContainersSamplePushScriptPath();
	}
}


// UI to show commands
TSharedRef<SWidget> SBuildAndPushToECRSection::CreateShowCommandsUI()
{
	SAssignNew(Command1Box, SCopyPasteTextBox);
	SAssignNew(Command2Box, SCopyPasteTextBox);
	SAssignNew(Command3Box, SCopyPasteTextBox);
	SAssignNew(Command4Box, SCopyPasteTextBox);
	SetCommandText();
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(STextBlock)
				.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelperDescriptionPart1)
				.AutoWrapText(true)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(STextBlock)
				.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelperDescriptionPart2)
				.AutoWrapText(true)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SOnlineHyperlink)
				.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelperLink)
				.Link(Url::kECRRegistryAuthenticationUrl)
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top2x_Bottom2x + SPadding::Right2x)
		[
			SNew(SExpandableArea)
				.AllowAnimatedTransition(false)
				.InitiallyCollapsed(false)
				.HeaderPadding(SPadding::Left2x_Right2x)
				.Padding(SPadding::ContentAreaLeftIndent + SPadding::Right2x + SPadding::Top2x + SPadding::Bottom)
				.BorderImage(FStyleDefaults::GetNoBrush())
				.BodyBorderImage(FStyleDefaults::GetNoBrush())
				.BorderBackgroundColor(FColor::Transparent)
				.BodyBorderBackgroundColor(FColor::Transparent)
				.HeaderContent()
				[
					SNew(STextBlock)
						.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelperHeader)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kFieldBold)
				]
				.BodyContent()
				[
					SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(SPadding::Top_Bottom + SPadding::Right2x)
						[
							SNew(STextBlock)
								.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelper_Step1)
								.AutoWrapText(true)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)

						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(SPadding::Top_Bottom + SPadding::Right2x)
						[
							Command1Box.ToSharedRef()
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(SPadding::Top_Bottom + SPadding::Right2x)
						[
							SNew(STextBlock)
								.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelper_Step2)
								.AutoWrapText(true)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)

						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(SPadding::Top_Bottom + SPadding::Right2x)
						[
							SNew(SOnlineHyperlink)
								.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelper_Step2Link)
								.Link(Url::kECSCreateContainerImageUrl)
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(SPadding::Top_Bottom + SPadding::Right2x)
						[
							Command2Box.ToSharedRef()
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(SPadding::Top_Bottom + SPadding::Right2x)
						[
							SNew(STextBlock)
								.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelper_Step3)
								.AutoWrapText(true)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)

						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(SPadding::Top_Bottom + SPadding::Right2x)
						[
							Command3Box.ToSharedRef()
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(SPadding::Top_Bottom + SPadding::Right2x)
						[
							SNew(STextBlock)
								.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelper_Step4)
								.AutoWrapText(true)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)

						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(SPadding::Top_Bottom + SPadding::Right2x)
						[
							Command4Box.ToSharedRef()
						]
				]
		]
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(STextBlock)
				.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelper_ContinueText)
				.AutoWrapText(true)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SBox)
				.WidthOverride(Style::kContainersContinueButtonWidth)
				.HeightOverride(Style::kContainersContinueButtonHeight)
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				[
					SAssignNew(ContinueButton, SButton)
						.Text(Menu::DeployContainers::kBuildAndPushToECRDescription_CLIHelper_ContinueButtonText)
						.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
						.OnClicked_Raw(this, &SBuildAndPushToECRSection::OnContinueButtonClicked_CLISteps)
				]
		];

	return VerticalBox;
}

void SBuildAndPushToECRSection::ResetUIToNotStarted() {
	ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::NotStart);
	FText EmptyStatus = FText::FromString("-");
	ImageTagTextBlock->SetText(EmptyStatus);
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	ContainersStatus->ErrorRunningBuildAndPushScript = false;
	ContainersStatus->SaveConfig();
}

FReply SBuildAndPushToECRSection::OnContinueButtonClicked_CLISteps() {
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	ContainersStatus->IsContainerImagePushed = true;
	ContainersStatus->SaveConfig();
	UpdateUIBasedOnCurrentState();

	OnBuildAndPushFinishedDelegate.ExecuteIfBound();
	
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
