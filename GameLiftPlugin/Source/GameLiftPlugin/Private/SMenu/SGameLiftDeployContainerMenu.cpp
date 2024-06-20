// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftDeployContainerMenu.h"

#include <Async/Async.h>
#include <Widgets/SBoxPanel.h>

#include "GameLiftPlugin.h"
#include "IAWSScenariosDeployer.h"
#include "IGameLiftCoreModule.h"
#include "SCommonMenuSections.h"
#include "Settings/UGameLiftDeploymentStatus.h"
#include "Settings/UGameLiftInternalSettings.h"
#include "Settings/UGameLiftSettings.h"
#include "SWidgets/SContainerDeploymentFields.h"
#include "SWidgets/SDeploymentStatus.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SSectionsWithHeaders.h"
#include "SWidgets/SSelectionComboBox.h"
#include "SWidgets/SSetupMessage.h"
#include "SWidgets/STextSeparator.h"
#include "Types/EBootstrapMessageState.h"
#include "Utils/Misc.h"
#include "Utils/Notifier.h"
#include "Utils/StringPaths.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Text/SRichTextBlock.h"

namespace
{
	bool IsContainerDeploymentStatusActive()
	{
		UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();
		return EDeploymentMessageStateFromString(DeploySettings->Status.ToString()) == EDeploymentMessageState::ActiveMessage;
	}

	std::pair<bool, FText> HandleContainerStopButtonState(TSharedPtr<SWidget> DeploymentStatus)
	{
		bool IsDeploymentInProgress = AsSDeploymentStatusRef(DeploymentStatus)->GetCurrentState() == EDeploymentMessageState::InProgressMessage;
		if (IsDeploymentInProgress)
		{
			return { true, Menu::DeployManagedEC2::kStopDeploymentEnabledTooltip };
		}
		else
		{
			return { false, Menu::DeployManagedEC2::kStopDeploymentDisabledTooltip };
		}
	}

	std::pair<bool, FText> HandleContainerDeployButtonState(TSharedPtr<SWidget> DeploymentStatus, TSharedPtr<SWidget> DeploymentFields)
	{
		if (AsSContainerDeploymentFieldsRef(DeploymentFields)->GetGameName().IsEmptyOrWhitespace())
		{
			return { false, Menu::DeployContainers::kDeploymentDisabledGameNameEmptyTooltip };
		}

		if (AsSContainerDeploymentFieldsRef(DeploymentFields)->GetGameName().ToString().Len() > Menu::DeployContainers::kMaxContainerNamesLength)
		{
			return { false, Menu::DeployContainers::kDeploymentDisabledGameNameTooLongTooltip };
		}

		if (AsSContainerDeploymentFieldsRef(DeploymentFields)->GetContainerImageURI().IsEmptyOrWhitespace())
		{
			return { false, Menu::DeployContainers::kDeploymentDisabledContainerImageURINotSetTooltip };
		}

		if (AsSContainerDeploymentFieldsRef(DeploymentFields)->GetContainerImageURI().IsEmptyOrWhitespace())
		{
			return { false, Menu::DeployContainers::kDeploymentDisabledIntraContainerLaunchPathNotSetTooltip };
		}

		bool IsDeploymentInProgress = AsSDeploymentStatusRef(DeploymentStatus)->GetCurrentState() == EDeploymentMessageState::InProgressMessage;
		if (IsDeploymentInProgress)
		{
			return { false, Menu::DeployContainers::kDeploymentDisabledAlreadyActiveTooltip };
		}

		auto* Settings = GetMutableDefault<UGameLiftSettings>();
		bool IsBootstrapped = EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::ActiveMessage;
		if (!IsBootstrapped)
		{
			return { false, Menu::DeployContainers::kDeploymentDisabledNeedBootstrapTooltip };
		}

		return { true, Menu::DeployContainers::kDeploymentEnabledTooltip };
	}
}
	
#define LOCTEXT_NAMESPACE "SGameLiftDeployContainerContent"

void SGameLiftDeployContainerMenu::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;

	DeploymentStatus = SNew(SDeploymentStatus);

	BuildScenarioValues(IAWSScenariosCategory::Containers);

	const auto kRunDeploymentGameInfo = FText::Format(
		FText::FromString("<RichTextBlock.TextHighlight>{1}</>: {0}"),
		Menu::DeployManagedEC2::kRunDeploymentGameInfoText,
		Settings::kRichTextBlockNoteText);

	// Create the widgets
	TSharedPtr<SSectionsWithHeaders> SectionsWithHeaders = SNew(SSectionsWithHeaders);
	SectionsWithHeaders->AddSection((SNew(SSetProfileSection))->GetSectionInfo());
	SectionsWithHeaders->AddSection(
		(SNew(SIntegrateGameSection).HideBuildPathInput(true).HowToIntegrateYourGameLinkUrl(
			Url::kHowToIntegrateYourGameForEC2Url))->GetSectionInfo()
	);
	SectionsWithHeaders->AddSection(
		LOCTEXT("ContainersSelectDeploymentScenarioTitle", "3. Select deployment scenario"),
		CreateSelectDeploymentScenarioSection(),
		false
	);
	SectionsWithHeaders->AddSection(
		LOCTEXT("ContainersGameParametersTitle", "4. Set game parameters"),
		CreateGameParametersSection(),
		false
	);
	SectionsWithHeaders->AddSection(
		LOCTEXT("ContainersDeployTitle", "5. Deploy scenario"),
		CreateDeploySection(),
		false
	);
	SectionsWithHeaders->AddSection(
		LOCTEXT("ContainersLaunchClientTitle", "6. Launch client"),
		CreateLaunchClientSection(),
		false
	);

	ChildSlot
		.Padding(SPadding::Top_Bottom + SPadding::Extra_For_Page_End)
		// This adds more space at the bottom so users can scroll down further.
		[
			SectionsWithHeaders.ToSharedRef()
		];

	UGameLiftInternalSettings* Settings = GetMutableDefault<UGameLiftInternalSettings>();

	SetDefaultValues();
}

TSharedRef<SWidget> SGameLiftDeployContainerMenu::CreateSelectDeploymentScenarioSection()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(STextBlock)
			.Text(Menu::DeployManagedEC2::kSelectScenarioDescription)
			.AutoWrapText(true)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
		]
		// Links
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SOnlineHyperlink)
				.Text(Menu::DeployManagedEC2::kGameLiftHowToDeployYourFirstGameLinkText)
				.Link(Url::kGameLiftHowToDeployYourFirstGameUrl)
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
				.Text(Menu::DeployManagedEC2::kGameLiftEndpointsLinkText)
				.Link(Url::kGameLiftEndpointsUrl)
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
				.Text(Menu::DeployManagedEC2::kGameLiftPricingPlanLinkText)
				.Link(Url::kGameLiftPricingPlanUrl)
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
				.Text(Menu::DeployContainers::kGameLiftContainersHelpLinkText)
				.Link(Url::kGameLiftContainersHelpUrl)
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kSelectScenarioTitle)
			.RowWidget(
				SNew(SSelectionComboBox)
				.OnListBuilding_Raw(this, &SGameLiftDeployContainerMenu::OnBuildingDeploymentScenarioValues)
				.OnItemSelected_Raw(this, &SGameLiftDeployContainerMenu::OnDeploymentScenarioSelected)
			)
		];
}

TSharedRef<SWidget> SGameLiftDeployContainerMenu::CreateGameParametersSection()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		.AutoHeight()
		[
			SAssignNew(DeploymentFields, SContainerDeploymentFields)
		];
}

TSharedRef<SWidget> SGameLiftDeployContainerMenu::CreateDeploySection()
{
	return SNew(SVerticalBox)
		// Description
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SRichTextBlock)
			.Text(Menu::DeployManagedEC2::kDeploymentStatusInfoRichText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
			.DecoratorStyleSet(&FGameLiftPluginStyle::Get())
			.AutoWrapText(true)
		]
		// Deployment status
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Right2x) // Bottom padding is needed since SDeploymentStatus has already added the padding.
		[
			DeploymentStatus.ToSharedRef()
		]
		// Buttons
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kAwsResourceActionsText)
			.RowWidget(
				SNew(SHorizontalBox)
				// Button to create/redeploy
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.Padding(SPadding::Right2x)
				[
					SNew(SWidgetSwitcher)
					.WidgetIndex_Lambda([&]
					{
						UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();
						bool IsSameContainerNames = DeploySettings->GameName
						.EqualTo(AsSContainerDeploymentFieldsRef(DeploymentFields)->GetGameName());
						return IsContainerDeploymentStatusActive() && IsSameContainerNames ? 1 : 0;
					})
					+ SWidgetSwitcher::Slot()
					[
						SNew(SButton)
						.Text(Menu::DeployManagedEC2::kDeployCloudFormationButtonText)
						.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonLight)
						.ToolTipText_Lambda([&]()
						{
							return HandleContainerDeployButtonState(DeploymentStatus, DeploymentFields).second;
						})
						.OnClicked_Raw(this, &SGameLiftDeployContainerMenu::DeployCloudFormation)
						.IsEnabled_Lambda([&]()
						{
							return HandleContainerDeployButtonState(DeploymentStatus, DeploymentFields).first;
						})
					]
					+ SWidgetSwitcher::Slot()
					[
						SNew(SButton)
						.Text(Menu::DeployManagedEC2::kRedeployCloudFormationButtonText)
						.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
						.ToolTipText_Lambda([&]()
						{
							return HandleContainerDeployButtonState(DeploymentStatus, DeploymentFields).second;
						})
						.OnClicked_Raw(this, &SGameLiftDeployContainerMenu::DeployCloudFormation)
						.IsEnabled_Lambda([&]()
						{
							return HandleContainerDeployButtonState(DeploymentStatus, DeploymentFields).first;
						})
					]
				]
				// Button to stop
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.Padding(SPadding::Right2x)
				[
					SNew(SButton)
					.Text(Menu::DeployManagedEC2::kStopCloudFormationButtonText)
					.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kErrorButtonStyleName)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonLight)
					.ToolTipText_Lambda([&]()
					{
						return HandleContainerStopButtonState(DeploymentStatus).second;
					})
					.OnClicked_Raw(this, &SGameLiftDeployContainerMenu::StopDeploying)
					.IsEnabled_Lambda([&]()
					{
						return HandleContainerStopButtonState(DeploymentStatus).first;
					})
				]
				// Hyperlink
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Right)
				.Padding(SPadding::Right) // move the link left a bit
				[
					CreateCloudFormationInConsoleHyperLink()
				]
			)
		];
}

TSharedRef<SWidget> SGameLiftDeployContainerMenu::CreateLaunchClientSection()
{
	return SGameLiftDeployManagedEC2Menu::CreateLaunchClientSection();
}

void SGameLiftDeployContainerMenu::BuildScenarioValues(IAWSScenariosCategory Category)
{
	ScenarioNames.Reset();

	auto& Deployer = IGameLiftCoreModule::Get().GetScenarioDeployer();
	TArray<FText> Scenarios = Deployer.GetScenarios(Category);

	for (int i = 0; i < Scenarios.Num(); i++)
	{
		ScenarioNames.Add(Scenarios[i]);
	}
}

void SGameLiftDeployContainerMenu::OnBuildingDeploymentScenarioValues(TArray<FTextIntPair>& Items)
{
	Items.Reset();

	auto& Deployer = IGameLiftCoreModule::Get().GetScenarioDeployer();

	for (int32 Index = 0; Index < ScenarioNames.Num(); Index++)
	{
		Items.Add(FTextIntPair(
			ScenarioNames[Index],
			Index,
			Deployer.GetToolTip(ScenarioNames[Index], IAWSScenariosCategory::Containers)));
	}
}

void SGameLiftDeployContainerMenu::SetDefaultValues()
{
	UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();

	auto DeploymentInfo = AsSContainerDeploymentFieldsRef(DeploymentFields);
	DeploymentInfo->SetGameName(DeploySettings->GameName);
	DeploymentInfo->SetContainerImageURI(DeploySettings->ContainerImageURI);
	DeploymentInfo->SetIntraContainerLaunchPath(DeploySettings->IntraContainerLaunchPath);
	DeploymentInfo->SetExtraServerResourcesPath(DeploySettings->ContainerExtraServerResourcesPath);
	DeploymentInfo->SetOutConfigFilePath(DeploySettings->ContainerOutConfigFilePath);

	int previousScenarioSelected = ScenarioNames.FindLastByPredicate([&](const FText& name)
	{
		return name.EqualTo(DeploySettings->Scenario);
	});
	if (previousScenarioSelected != INDEX_NONE)
	{
		CurrentScenarioSelected = previousScenarioSelected;
	}
}

FReply SGameLiftDeployContainerMenu::DeployCloudFormation()
{
	if (Paths::DefaultOutConfigFilePath() != AsSContainerDeploymentFieldsRef(DeploymentFields)
		->GetOutConfigFilePath().ToString())
	{
		UE_LOG(GameLiftPluginLog, Warning, TEXT("%s"), Menu::DeployContainers::Logs::kOutputPathChangedWarning);
	}
	
	if (IsContainerDeploymentStatusActive())
	{
		auto choice = FMessageDialog::Open(
			EAppMsgType::YesNo,Menu::DeployManagedEC2::kConfirmReploymentText);
		if (choice != EAppReturnType::Yes) {
			return FReply::Handled();
		}
	}
	
	AsSDeploymentStatusRef(DeploymentStatus)->OnDeploy();
	
	auto DeploymentInfo = AsSContainerDeploymentFieldsRef(DeploymentFields);
	UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();
	DeploySettings->GameName = DeploymentInfo->GetGameName();
	DeploySettings->ContainerGroupDefinitionName = FText::FromString(DeploymentInfo->GetGameName().ToString() + FString("ContainerGroup"));
	DeploySettings->ContainerImageName = FText::FromString(DeploymentInfo->GetGameName().ToString() + FString("Container"));
	DeploySettings->ContainerImageURI = DeploymentInfo->GetContainerImageURI();
	DeploySettings->IntraContainerLaunchPath = DeploymentInfo->GetIntraContainerLaunchPath();
	DeploySettings->ExtraServerResourcesPath = DeploymentInfo->GetExtraServerResourcesPath();
	DeploySettings->OutConfigFilePath = DeploymentInfo->GetOutConfigFilePath();
	
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	DeploySettings->DeployedRegion = Settings->AwsRegion;
	DeploySettings->ApiGatewayEndpoint = FText::GetEmpty();
	DeploySettings->CognitoClientId = FText::GetEmpty();
	DeploySettings->SaveConfig();
	
	FText NotifyMessage = FText::GetEmpty();
	
	DeploySettings->Scenario = ScenarioNames[CurrentScenarioSelected];
	NotifyMessage = FText::Format(LOCTEXT("DeploymentNotificationAws", "{0}\n{1}"),
		FText::FromString(Menu::DeployContainers::kDeploymentStartedAwsScenarioNotification), DeploySettings->Scenario);
	
	DeploySettings->SaveConfig();
	
	NotificationItem = Notifier::CreateNotification(NotifyMessage);
	
	Async(EAsyncExecution::Thread, [
		NotificationItem = NotificationItem
	] () mutable
	{
		UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();
		auto& deployer = IGameLiftCoreModule::Get().GetScenarioDeployer();
	
		bool IsDeployed = deployer.DeployContainerScenario(
			DeploySettings->Scenario,
			IGameLiftCoreModule::Get().GetProfileBootstrap().GetAccountInstance(),
			DeploySettings->ContainerGroupDefinitionName.ToString(),
			DeploySettings->ContainerImageName.ToString(),
			DeploySettings->ContainerImageURI.ToString(),
			DeploySettings->IntraContainerLaunchPath.ToString(),
			DeploySettings->GameName.ToString(),
			DeploySettings->OutConfigFilePath.ToString()
		);
	
		UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
	
		if (IsDeployed)
		{
			UE_LOG(GameLiftPluginLog, Display, TEXT("%s"), Menu::DeployManagedEC2::Logs::kDeploymentSucceed);
	
			DeploySettings->ApiGatewayEndpoint = FText::FromString(deployer.GetLastApiGatewayEndpoint());
			DeploySettings->CognitoClientId = FText::FromString(deployer.GetLastCognitoClientId());
	
			Settings->Status = FText::FromString(EDeploymentMessageStateToString(EDeploymentMessageState::ActiveMessage));
			Notifier::CompleteWithSuccess(NotificationItem, Menu::DeployManagedEC2::kDeploymentCompletedNotification);
		}
		else
		{
			UE_LOG(GameLiftPluginLog, Display, TEXT("%s"), Menu::DeployManagedEC2::Logs::kDeploymentFailed);
	
			DeploySettings->LatestError = Utils::BuildLastestErrorMessage(deployer);
	
			Settings->Status = FText::FromString(EDeploymentMessageStateToString(EDeploymentMessageState::FailureMessage));
			Notifier::CompleteWithFailure(NotificationItem, Menu::DeployManagedEC2::kDeploymentFailedNotification);
		}
	
		DeploySettings->SaveConfig();
		Settings->SaveConfig();
	});
	
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
