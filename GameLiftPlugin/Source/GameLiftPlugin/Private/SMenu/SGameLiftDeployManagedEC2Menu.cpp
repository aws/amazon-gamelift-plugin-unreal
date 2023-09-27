// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftDeployManagedEC2Menu.h"

#include <Widgets/SBoxPanel.h>
#include <Widgets/Text/SRichTextBlock.h>
#include "Widgets/Layout/SWidgetSwitcher.h"
#include <Framework/MetaData/DriverMetaData.h>

#include "SCommonMenuSections.h"
#include "SWidgets/SBootstrapStatus.h"
#include "SWidgets/SDeploymentFields.h"
#include "SWidgets/SDeploymentStatus.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SPathInput.h"
#include "SWidgets/SSectionsWithHeaders.h"
#include "SWidgets/SSetupMessage.h"
#include "SWidgets/STextStatus.h"
#include "SWidgets/SSelectionComboBox.h"
#include "SWidgets/STextSeparator.h"

#include "Settings/UGameLiftDeploymentStatus.h"
#include "Settings/UGameLiftInternalSettings.h"
#include "Settings/UGameLiftSettings.h"

#include "Utils/Misc.h"
#include "Utils/Notifier.h"
#include "Utils/StringPaths.h"
#include <Async/Async.h>

#include "Types/EDeploymentMessageState.h"

#include "IGameLiftCoreModule.h"
#include "GameLiftPlugin.h"
#include <Developer/Settings/Public/ISettingsModule.h>

namespace
{
	bool IsDeploymentStatusActive()
	{
		UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();
		return EDeploymentMessageStateFromString(DeploySettings->Status.ToString()) == EDeploymentMessageState::ActiveMessage;
	}

	std::pair<bool, FText> HandleStopButtonState(TSharedPtr<SWidget> DeploymentStatus)
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

	std::pair<bool, FText> HandleDeployButtonState(TSharedPtr<SWidget> DeploymentStatus, TSharedPtr<SWidget> DeploymentFields)
	{
		if (AsSDeploymentFieldsRef(DeploymentFields)->GetBuildName().IsEmptyOrWhitespace())
		{
			return { false, Menu::DeployManagedEC2::kDeploymentDisabledBuildNameEmptyTooltip };
		}

		if (AsSDeploymentFieldsRef(DeploymentFields)->GetBuildName().ToString().Len() > Menu::DeployManagedEC2::kMaxGameNameLength)
		{
			return { false, Menu::DeployManagedEC2::kDeploymentDisabledBuildNameTooLongTooltip };
		}

		if (AsSDeploymentFieldsRef(DeploymentFields)->GetBuildFilePath().IsEmptyOrWhitespace() || AsSDeploymentFieldsRef(DeploymentFields)->GetBuildFolderPath().IsEmptyOrWhitespace())
		{
			return { false, Menu::DeployManagedEC2::kDeploymentDisabledServerBuildPathNotSetTooltip };
		}

		bool IsDeploymentInProgress = AsSDeploymentStatusRef(DeploymentStatus)->GetCurrentState() == EDeploymentMessageState::InProgressMessage;
		if (IsDeploymentInProgress)
		{
			return { false, Menu::DeployManagedEC2::kDeploymentDisabledAlreadyActiveTooltip };
		}

		auto* Settings = GetMutableDefault<UGameLiftSettings>();
		bool IsBootstrapped = EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::ActiveMessage;
		if (!IsBootstrapped)
		{
			return { false, Menu::DeployManagedEC2::kDeploymentDisabledNeedBootstrapTooltip };
		}

		return { true, Menu::DeployManagedEC2::kDeploymentEnabledTooltip };
	}
}

#define LOCTEXT_NAMESPACE "SGameLiftDeployManagedEC2Content"

namespace Internal
{
	bool IsDeployed()
	{
		auto* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
		return EDeploymentMessageStateFromString(Settings->Status.ToString()) == EDeploymentMessageState::ActiveMessage;
	}
} // namespace Internal

void SGameLiftDeployManagedEC2Menu::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;

	DeploymentStatus = SNew(SDeploymentStatus);

	BuildScenarioValues();

	const auto kRunDeploymentGameInfo = FText::Format(FText::FromString("<RichTextBlock.TextHighlight>{1}</>: {0}"), Menu::DeployManagedEC2::kRunDeploymentGameInfoText, Settings::kRichTextBlockNoteText);

	// Create the widgets
	TSharedPtr<SSectionsWithHeaders> SectionsWithHeaders = SNew(SSectionsWithHeaders);
	SectionsWithHeaders->AddSection((SNew(SSetProfileSection))->GetSectionInfo());
	SectionsWithHeaders->AddSection((SNew(SIntegrateGameSection).HideBuildPathInput(true).HowToIntegrateYourGameLinkUrl(Url::kHowToIntegrateYourGameForEC2Url))->GetSectionInfo());
	SectionsWithHeaders->AddSection(LOCTEXT("ManagedEC2SelectDeploymentScenarioTitle", "3. Select deployment scenario"), CreateSelectDeploymentScenarioSection(), false);
	SectionsWithHeaders->AddSection(LOCTEXT("ManagedEC2GameParametersTitle", "4. Set game parameters"), CreateGameParametersSection(), false);
	SectionsWithHeaders->AddSection(LOCTEXT("ManagedEC2DeployTitle", "5. Deploy scenario"), CreateDeploySection(), false);
	SectionsWithHeaders->AddSection(LOCTEXT("ManagedEC2LaunchClientTitle", "6. Launch client"), CreateLaunchClientSection(), false);

	ChildSlot
		.Padding(SPadding::Top_Bottom + SPadding::Extra_For_Page_End) // This adds more space at the bottom so users can scroll down further.
		[
			SectionsWithHeaders.ToSharedRef()
		];

	UGameLiftInternalSettings* Settings = GetMutableDefault<UGameLiftInternalSettings>();

	SetDefaultValues();
}

TSharedRef<SWidget> SGameLiftDeployManagedEC2Menu::CreateSelectDeploymentScenarioSection()
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
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kSelectScenarioTitle)
			.RowWidget(
				SNew(SSelectionComboBox)
				.OnListBuilding_Raw(this, &SGameLiftDeployManagedEC2Menu::OnBuildingDeploymentScenarioValues)
				.OnItemSelected_Raw(this, &SGameLiftDeployManagedEC2Menu::OnDeploymentScenarioSelected)
			)
		];
}

void SGameLiftDeployManagedEC2Menu::OnBuildingDeploymentScenarioValues(TArray<FTextIntPair>& Items)
{
	Items.Reset();

	auto& Deployer = IGameLiftCoreModule::Get().GetScenarioDeployer();

	for (int32 Index = 0; Index < ScenarioNames.Num(); Index++)
	{
		Items.Add(FTextIntPair(ScenarioNames[Index], Index, Deployer.GetToolTip(ScenarioNames[Index])));
	}
}

void SGameLiftDeployManagedEC2Menu::OnDeploymentScenarioSelected(int SelectionId, const FTextIntPair& Item)
{
	CurrentScenarioSelected = SelectionId;
}

TSharedRef<SWidget> SGameLiftDeployManagedEC2Menu::CreateGameParametersSection()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		.AutoHeight()
		[
			SAssignNew(DeploymentFields, SDeploymentFields)
		];
}

TSharedRef<SWidget> SGameLiftDeployManagedEC2Menu::CreateDeploySection()
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
						bool IsSameGameName = DeploySettings->BuildName.EqualTo(AsSDeploymentFieldsRef(DeploymentFields)->GetBuildName());
						return IsDeploymentStatusActive() && IsSameGameName ? 1 : 0;
					})
					+ SWidgetSwitcher::Slot()
					[
						SNew(SButton)
						.Text(Menu::DeployManagedEC2::kDeployCloudFormationButtonText)
						.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonLight)
						.ToolTipText_Lambda([&]()
						{
							return HandleDeployButtonState(DeploymentStatus, DeploymentFields).second;
						})
						.OnClicked_Raw(this, &SGameLiftDeployManagedEC2Menu::DeployCloudFormation)
						.IsEnabled_Lambda([&]()
						{
							return HandleDeployButtonState(DeploymentStatus, DeploymentFields).first;
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
							return HandleDeployButtonState(DeploymentStatus, DeploymentFields).second;
						})
						.OnClicked_Raw(this, &SGameLiftDeployManagedEC2Menu::DeployCloudFormation)
						.IsEnabled_Lambda([&]()
						{
							return HandleDeployButtonState(DeploymentStatus, DeploymentFields).first;
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
						return HandleStopButtonState(DeploymentStatus).second;
					})
					.OnClicked_Raw(this, &SGameLiftDeployManagedEC2Menu::StopDeploying)
					.IsEnabled_Lambda([&]()
					{
						return HandleStopButtonState(DeploymentStatus).first;
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

TSharedRef<SWidget> SGameLiftDeployManagedEC2Menu::CreateLaunchClientSection()
{
	TSharedPtr<SSetupMessage> GameClientMessage = SNew(SSetupMessage)
		.ReadyToGoText(Menu::DeployManagedEC2::kDeployedGameClientRunningMessage)
		.WarningText(Menu::DeployManagedEC2::kDeployedGameClientFailureMessage);

	return SNew(SVerticalBox)	
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kGameClientPathText)
			.RowWidget(
				SAssignNew(GameClientPathInput, SPathInput)
				.Title(Menu::DeployManagedEC2::kGameClientPathText)
				.PathHint(Menu::DeployManagedEC2::kGameClientPathHint)
			)
		]
		+ SVerticalBox::Slot()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		.AutoHeight()
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kLaunchGameClientText)
			.RowWidget(
				SNew(SHorizontalBox)
				// Button to launch client
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.Padding(SPadding::Right2x)
				[
					SNew(SButton)
					.Text(Menu::DeployManagedEC2::kLaunchGameClientButtonText)
					.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonLight)
					.OnClicked_Lambda([this, MessageWidget = GameClientMessage.ToSharedRef()]()
					{
						IsLaunchingGameClient = true;

						FText path = GameClientPathInput->GetSelectedPath();

						UGameLiftInternalSettings* Settings = GetMutableDefault<UGameLiftInternalSettings>();
						Settings->DeployGameClientPath.FilePath = path.ToString();
						Settings->SaveConfig();

						TArray<FString> Args;
						FString RunPath = Utils::Splitters::ExtractPathArgs(path, Args);

						Async(EAsyncExecution::Thread, [this, RunPath = MoveTemp(RunPath), Args = MoveTemp(Args), MessageWidget
						]()
						{
							auto runner = IGameLiftCoreModule::Get().MakeRunner();
							bool isLaunched = runner->LaunchProcess(RunPath, Args);
							Utils::ShowLaunchProcessMessage(MessageWidget, isLaunched);

							IsLaunchingGameClient = false;
						});

						return FReply::Handled();
					})
					.IsEnabled_Raw(this, &SGameLiftDeployManagedEC2Menu::CanLaunchGameClient)
					.ToolTipText_Raw(this, &SGameLiftDeployManagedEC2Menu::TooltipLaunchGameClient)
				]
				// Loading indicator
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				[
					SNew(STextStatus)
					.IconState(STextStatus::EIconState::Loading)
					.Visibility_Lambda([&]
					{
						return IsLaunchingGameClient ? EVisibility::Visible : EVisibility::Hidden;
					})
				]
			)
		];
}

void SGameLiftDeployManagedEC2Menu::SetDefaultValues()
{
	UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();

	auto DeploymentInfo = AsSDeploymentFieldsRef(DeploymentFields);
	DeploymentInfo->SetBuildName(DeploySettings->BuildName);
	DeploymentInfo->SetBuildOperatingSystem(DeploySettings->BuildOperatingSystem);
	DeploymentInfo->SetBuildFolderPath(DeploySettings->BuildFolderPath);
	DeploymentInfo->SetBuildFilePath(DeploySettings->BuildFilePath);
	DeploymentInfo->SetExtraServerResourcesPath(DeploySettings->ExtraServerResourcesPath);
	DeploymentInfo->SetOutConfigFilePath(DeploySettings->OutConfigFilePath);

	AsSDeploymentStatusRef(DeploymentStatus)->SetState(EDeploymentMessageStateFromString(DeploySettings->Status.ToString()));

	int previousScenarioSelected = ScenarioNames.FindLastByPredicate([&](const FText& name)
	{
		return name.EqualTo(DeploySettings->Scenario);
	});
	if (previousScenarioSelected != INDEX_NONE)
	{
		CurrentScenarioSelected = previousScenarioSelected;
	}
}

void SGameLiftDeployManagedEC2Menu::BuildScenarioValues()
{
	ScenarioNames.Reset();

	auto& Deployer = IGameLiftCoreModule::Get().GetScenarioDeployer();
	TArray<FText> Scenarios = Deployer.GetScenarios();

	for (int i = 0; i < Scenarios.Num(); i++)
	{
		ScenarioNames.Add(Scenarios[i]);
	}
}

void SGameLiftDeployManagedEC2Menu::SwitchDeploymentFields()
{
	AsSDeploymentFieldsRef(DeploymentFields)->SetFullMode();
}

FReply SGameLiftDeployManagedEC2Menu::DeployCloudFormation()
{
	if (Paths::DefaultOutConfigFilePath() != AsSDeploymentFieldsRef(DeploymentFields)->GetOutConfigFilePath().ToString())
	{
		UE_LOG(GameLiftPluginLog, Warning, TEXT("%s"), Menu::DeployManagedEC2::Logs::kOutputPathChangedWarning);
	}

	if (IsDeploymentStatusActive())
	{
		auto choice = FMessageDialog::Open(EAppMsgType::YesNo, Menu::DeployManagedEC2::kConfirmReploymentText);
		if (choice != EAppReturnType::Yes) {
			return FReply::Handled();
		}
	}

	AsSDeploymentStatusRef(DeploymentStatus)->OnDeploy();

	auto DeploymentInfo = AsSDeploymentFieldsRef(DeploymentFields);
	UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();
	DeploySettings->BuildName = DeploymentInfo->GetBuildName();
	DeploySettings->BuildOperatingSystem = DeploymentInfo->GetBuildOperatingSystem();
	DeploySettings->BuildFolderPath = DeploymentInfo->GetBuildFolderPath();
	DeploySettings->BuildFilePath = DeploymentInfo->GetBuildFilePath();
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
		FText::FromString(Menu::DeployManagedEC2::kDeploymentStartedAwsScenarioNotification), DeploySettings->Scenario);

	DeploySettings->SaveConfig();

	NotificationItem = Notifier::CreateNotification(NotifyMessage);

	Async(EAsyncExecution::Thread, [
		NotificationItem = NotificationItem
	] () mutable
	{
		UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();
		auto& deployer = IGameLiftCoreModule::Get().GetScenarioDeployer();

		bool IsDeployed = deployer.DeployScenario(
			DeploySettings->Scenario,
			IGameLiftCoreModule::Get().GetProfileBootstrap().GetAccountInstance(),
			DeploySettings->BuildName.ToString(),
			DeploySettings->BuildOperatingSystem.ToString(),
			DeploySettings->BuildFolderPath.ToString(),
			DeploySettings->BuildFilePath.ToString(),
			DeploySettings->OutConfigFilePath.ToString(),
			DeploySettings->ExtraServerResourcesPath.ToString()
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

FReply SGameLiftDeployManagedEC2Menu::StopDeploying()
{
	auto choice = FMessageDialog::Open(EAppMsgType::YesNo, Menu::DeployManagedEC2::kConfirmStopDeploymentText);

	if (choice != EAppReturnType::Yes)
	{
		return FReply::Handled();
	}

	Async(EAsyncExecution::Thread, [Status = DeploymentStatus, NotificationItem = NotificationItem]()
	{
		auto& deployer = IGameLiftCoreModule::Get().GetScenarioDeployer();
		if (deployer.StopDeployment(IGameLiftCoreModule::Get().GetProfileBootstrap().GetAccountInstance()))
		{
			AsSDeploymentStatusRef(Status)->OnAbort();
			Notifier::UpdateTextNotification(NotificationItem, Menu::DeployManagedEC2::kDeploymentAbortedNotification);
		}
		else
		{
			AsSDeploymentStatusRef(Status)->OnFailure();
			Notifier::CompleteWithFailure(NotificationItem, Menu::DeployManagedEC2::kDeploymentFailedNotification);
		}
	});

	return FReply::Handled();
}

bool SGameLiftDeployManagedEC2Menu::CanLaunchGameClient() const
{
	const FText& SelectedPath = GameClientPathInput->GetSelectedPathRef();
	return !SelectedPath.IsEmptyOrWhitespace() && !IsLaunchingGameClient && Internal::IsDeployed();
}

FText SGameLiftDeployManagedEC2Menu::TooltipLaunchGameClient() const
{
	if (!Internal::IsDeployed())
	{
		return Menu::DeployManagedEC2::kCannotLaunchGameClientNoDeploymentTooltipText;
	}

	const FText& SelectedPath = GameClientPathInput->GetSelectedPathRef();

	if (SelectedPath.IsEmptyOrWhitespace())
	{
		return Menu::DeployManagedEC2::kCannotLaunchGameClientNoPathTooltipText;
	}

	return Menu::DeployManagedEC2::kCanLaunchGameClientTooltipText;
}

TSharedRef<SWidget> SGameLiftDeployManagedEC2Menu::CreateCloudFormationInConsoleHyperLink()
{
	return SNew(SOnlineHyperlink)
		.Text(Menu::DeployManagedEC2::kViewInCloudFormationConsoleHyperLinkText)
		.Link_Lambda([&]
		{
			// Update link with the region associated with the currently selected profile
			FString CurrentAwsRegion(TEXT("us-west-2"));
			UGameLiftDeploymentStatus* DeploymentStatus = GetMutableDefault<UGameLiftDeploymentStatus>();
			if (DeploymentStatus && !DeploymentStatus->DeployedRegion.IsEmpty())
			{
				CurrentAwsRegion = DeploymentStatus->DeployedRegion.ToString();
			}
			return FString::Format(Menu::DeployManagedEC2::kViewInCloudFormationHyperLinkUrlFormat, { CurrentAwsRegion });
		});
}

#undef LOCTEXT_NAMESPACE
