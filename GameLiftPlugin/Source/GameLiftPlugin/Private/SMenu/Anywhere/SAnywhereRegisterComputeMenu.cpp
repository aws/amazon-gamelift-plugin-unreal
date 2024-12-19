// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SAnywhereRegisterComputeMenu.h"

#include <Widgets/Layout/SWidgetSwitcher.h>
#include <Async/Async.h>

#include "SWidgets/SInputTextBox.h"
#include "SWidgets/SIPAddressTextBox.h"
#include "SWidgets/STextStatus.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SSectionsWithHeaders.h"
#include "SWidgets/SSelectionComboBox.h"
#include "SWidgets/SBootstrapStatus.h"
#include "SMenu/SGameLiftSettingsAwsAccountMenu.h"

#include "IGameLiftCoreModule.h"
#include "GameLiftPlugin.h"
#include "GameLiftPluginStyle.h"
#include <Developer/Settings/Public/ISettingsModule.h>

#include "Settings/UGameLiftAnywhereStatus.h"
#include "Settings/UGameLiftSettings.h"
#include "Types/EBootstrapMessageState.h"
#include "Utils/StringPaths.h"
#include "Utils/Misc.h"

#define LOCTEXT_NAMESPACE "SAnywhereRegisterComputeMenu"

void SAnywhereRegisterComputeMenu::Construct(const FArguments& InArgs)
{
	OnComputeChangedDelegate = InArgs._OnComputeChangedDelegate;

	// Make sure compute registration settings are still valid based on bootstrap status
	ValidateComputeSettings();

	SSectionStep::Construct(
		SSectionStep::FArguments()
		.HeaderTitle(Menu::DeployAnywhere::kRegisterComputeHeader)
		.HeaderDescription(Menu::DeployAnywhere::kRegisterWorkstationDescription)
		.BodyContent()
		[
			SAssignNew(ComputeWidgetSwitcher, SWidgetSwitcher)
				+ SWidgetSwitcher::Slot()
				[
					CreateAddNewComputeUI()
				]
				+ SWidgetSwitcher::Slot()
				[
					CreateShowExistingComputeUI()
				]
		]);

	// Set up compute data from UGameLiftAnywhereStatus.
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	if (AnywhereStatus->IsFleetDeployed && AnywhereStatus->IsComputeRegistered)
	{
		AddNewCompute(AnywhereStatus->ComputeName, AnywhereStatus->ComputeIPAddress);
	}
	else
	{
		// If IP address was not set up before, we set it to the local host address by default.
		ComputeIPTextInput->SetAddress(Utils::GetLocalHostIPv4Address());

		ChangeComputeSelectionUIState(EComputeUIState::CreateNewCompute);
	}

	// Listen to profile changes
	SGameLiftSettingsAwsAccountMenu::OnProfileSelectionChangedMultiDelegate.AddSP(this, &SAnywhereRegisterComputeMenu::OnBootstrapStatusChanged);

	// Initialize section UI based on state
	if (!HaveExistingCompute() && !AnywhereStatus->IsFleetDeployed)
	{
		ResetAndCollapseSection();
	}
}

void SAnywhereRegisterComputeMenu::OnComputeRegistered()
{
	// Called when a user registers a new compute
	OnComputeChangedDelegate.ExecuteIfBound();
}

void SAnywhereRegisterComputeMenu::OnBootstrapStatusChanged(const SGameLiftSettingsAwsAccountMenu* /* Sender */)
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	if (EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::NoBootstrappedMessage)
	{
		InvalidateCompute();
	}
}

void SAnywhereRegisterComputeMenu::StartSection()
{
	InvalidateCompute();
}

void SAnywhereRegisterComputeMenu::InvalidateCompute()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	ComputeNameTextInput->SetText(GetDefaultComputeName());
	ComputeIPTextInput->SetAddress(Utils::GetLocalHostIPv4Address());

	SelectedCompute.ComputeName = FString();
	SelectedCompute.RegisteredIPAddress = FString();
	SelectedCompute.LinkedFleetId = AnywhereStatus->FleetId;

	AnywhereStatus->ComputeName = FString();
	AnywhereStatus->ComputeIPAddress = FString();
	AnywhereStatus->IsComputeRegistered = false;
	AnywhereStatus->SaveConfig();

	ChangeComputeSelectionUIState(EComputeUIState::CreateNewCompute);
}

TSharedRef<SWidget> SAnywhereRegisterComputeMenu::CreateAddNewComputeUI()
{
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox)
		// Compute name text input
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Right2x + SPadding::Top)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployAnywhere::kComputeNameTitle)
			.RowWidget(
				SAssignNew(ComputeNameTextInput, SEditableTextBox)
				.HintText(Menu::DeployAnywhere::kComputeNameTextHint)
				.IsEnabled_Raw(this, &SAnywhereRegisterComputeMenu::CanEditComputeSettings)
			)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top2x + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployAnywhere::kComputeIPTitle)
			.NameTooltipText(Menu::DeployAnywhere::kComputeIPTextTooltip)
			.RowWidget(
				SAssignNew(ComputeIPTextInput, SIPAddressTextBox)
				.HintText(Menu::DeployAnywhere::kComputeIPTextHint)
				.IsEnabled_Raw(this, &SAnywhereRegisterComputeMenu::CanEditComputeSettings)
			)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top3x + SPadding::Right2x)
		[
			SNew(SHorizontalBox)
			// Button to cancel adding new compute
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.Padding(SPadding::Right2x)
			[
				SAssignNew(CancelButton, SButton)
				.Text(Menu::DeployAnywhere::kCancelButtonText)
				.OnClicked_Raw(this, &SAnywhereRegisterComputeMenu::OnCancelComputeButtonClicked)
				.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
			]
			// Button to register new compute
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.Padding(SPadding::Right2x)
			[
				SNew(SButton)
				.Text(Menu::DeployAnywhere::kRegisterFirstComputeButtonText)
				.OnClicked_Raw(this, &SAnywhereRegisterComputeMenu::OnRegisterFirstComputeButtonClicked)
				.IsEnabled_Raw(this, &SAnywhereRegisterComputeMenu::CanRegisterCompute)
				.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonLight)
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
					return IsLoading ? EVisibility::Visible : EVisibility::Hidden;
				})
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.Padding(SPadding::Top2x + SPadding::Right2x)
		[
			SAssignNew(RegisterComputeErrorRow, SNamedRow)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SAssignNew(RegisterComputeErrorTextBlock, STextBlock)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote)
				.AutoWrapText(true)
			)
			.Visibility(EVisibility::Collapsed)
		];

		RegisterComputeErrorTextBlock->SetColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kError));

		return VerticalBox;
}

TSharedRef<SWidget> SAnywhereRegisterComputeMenu::CreateShowExistingComputeUI()
{
	return SNew(SVerticalBox)
		// Compute name
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Right2x + SPadding::Top)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployAnywhere::kComputeNameTitle)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SAssignNew(ComputeNameTextView, SEditableText)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
				.IsReadOnly(true)
			)
		]
		// Compute IP
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top2x + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployAnywhere::kComputeIPTitle)
			.NameTooltipText(Menu::DeployAnywhere::kComputeIPTextTooltip)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SAssignNew(ComputeIPTextView, SEditableText)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
				.IsReadOnly(true)
			)
		]
		// Compute status
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top2x + SPadding::Right2x)
		[
			CreateComputeStatusRow()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top3x + SPadding::Right2x)
		[
			SNew(SHorizontalBox)
			// Button to register a new compute
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.Padding(SPadding::Right)
			[
				SAssignNew(RegisterComputeButton, SButton)
				.Text(Menu::DeployAnywhere::kRegisterNewComputeButtonText)
				.OnClicked_Raw(this, &SAnywhereRegisterComputeMenu::OnRegisterNewComputeButtonClicked)
				.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
			]
		];
}

TSharedRef<SWidget> SAnywhereRegisterComputeMenu::CreateComputeStatusRow()
{
	TSharedRef<STextStatus> TextStatus = SNew(STextStatus)
		.StatusText(Menu::DeployAnywhere::kComputeStatusRegisteredText)
		.StatusTextStyle(Style::Text::kFieldBold)
		.IconState(STextStatus::EIconState::Success);

	TextStatus->SetStatusTextColor(FGameLiftPluginStyle::Get().GetColor(Style::Color::kSuccess));
	
	return SAssignNew(ComputeStatusRow, SNamedRow)
		.NameText(Menu::DeployAnywhere::kStatusTitle)
		.SecondaryColumnLeftPadding(true)
		.RowWidget(
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				TextStatus
			]
		);
}

FReply SAnywhereRegisterComputeMenu::OnRegisterFirstComputeButtonClicked()
{
	FString ComputeName = ComputeNameTextInput->GetText().ToString().TrimStartAndEnd();
	FString ComputeIPAddress = ComputeIPTextInput->GetAddress();

	// Validate input
	if (ComputeName.IsEmpty() || ComputeIPAddress.IsEmpty())
	{
		return FReply::Handled();
	}

	IsLoading = true;
	SetProgressBarState(SProgressBar::EProgressBarUIState::InProgress);

	Async(EAsyncExecution::Thread,
		[this, ComputeName = MoveTemp(ComputeName), ComputeIPAddress = MoveTemp(ComputeIPAddress)]()
		{
			TTuple<bool, FString> RegisterResult = RegisterCompute(ComputeName, ComputeIPAddress);

			IsLoading = false;

			Async(EAsyncExecution::TaskGraphMainThread,
				[this, ComputeNameCopy = ComputeName, ComputeIPAddressCopy = ComputeIPAddress, RegisterResult = MoveTemp(RegisterResult)]
				{
					if (RegisterResult.Get<0>())
					{
						AddNewCompute(ComputeNameCopy, ComputeIPAddressCopy);
						OnComputeRegistered();
						UpdateErrorMessage(FText::GetEmpty());

						SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressComplete);
						StartNextSection();
					}
					else
					{
						UpdateErrorMessage(FText::FromString(RegisterResult.Get<1>()));
						SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressError);
					}
				});
		});

	return FReply::Handled();
}

FReply SAnywhereRegisterComputeMenu::OnRegisterNewComputeButtonClicked()
{
	ChangeComputeSelectionUIState(EComputeUIState::CreateNewCompute);
	ResetAndCollapseNextSections();

	return FReply::Handled();
}

FReply SAnywhereRegisterComputeMenu::OnCancelComputeButtonClicked()
{
	ChangeComputeSelectionUIState(EComputeUIState::ShowExistingCompute);

	return FReply::Handled();
}

TTuple<bool, FString> SAnywhereRegisterComputeMenu::RegisterCompute(const FString& InComputeName, const FString& InIPAddress)
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	IGameLiftAnywhereHandler& Handler = IGameLiftCoreModule::Get().GetGameLiftAnywhereHandler();

	// First, make sure that we have a custom location created for the current AWS region.
	// Needed for existing fleets that were created outside of the plugin.
	TTuple<FString, FString> CreateLocationResult = CreateCustomLocation();
	const FString LocationName = CreateLocationResult.Get<0>();
	if (LocationName.IsEmpty())
	{
		// Failed to create custom location.
		return MakeTuple(false, CreateLocationResult.Get<1>());
	}

	// Next, make sure the custom location has been added to the fleet.
	// Needed for existing fleets that were created outside of the plugin.
	GameLiftAnywhereAddFleetLocationResult AddFleetLocationResult = Handler.AddFleetLocation(AnywhereStatus->FleetId, LocationName);

	if (!AddFleetLocationResult.bIsSuccessful)
	{
		return MakeTuple(false, AddFleetLocationResult.ErrorMessage);
	}

	// Register the compute
	GameLiftAnywhereRegisterComputeResult RegisterComputeResult = Handler.RegisterCompute(
		InComputeName, InIPAddress, AnywhereStatus->FleetId, AnywhereStatus->CustomLocation);

	if (RegisterComputeResult.bIsSuccessful)
	{
		AnywhereStatus->ComputeName = InComputeName;
		AnywhereStatus->ComputeIPAddress = InIPAddress;
		AnywhereStatus->IsComputeRegistered = true;

		AnywhereStatus->SaveConfig();

		return MakeTuple(true, TEXT(""));
	}
	else
	{
		return MakeTuple(false, RegisterComputeResult.ErrorMessage);
	}
}

TTuple<FString, FString> SAnywhereRegisterComputeMenu::CreateCustomLocation()
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

void SAnywhereRegisterComputeMenu::AddNewCompute(const FString& InComputeName, const FString& InIPAddress)
{
	// Set selected compute
	SelectedCompute.ComputeName = InComputeName;
	SelectedCompute.RegisteredIPAddress = InIPAddress;

	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	SelectedCompute.LinkedFleetId = AnywhereStatus->FleetId;

	ChangeComputeSelectionUIState(EComputeUIState::ShowExistingCompute);
}

FText SAnywhereRegisterComputeMenu::GetDefaultComputeName() const
{
	return Menu::DeployAnywhere::kComputeNameDefault;
}

void SAnywhereRegisterComputeMenu::ValidateComputeSettings()
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	if (EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::NoBootstrappedMessage)
	{
		UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
		AnywhereStatus->ComputeName = FString();
		AnywhereStatus->ComputeIPAddress = FString();
		AnywhereStatus->IsComputeRegistered = false;
		AnywhereStatus->SaveConfig();
	}
}

bool SAnywhereRegisterComputeMenu::CanEditComputeSettings() const
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	return EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::ActiveMessage
		&& AnywhereStatus->IsFleetDeployed
		&& !IsLoading;
}

bool SAnywhereRegisterComputeMenu::CanRegisterCompute() const
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	return CanEditComputeSettings()
		&& !ComputeNameTextInput->GetText().IsEmpty()
		&& ComputeIPTextInput->IsAddressValid();
}

void SAnywhereRegisterComputeMenu::ChangeComputeSelectionUIState(EComputeUIState InState)
{
	ComputeWidgetSwitcher->SetActiveWidgetIndex(ComputeUIStateToInt(InState));

	UpdateContentForCurrentUIState();
}

void SAnywhereRegisterComputeMenu::UpdateContentForCurrentUIState()
{
	ComputeNameTextInput->SetText(GetDefaultComputeName());

	if (ComputeWidgetSwitcher->GetActiveWidgetIndex() == ComputeUIStateToInt(EComputeUIState::CreateNewCompute))
	{
		// Update UI for registering a new compute
		CancelButton->SetVisibility(HaveExistingCompute() ? EVisibility::Visible : EVisibility::Collapsed);
		SetProgressBarState(SProgressBar::EProgressBarUIState::NotStart);
	}
	else
	{
		// Update UI for registering an existing compute
		if (HaveExistingCompute())
		{
			// Show ID
			ComputeNameTextView->SetText(FText::FromString(SelectedCompute.ComputeName));

			FString FormattedAddress = SelectedCompute.RegisteredIPAddress;
			SIPAddressTextBox::FormatAddressForDisplay(FormattedAddress);
			ComputeIPTextView->SetText(FText::FromString(FormattedAddress));

			// Show status
			ComputeStatusRow->SetVisibility(EVisibility::Visible);
			SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressComplete);
			StartNextSection();
		}
		else
		{
			// Hide status
			ComputeStatusRow->SetVisibility(EVisibility::Collapsed);
			SetProgressBarState(SProgressBar::EProgressBarUIState::NotStart);
		}
	}

	// Update button style
	const FButtonStyle& CurrentButtonStyle = FGameLiftPluginStyle::Get().GetWidgetStyle<FButtonStyle>(
		HaveExistingCompute() ? Style::Button::kNormalButtonStyleName : Style::Button::kSuccessButtonStyleName);
	RegisterComputeButton->SetButtonStyle(&CurrentButtonStyle);
}

bool SAnywhereRegisterComputeMenu::HaveExistingCompute() const
{
	return !SelectedCompute.ComputeName.IsEmpty();
}

void SAnywhereRegisterComputeMenu::UpdateErrorMessage(const FText& ErrorMessage)
{
	if (ErrorMessage.IsEmpty())
	{
		RegisterComputeErrorRow->SetVisibility(EVisibility::Collapsed);
		RegisterComputeErrorTextBlock->SetText(FText::GetEmpty());
	}
	else
	{
		RegisterComputeErrorRow->SetVisibility(EVisibility::Visible);
		RegisterComputeErrorTextBlock->SetText(ErrorMessage);
	}
}

#undef LOCTEXT_NAMESPACE
