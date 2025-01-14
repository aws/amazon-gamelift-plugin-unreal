// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SConnectAnywhereFleetMenu.h"

#include <Widgets/Layout/SWidgetSwitcher.h>
#include <Async/Async.h>

#include "SWidgets/SBootstrapStatus.h"
#include "SWidgets/SErrorBanner.h"
#include "SWidgets/SInputTextBox.h"
#include "SWidgets/STextStatus.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SSectionsWithHeaders.h"
#include "SWidgets/SSelectionComboBox.h"

#include "IGameLiftAnywhereHandler.h"
#include "IGameLiftCoreModule.h"
#include "GameLiftPlugin.h"
#include "GameLiftPluginStyle.h"
#include <Developer/Settings/Public/ISettingsModule.h>

#include "Settings/UGameLiftAnywhereStatus.h"
#include "Settings/UGameLiftSettings.h"
#include "Types/EBootstrapMessageState.h"
#include "Utils/StringPaths.h"
#include "Utils/Misc.h"

#define LOCTEXT_NAMESPACE "SConnectAnywhereFleetMenu"

void SConnectAnywhereFleetMenu::Construct(const FArguments& InArgs)
{
	OnFleetChangedDelegate = InArgs._OnFleetChangedDelegate;

	SSectionStep::Construct(
		SSectionStep::FArguments()
		.HeaderTitle(Menu::DeployAnywhere::kConnectToFleetHeader)
		.HeaderDescription(Menu::DeployAnywhere::kFleetSectionDescription)
		.BodyContent()
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Fill)
				[
					SAssignNew(DeployFleetErrorBanner, SErrorBanner)
						.ErrorText(Menu::DeployAnywhere::kLoadingFleetErrorText)
						.ErrorButtonText(Menu::DeployAnywhere::kLoadingFleetRetryText)
						.OnBannerButtonClicked_Raw(this, &SConnectAnywhereFleetMenu::OnRetryLoadingFleetInfo)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(SPadding::Bottom)
				[
					SNew(SOnlineHyperlink)
						.Text(Settings::AwsAccount::kAWSFreeTierLinkText)
						.Link(Settings::AwsAccount::kAWSFreeTierLinkUrl)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Fill)
				.Padding(SPadding::Top)
				[
					SAssignNew(ConnectToFleetWidgetSwitcher, SWidgetSwitcher)
						+ SWidgetSwitcher::Slot()
						[
							// input box that has "Create new fleet" and cancel button (depending on whether it has existing fleets or not)
							CreateAddNewFleetUI()
						]
						+ SWidgetSwitcher::Slot()
						[
							// it has create new anywhere fleet and selection box (with an inprogress state) when fleet selected, it is marked as done
							CreateChooseExistingFleetUI()
						]
				]
		]);

	// Listen to profile changes
	SGameLiftSettingsAwsAccountMenu::OnProfileSelectionChangedMultiDelegate.AddSP(this, &SConnectAnywhereFleetMenu::OnBootstrapStatusChanged);

	// Initialize section UI based on state
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	// If section not done and previous section not done
	if (!AnywhereStatus->IsFleetDeployed && AnywhereStatus->PathToServerBuild.IsEmpty())
	{
		ResetAndCollapseSection();
	}
	// If section not done, but previous is done
	else if (!AnywhereStatus->IsFleetDeployed)
	{
		StartSection();
	}
	// If section is done, and previous done
	else {
		DeployFleetErrorBanner->SetVisibility(EVisibility::Collapsed);
		ExistingFleetsComboBox->SetUnselectedText(FText::FromString(AnywhereStatus->FleetName));
		ConnectToFleetWidgetSwitcher->SetActiveWidgetIndex((int)EFleetSelectionUIState::ChooseExistingFleet);
		FleetIDRow->SetVisibility(EVisibility::Visible);
		FleetIDTextView->SetText(FText::FromString(AnywhereStatus->FleetId));
		SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressComplete);
		ModifyCreateButtonSwitcher->SetActiveWidgetIndex(1);
		ExistingFleetsComboBox->SetEnabled(false);
	}
}

void SConnectAnywhereFleetMenu::StartSection()
{
	// Default UI to show existing fleet selection until fleet data is loaded
	ClearSelectedFleet();
	ExistingFleetList.Reset();
	ExistingFleetsComboBox->SetEnabled(true);
	ExistingFleetsComboBox->SetUnselectedText(Menu::DeployAnywhere::kUnselectedFleetDropDownText);
	ChangeFleetSelectionUIState(EFleetSelectionUIState::ChooseExistingFleet);

	// Start loading fleet data
	if (CanEnableUI())
	{
		// Refresh the available fleets for the newly bootstrapped profile
		LoadFleetInfoAsync();
	}
}

void SConnectAnywhereFleetMenu::OnBootstrapStatusChanged(const SGameLiftSettingsAwsAccountMenu* /* Sender */)
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	EBootstrapMessageState BootstrapState = EBootstrapMessageStateFromInt(Settings->BootstrapStatus);
	if (BootstrapState == EBootstrapMessageState::NoBootstrappedMessage
		|| BootstrapState == EBootstrapMessageState::ActiveMessage)
	{
		ClearSelectedFleet();

		// Set UI to show existing fleet selection
		ExistingFleetList.Reset();
		ExistingFleetsComboBox->RequestToRebuildList();
		ExistingFleetsComboBox->ClearSelection();
		ExistingFleetsComboBox->SetUnselectedText(Menu::DeployAnywhere::kUnselectedFleetDropDownText);
		ChangeFleetSelectionUIState(EFleetSelectionUIState::ChooseExistingFleet);

		if (CanEnableUI())
		{
			// Refresh the available fleets for the newly bootstrapped profile
			LoadFleetInfoAsync();
		}
	}
}

void SConnectAnywhereFleetMenu::LoadFleetInfoAsync()
{
	IsLoadingFleetInfo = true;
	ExistingFleetsComboBox->SetUnselectedText(Menu::DeployAnywhere::kLoadingFleetDropDownText);

	// Hide error banner
	DeployFleetErrorBanner->SetVisibility(EVisibility::Collapsed);

	Async(EAsyncExecution::Thread,
		[this]()
		{
			// Get list of available Anywhere fleets
			IGameLiftAnywhereHandler& Handler = IGameLiftCoreModule::Get().GetGameLiftAnywhereHandler();
			GameLiftAnywhereDescribeFleetsResult ListFleetResult = Handler.DescribeAnywhereFleets();

			// Update UI on the main thread to avoid Slate errors such as SLATE_CROSS_THREAD_CHECK failure.
			Async(EAsyncExecution::TaskGraphMainThread,
				[this, ListFleetResult = MoveTemp(ListFleetResult)]
				{
					OnLoadFleetInfoComplete(ListFleetResult);
				});
		});
}

void SConnectAnywhereFleetMenu::OnLoadFleetInfoComplete(const GameLiftAnywhereDescribeFleetsResult& ListFleetResult)
{
	IsLoadingFleetInfo = false;
	ExistingFleetsComboBox->SetUnselectedText(Menu::DeployAnywhere::kUnselectedFleetDropDownText);

	if (ListFleetResult.bIsSuccessful)
	{
		// Update available fleet list
		OnAvailableFleetsChanged(ListFleetResult.Fleets);
	}
	else
	{
		// Show error banner
		DeployFleetErrorBanner->SetVisibility(EVisibility::Visible);
	}
}

void SConnectAnywhereFleetMenu::OnRetryLoadingFleetInfo()
{
	if (CanEnableUI())
	{
		// Refresh the available fleets for the current bootstrapped profile
		LoadFleetInfoAsync();
	}
}

void SConnectAnywhereFleetMenu::OnAvailableFleetsChanged(const TArray<GameLiftAnywhereDescribeFleetsResult::FleetAttributes>& Fleets)
{
	ExistingFleetList.Reset();

	for (const auto& Fleet : Fleets)
	{
		ExistingFleetList.Add(FTextIntPair(FText::FromString(Fleet.FleetName), ExistingFleetList.Num(), FText::FromString(Fleet.FleetId)));
	}

	ValidateCurrentlySelectedFleet();

	if (ExistingFleetList.Num() > 0)
	{
		ChangeFleetSelectionUIState(EFleetSelectionUIState::ChooseExistingFleet);
	}
	else
	{
		ChangeFleetSelectionUIState(EFleetSelectionUIState::CreateNewFleet);
	}
}

TSharedRef<SWidget> SConnectAnywhereFleetMenu::CreateAddNewFleetUI()
{
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox)
		// Anywhere fleet name text input
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployAnywhere::kNewFleetNameTitle)
			.RowWidget(
				SAssignNew(FleetNameTextInput, SEditableTextBox)
				.Text(GetDefaultFleetName())
				.HintText(Menu::DeployAnywhere::kNewFleetNameTextBoxHint)
			)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(STextBlock)
				.Text(Menu::DeployAnywhere::kFleetNameInstructionText)
				.AutoWrapText(true)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote)
			)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.Padding(SPadding::Top + SPadding::Right2x)
		[
			SAssignNew(DeployFleetErrorRow, SNamedRow)
				.SecondaryColumnLeftPadding(true)
				.RowWidget(
					SAssignNew(DeployFleetErrorTextBlock, STextBlock)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote)
					.AutoWrapText(true)
				)
				.Visibility(EVisibility::Collapsed)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.Padding(SPadding::Top3x + SPadding::Right2x)
		[
			SNew(SHorizontalBox)
			// Button to cancel adding new anywhere fleet
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.Padding(SPadding::Right2x)
			[
				SAssignNew(CancelButton, SButton)
				.Text(Menu::DeployAnywhere::kCancelButtonText)
				.OnClicked_Raw(this, &SConnectAnywhereFleetMenu::OnCancelFleetButtonClicked)
				.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
			]
			// Button to add a new anywhere fleet
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.Padding(SPadding::Right2x)
			[
				SNew(SButton)
				.Text(Menu::DeployAnywhere::kCreateFleetButtonText)
				.OnClicked_Raw(this, &SConnectAnywhereFleetMenu::OnCreateFleetButtonClicked)
				.IsEnabled_Raw(this, &SConnectAnywhereFleetMenu::CanCreateFleet)
				.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonLight)
			]
			// Loading indicator during fleet creation
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			[
				SNew(STextStatus)
				.IconState(STextStatus::EIconState::Loading)
				.Visibility_Lambda([&]
				{
					return IsLoading ? EVisibility::Visible : EVisibility::Hidden;
				})
			]
			// Hyperlink to see/manage available fleets in console
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			.HAlign(HAlign_Right)
			.Padding(SPadding::Right) // move the link left a bit
			[
				CreateFleetsInConsoleHyperLink()
			]
		];

	DeployFleetErrorTextBlock->SetColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kError));

	return VerticalBox;
}

TSharedRef<SWidget> SConnectAnywhereFleetMenu::CreateChooseExistingFleetUI()
{
	return SNew(SVerticalBox)
		// Anywhere fleet dropdown
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployAnywhere::kSelectedFleetTitle)
			.RowWidget(
				SAssignNew(ExistingFleetsComboBox, SSelectionComboBox)
				.UnselectedText(Menu::DeployAnywhere::kUnselectedFleetDropDownText)
				.OnListBuilding_Raw(this, &SConnectAnywhereFleetMenu::OnBuildExistingFleetValues)
				.OnItemSelected_Raw(this, &SConnectAnywhereFleetMenu::OnExistingFleetSelected)
				.IsEnabled_Raw(this, &SConnectAnywhereFleetMenu::CanEnableFleetSelectionUI)
			)
		]
		// Anywhere fleet ID
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SAssignNew(FleetIDRow, SNamedRow)
			.NameText(Menu::DeployAnywhere::kSelectedFleetIDTitle)
			.RowWidget(
				SAssignNew(FleetIDTextView, SEditableText)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
				.IsReadOnly(true)
			)
			.SecondaryColumnLeftPadding(true)
		]
		// Button to add a new Anywhere fleet
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.Padding(SPadding::Right)
			[
				SAssignNew(ModifyCreateButtonSwitcher, SWidgetSwitcher)
					+ SWidgetSwitcher::Slot()
					[
						SAssignNew(AddFleetButton, SButton)
							.Text(Menu::DeployAnywhere::kGoToCreateFleetButtonText)
							.OnClicked_Raw(this, &SConnectAnywhereFleetMenu::OnGoToCreateFleetButtonClicked)
							.IsEnabled_Raw(this, &SConnectAnywhereFleetMenu::CanEnableUI)
							.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
							.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
					]
					+ SWidgetSwitcher::Slot()
					[
						// modify button
						SAssignNew(ModifyButton, SButton)
							.Text(Menu::DeployAnywhere::kModifyAnywhereFleet)
							.OnClicked_Raw(this, &SConnectAnywhereFleetMenu::OnModifyButtonClicked)
							.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
							.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
					]
			]
			// Hyperlink to fleet list in console for current region
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			.HAlign(HAlign_Right)
			.Padding(SPadding::Right) // move the link left a bit
			[
				CreateFleetsInConsoleHyperLink()
			]
		];
}

FReply SConnectAnywhereFleetMenu::OnModifyButtonClicked()
{
	ResetAndCollapseNextSections();

	return FReply::Handled();
}

TSharedRef<SWidget> SConnectAnywhereFleetMenu::CreateFleetsInConsoleHyperLink()
{
	return SNew(SOnlineHyperlink)
		.Text(Menu::DeployAnywhere::kViewInGameLiftConsoleHyperLinkText)
		.Link_Lambda([&]
		{
			// Update link with the region associated with the currently selected profile
			FString CurrentAwsRegion(TEXT("us-west-2"));
			UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
			if (Settings && !Settings->AwsRegion.IsEmpty())
			{
				CurrentAwsRegion = Settings->AwsRegion.ToString();
			}
			return (FString::Format(Menu::DeployAnywhere::kViewInGameLiftConsoleHyperLinkUrlFormat, { CurrentAwsRegion }));
		});
}

FReply SConnectAnywhereFleetMenu::OnCreateFleetButtonClicked()
{
	FString FleetName = FleetNameTextInput->GetText().ToString().TrimStartAndEnd();

	// Validate input
	if (FleetName.IsEmpty())
	{
		return FReply::Handled();
	}

	IsLoading = true;
	SetProgressBarState(SProgressBar::EProgressBarUIState::InProgress);
	FleetNameTextInput->SetIsReadOnly(true);
	if (CancelButton->GetVisibility() == EVisibility::Visible)
	{
		CancelButton->SetVisibility(EVisibility::Collapsed);
	}

	Async(EAsyncExecution::Thread,
		// Move or copy is needed here so the new thread can always access the variable.
		[this, FleetName = MoveTemp(FleetName)]()
		{
			TTuple<FString, FString> FleetIdResult = CreateCustomLocationAndFleet(FleetName);

			IsLoading = false;

			// Have to update UI in this new thread otherwise SLATE_CROSS_THREAD_CHECK will fail.
			// This is because updates in switcher widget can only happen in the game thread or Slate thread.
			// Note: There could be a better solution here.
			Async(EAsyncExecution::TaskGraphMainThread,
				[this, FleetNameCopy = FleetName, FleetIdResult = MoveTemp(FleetIdResult)]
				{
					if (!FleetIdResult.Get<0>().IsEmpty())
					{
						AddNewAnywhereFleet(FleetNameCopy, FleetIdResult.Get<0>());
						UpdateErrorMessage(FText::GetEmpty()); // added this to mimic other section
						ChangeFleetSelectionUIState(EFleetSelectionUIState::ChooseExistingFleet);
					}
					else
					{
						UpdateErrorMessage(FText::FromString(FleetIdResult.Get<1>()));
						SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressError);
					}

					FleetNameTextInput->SetIsReadOnly(false);
					CancelButton->SetVisibility(EVisibility::Visible);
				});
		});

	return FReply::Handled();
}

FReply SConnectAnywhereFleetMenu::OnGoToCreateFleetButtonClicked()
{
	ChangeFleetSelectionUIState(EFleetSelectionUIState::CreateNewFleet);

	return FReply::Handled();
}

FReply SConnectAnywhereFleetMenu::OnCancelFleetButtonClicked()
{
	ChangeFleetSelectionUIState(EFleetSelectionUIState::ChooseExistingFleet);

	return FReply::Handled();
}

TTuple<FString, FString> SConnectAnywhereFleetMenu::CreateCustomLocation()
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	FString AwsRegion = Settings->AwsRegion.ToString();

	IGameLiftAnywhereHandler& Handler = IGameLiftCoreModule::Get().GetGameLiftAnywhereHandler();
	GameLiftAnywhereCreateLocationResult CreateLocationResult = Handler.CreateCustomLocation(AwsRegion);

	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	if (CreateLocationResult.bIsSuccessful)
	{
		AnywhereStatus->CustomLocation = CreateLocationResult.LocationName;
		AnywhereStatus->DeployedRegion = AwsRegion;
		AnywhereStatus->SaveConfig();

		return MakeTuple(CreateLocationResult.LocationName, TEXT(""));
	}
	else
	{
		return MakeTuple(TEXT(""), CreateLocationResult.ErrorMessage);
	}
}

TTuple<FString, FString> SConnectAnywhereFleetMenu::CreateCustomLocationAndFleet(const FString& InFleetName)
{
	// Create a custom location for the current AWS region used in the profile.
	TTuple<FString, FString> CreateLocationResult = CreateCustomLocation();
	const FString LocationName = CreateLocationResult.Get<0>();
	if (LocationName.IsEmpty())
	{
		// Failed to create custom location.
		return CreateLocationResult;
	}

	// Create an Anywhere fleet.
	IGameLiftAnywhereHandler& Handler = IGameLiftCoreModule::Get().GetGameLiftAnywhereHandler();
	GameLiftAnywhereCreateFleetResult CreateFleetResult = Handler.CreateFleet(InFleetName, LocationName);

	if (CreateFleetResult.bIsSuccessful)
	{
		return MakeTuple(CreateFleetResult.FleetId, TEXT(""));
	}
	else
	{
		return MakeTuple(TEXT(""), CreateFleetResult.ErrorMessage);
	}
}

void SConnectAnywhereFleetMenu::AddNewAnywhereFleet(const FString& InFleetName, const FString& InFleetId)
{
	// Add new Anywhere fleet
	ExistingFleetList.Add(FTextIntPair(FText::FromString(InFleetName), ExistingFleetList.Num(), FText::FromString(InFleetId)));

	// Set selected Anywhere fleet
	SaveSelectedFleet(InFleetName, InFleetId);
}

bool SConnectAnywhereFleetMenu::CanCreateFleet() const
{
	return CanEnableUI() && !FleetNameTextInput->GetText().IsEmpty();
}

bool SConnectAnywhereFleetMenu::CanEnableFleetSelectionUI() const
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	return EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::ActiveMessage
		&& !IsLoading;
}

bool SConnectAnywhereFleetMenu::CanEnableUI() const
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	return EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::ActiveMessage
		&& !IsLoading && !IsLoadingFleetInfo;
}

void SConnectAnywhereFleetMenu::ChangeFleetSelectionUIState(EFleetSelectionUIState InState)
{
	ConnectToFleetWidgetSwitcher->SetActiveWidgetIndex(FleetSelectionUIStateToInt(InState));

	UpdateContentForCurrentUIState();
}

void SConnectAnywhereFleetMenu::UpdateContentForCurrentUIState()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	
	// Hide error banner
	DeployFleetErrorBanner->SetVisibility(EVisibility::Collapsed);

	if (ConnectToFleetWidgetSwitcher->GetActiveWidgetIndex() == FleetSelectionUIStateToInt(EFleetSelectionUIState::CreateNewFleet))
	{
		// Update UI for creating a new fleet
		bool HasExistingFleets = HaveExistingFleets();
		CancelButton->SetVisibility(HasExistingFleets ? EVisibility::Visible : EVisibility::Collapsed);
		if (HasExistingFleets)
		{
			SetProgressBarState(SProgressBar::EProgressBarUIState::NotStart);
		}
	}
	else
	{
		// Update UI for selecting an existing fleet
		ExistingFleetsComboBox->RequestToRebuildList();

		ExistingFleetsComboBox->SetSelectedByName(FText::FromString(AnywhereStatus->FleetName));

		if (ExistingFleetsComboBox->IsCurrentSelectionValid())
		{
			FleetIDRow->SetVisibility(EVisibility::Visible);
			FleetIDTextView->SetText(FText::FromString(AnywhereStatus->FleetId));
			SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressComplete);
			ModifyCreateButtonSwitcher->SetActiveWidgetIndex(1);
			ExistingFleetsComboBox->SetEnabled(false);
			StartNextSection();
		}
		else
		{
			if (ExistingFleetList.Num() > 0) // We use Num instead of IsEmpty to maintain UE4 compatibility.
			{
				// Can't find previously selected fleet, so clear it.
				ClearSelectedFleet();
			}
			FleetIDRow->SetVisibility(EVisibility::Collapsed);
			ModifyCreateButtonSwitcher->SetActiveWidgetIndex(0);
			SetProgressBarState(SProgressBar::EProgressBarUIState::NotStart);
		}
	}
}

void SConnectAnywhereFleetMenu::OnSelectedFleetChanged()
{
	// Called when a user creates a new fleet or changes to another existing fleet
	OnFleetChangedDelegate.ExecuteIfBound();
}

bool SConnectAnywhereFleetMenu::HaveExistingFleets() const
{
	return ExistingFleetList.Num() > 0;
}

bool SConnectAnywhereFleetMenu::IsFleetSelected() const
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	return !AnywhereStatus->FleetName.IsEmpty();
}

void SConnectAnywhereFleetMenu::SaveSelectedFleet(const FString& InFleetName, const FString& InFleetId)
{
	if (InFleetName.IsEmpty() || InFleetId.IsEmpty())
	{
		ClearSelectedFleet();
	}
	else
	{
		UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
		if (AnywhereStatus->FleetName != InFleetName
			|| AnywhereStatus->FleetId != InFleetId
			|| !AnywhereStatus->IsFleetDeployed)
		{
			AnywhereStatus->FleetName = InFleetName;
			AnywhereStatus->FleetId = InFleetId;
			AnywhereStatus->IsFleetDeployed = true;

			AnywhereStatus->SaveConfig();

			OnSelectedFleetChanged();
		}
	}
}

void SConnectAnywhereFleetMenu::ClearSelectedFleet()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	if (AnywhereStatus->IsFleetDeployed)
	{
		AnywhereStatus->FleetName.Empty();
		AnywhereStatus->FleetId.Empty();
		AnywhereStatus->IsFleetDeployed = false;

		AnywhereStatus->SaveConfig();

		ExistingFleetsComboBox->ClearSelection();

		OnSelectedFleetChanged();
	}
}

void SConnectAnywhereFleetMenu::ValidateCurrentlySelectedFleet()
{
	// Check if the currently selected fleet is still available
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	if (AnywhereStatus->IsFleetDeployed)
	{
		bool SelectedFleetExists = false;
		for (const FTextIntPair& ExistingFleet : ExistingFleetList)
		{
			if ((ExistingFleet.Text.ToString() == AnywhereStatus->FleetName)
				&& (ExistingFleet.Description.ToString() == AnywhereStatus->FleetId))
			{
				SelectedFleetExists = true;
				break;
			}
		}
		if (!SelectedFleetExists)
		{
			ClearSelectedFleet();
		}
	}
}

void SConnectAnywhereFleetMenu::OnBuildExistingFleetValues(TArray<FTextIntPair>& Items)
{
	Items.Reset();

	for (const FTextIntPair& ExistingFleet : ExistingFleetList)
	{
		Items.Add(ExistingFleet);
	}
}

void SConnectAnywhereFleetMenu::OnExistingFleetSelected(int SelectionId, const FTextIntPair& Items)
{
	// Change which fleet is selected
	SaveSelectedFleet(Items.Text.ToString(), Items.Description.ToString());

	UpdateContentForCurrentUIState();
}

void SConnectAnywhereFleetMenu::UpdateErrorMessage(const FText& ErrorMessage)
{
	if (ErrorMessage.IsEmpty())
	{
		DeployFleetErrorRow->SetVisibility(EVisibility::Collapsed);
		DeployFleetErrorTextBlock->SetText(FText::GetEmpty());
	}
	else
	{
		DeployFleetErrorRow->SetVisibility(EVisibility::Visible);
		DeployFleetErrorTextBlock->SetText(ErrorMessage);
	}
}

FText SConnectAnywhereFleetMenu::GetDefaultFleetName() const
{
	FString DefaultFleetName = FString::Format(TEXT("{0}-AnywhereFleet"), { FApp::GetProjectName() });
	return FText::FromString(DefaultFleetName);
}

#undef LOCTEXT_NAMESPACE
