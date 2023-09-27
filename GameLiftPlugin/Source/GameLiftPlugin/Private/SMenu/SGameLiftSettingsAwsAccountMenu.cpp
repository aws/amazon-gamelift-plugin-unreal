// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftSettingsAwsAccountMenu.h"

#include <Async/Async.h>
#include <DetailLayoutBuilder.h>
#include <Widgets/SBoxPanel.h>
#include <Widgets/Layout/SWidgetSwitcher.h>

#include "IAWSConfigFileProfile.h"
#include "IGameLiftCoreModule.h"

#include "GameLiftPlugin.h"
#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#include "SWidgets/SAccountStartupCard.h"
#include "SWidgets/SBootstrapStatus.h"
#include "SWidgets/SInputTextBox.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SSelectionComboBox.h"
#include "SWidgets/SSetupMessage.h"
#include "SWidgets/STextSeparator.h"
#include "SWidgets/STitleBlock.h"

#include "Settings/UGameLiftSettings.h"
#include "Types/EAwsRegions.h"
#include "Utils/Misc.h"

#define LOCTEXT_NAMESPACE "SGameLiftSettingsAwsAccountMenu"

FOnProfileSelectionChanged SGameLiftSettingsAwsAccountMenu::OnProfileSelectionChangedMultiDelegate;

void SGameLiftSettingsAwsAccountMenu::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	ProfileManagementEnabled = InArgs._ProfileManagementEnabled;
	HideButtonsWhenBootstrapped = InArgs._HideButtonsWhenBootstrapped;
	ShowBootstrapStatusOnly = InArgs._ShowBootstrapStatusOnly;

	// Make sure current profile settings are still valid based on available profiles
	ValidateAwsAccountProfileSettings();

	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	if (!ShowBootstrapStatusOnly)
	{
		VerticalBox->AddSlot()
			.AutoHeight()
			.Padding(SPadding::Bottom)
			[
				MakeHeaderWidget()
			];
	}

	// The message widget still needs to be initialized since there is a member variable pointing to the widget.
	// If ShowBootstrapStatusOnly is false, the visibility of the message widget would be 'collapsed'.
	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			MakeSetupMessageWidget()
		];

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Top)
		[
			MakeProfileSwitcherWidget()
		];

	ChildSlot
	[
		VerticalBox
	];

	// Listen to "profile selection change" notifications to update the UI when the change comes from another instance.
	// Keeps a weak reference to the object
	OnProfileSelectionChangedMultiDelegate.AddSP(this, &SGameLiftSettingsAwsAccountMenu::OnProfileSelectionChanged);

	SetupMenu();
}

TSharedRef<SWidget> SGameLiftSettingsAwsAccountMenu::MakeHeaderWidget()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		[
			SNew(STitleBlock)
			.Text(Settings::AwsAccount::kHeaderTitleText)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(STextBlock)
			.Text(Settings::AwsAccount::kHeaderDescriptionText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
			.AutoWrapText(true)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SOnlineHyperlink)
				.Text(Settings::AwsAccount::kHeaderDocumentationLinkText)
				.Link(Url::kGameLiftDocumentationUrl)
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
				.Text(Settings::AwsAccount::kHeaderForumLinkText)
				.Link(Url::kGameTechForumUrl)
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
				.Text(Settings::AwsAccount::kHeaderPricePlanLinkText)
				.Link(Url::kGameLiftPricingPlanUrl)
			]
		];
}

TSharedRef<SWidget> SGameLiftSettingsAwsAccountMenu::MakeSetupMessageWidget()
{
	return SAssignNew(AwsProfileSetupMessage, SSetupMessage)
		.WarningText(Settings::AwsAccount::kNotConfiguredText)
		.FailureText(Settings::AwsAccount::kConfigurationFailedText)
		.ReadyToGoText(Settings::AwsAccount::kConfiguredText)
		.OnUpdateState_Raw(this, &SGameLiftSettingsAwsAccountMenu::DetectBootstrapSetup)
		.Visibility(ShowBootstrapStatusOnly ? EVisibility::Collapsed : EVisibility::Visible);
}

TSharedRef<SWidget> SGameLiftSettingsAwsAccountMenu::MakeProfileSwitcherWidget()
{
	TSharedRef<SWidget> StartupWidget = MakeProfileStartupWidget();
	TSharedRef<SWidget> ModifyAccount = MakeProfileModificationWidget();
	TSharedRef<SWidget> BootstrapAccount = MakeProfileBootstrappingWidget();

	return SNew(SWidgetSwitcher)
		.WidgetIndex(this, &SGameLiftSettingsAwsAccountMenu::GetAccountManagementStateAsInt)
		+ SWidgetSwitcher::Slot()
		[
			StartupWidget
		]
		+ SWidgetSwitcher::Slot()
		[
			ModifyAccount
		]
		+ SWidgetSwitcher::Slot()
		[
			BootstrapAccount
		];
}

ESetupMessageState SGameLiftSettingsAwsAccountMenu::DetectBootstrapSetup(ESetupMessageState CurrentState)
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	
	switch (Settings->BootstrapStatus)
	{
		case (int)EBootstrapMessageState::ActiveMessage:
			return ESetupMessageState::ReadyToGoMessage;
		case (int)EBootstrapMessageState::FailureMessage:
			return ESetupMessageState::FailureMessage;
		default:
			return ESetupMessageState::WarningMessage;
	}
}

void SGameLiftSettingsAwsAccountMenu::OnBootstrapStateChanged(EBootstrapMessageState NewState)
{
	AwsProfileSetupMessage->Tick();
}

void SGameLiftSettingsAwsAccountMenu::OnProfileSelectionChanged(const SGameLiftSettingsAwsAccountMenu* Sender)
{
	if (this != Sender)
	{
		// Profile selection has changed externally, udpate the UI accordingly
		SetupMenu();
	}
}

void SGameLiftSettingsAwsAccountMenu::SetupMenu()
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	TSharedRef<IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();
	const TArray<FString>& AwsAccountsNames = Configurator->GetProfileNames();

	ResetModificationUI();

	if (AwsAccountsNames.Num() == 0)
	{
		// Users don't have any account profile.
		UpdateAccountManagementState(EAccountManagementState::NoAccount);

		if (Settings->BootstrapStatus != (int)EBootstrapMessageState::NoBootstrappedMessage)
		{
			SBootstrapStatus::CastToSharedRef(BootstrapStatus)->OnNeedBootstrap();
		}
	}
	else
	{
		UpdateAccountManagementState(EAccountManagementState::ModifyAccount);
		FText& ProfileName = Settings->ProfileName;

		if (ProfileName.IsEmpty() || ProfileName.ToString() == "")
		{
			UpdateAccountManagementState(EAccountManagementState::ModifyAccount);
		}
		else
		{
			SSelectionComboBox::CastToSharedRef(ProfileBootstrapComboBox)->RequestToRebuildList();
			RefreshSelectedProfile(ProfileName);
		}
	}
}

void SGameLiftSettingsAwsAccountMenu::RefreshSelectedProfile(const FText& ProfileName)
{
	TSharedRef<IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();
	const TArray<FString>& AwsAccountsNames = Configurator->GetProfileNames();

	for (int Index = 0; Index < AwsAccountsNames.Num(); Index++)
	{
		if (ProfileName.EqualTo(FText::FromString(AwsAccountsNames[Index])))
		{
			SSelectionComboBox::CastToSharedRef(ProfileBootstrapComboBox)->SetSelectedId(Index);
			UpdateAccountManagementState(EAccountManagementState::BootstrapAccount);
			break;
		}
	}
}

void SGameLiftSettingsAwsAccountMenu::UpdateAccountManagementState(EAccountManagementState NewState)
{
	AccountManagementState = NewState;
}

int32 SGameLiftSettingsAwsAccountMenu::GetAccountManagementStateAsInt() const
{
	return (int32)AccountManagementState;
}

TSharedRef<SWidget> SGameLiftSettingsAwsAccountMenu::MakeProfileDescriptionChildWidget(const FText& HeaderText, const FText& DescriptionText)
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		[
			SNew(SSubtitleBlock)
			.Text(HeaderText)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		[
			SNew(STextBlock)
			.Text(DescriptionText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
			.AutoWrapText(true)
		];
}

TSharedRef<SWidget> SGameLiftSettingsAwsAccountMenu::MakeProfileStartupWidget()
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(SPadding::Top2x_Bottom2x + SPadding::Left2x_Right2x)
		[
			SNew(SAccountStartupCard)
			.Icon(Style::Brush::kAccountMissingIconName)
			.DescriptionText(Settings::AwsAccount::kProfileStartupAccountMissingText)
			.ButtonText(Settings::AwsAccount::kProfileStartupAccountMissingButtonText)
			.OnButtonClicked_Lambda([]
			{
				FPlatformProcess::LaunchURL(*FString(Url::kAwsAccountCreateAwsAccountUrl), nullptr, nullptr);
			})
			.IsHyperlinkButton(true)
			.LinkText(Settings::AwsAccount::kProfileStartupAccountMissingLinkText)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(SPadding::Top2x_Bottom2x + SPadding::Left2x_Right2x)
		[
			SNew(SAccountStartupCard)
			.Icon(Style::Brush::kAccountIconName)
			.DescriptionText(Settings::AwsAccount::kProfileStartupAccountText)
			.ButtonText(Settings::AwsAccount::kProfileStartupAccountButtonText)
			.UseSuccessButton(true)
			.OnButtonClicked_Lambda([&]
			{
				UpdateAccountManagementState(EAccountManagementState::ModifyAccount);
			})
		];
}

TSharedRef<SWidget> SGameLiftSettingsAwsAccountMenu::MakeProfileModificationWidget()
{
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	if (!ShowBootstrapStatusOnly)
	{
		VerticalBox->AddSlot()
			.AutoHeight()
			.Padding(SPadding::Bottom + SPadding::Right2x)
			[
				MakeProfileDescriptionChildWidget(
					Settings::AwsAccount::kProfileModificationTitleText,
					Settings::AwsAccount::kProfileModificationDescriptionText)
			];
	}

	// Profile selection
	VerticalBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Settings::AwsAccount::kProfileModificationProfileSelectionText)
			.RowWidget(
				SAssignNew(ProfileModificationComboBox, SSelectionComboBox)
				.OnListBuilding_Raw(this, &SGameLiftSettingsAwsAccountMenu::BuildAccountsForModificationValues)
				.OnItemSelected_Raw(this, &SGameLiftSettingsAwsAccountMenu::OnProfileSelectedForModification)
			)
		];

	// AWS profile name
	VerticalBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Settings::AwsAccount::kProfileModificationProfileNameText)
			.RowWidget(
				SAssignNew(AwsProfileNameInput, SInputTextBox)
				.ButtonVisibility(EVisibility::Hidden)
			)
		];

	// AWS access key
	VerticalBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Settings::AwsAccount::kProfileModificationAccessKeyText)
			.RowWidget(SAssignNew(AwsAccessKeyIdInput, SInputTextBox))
		];

	// AWS secret key
	VerticalBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Settings::AwsAccount::kProfileModificationSecretKeyText)
			.RowWidget(SAssignNew(AwsSecretKeyInput, SInputTextBox))
		];

	// AWS region
	VerticalBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Settings::AwsAccount::kProfileModificationRegionText)
			.RowWidget(
				SAssignNew(AwsRegionInput, SSelectionComboBox)
				.OnListBuilding_Raw(this, &SGameLiftSettingsAwsAccountMenu::BuildRegionValues)
				.OnItemSelected_Raw(this, &SGameLiftSettingsAwsAccountMenu::OnGetRegion)
			)
		];

	// Buttons and hyperlink
	VerticalBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.RowWidget(
				SNew(SHorizontalBox)
				// Button to bootstrap profile
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.Padding(SPadding::Right)
				[
					SNew(SButton)
					.Text_Raw(this, &SGameLiftSettingsAwsAccountMenu::GetCreateAndBootstrapAccountText)
					.OnClicked_Raw(this, &SGameLiftSettingsAwsAccountMenu::CreateAndBootstrapAccount)
					.IsEnabled_Raw(this, &SGameLiftSettingsAwsAccountMenu::CanCreateAccountProfile)
					.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonLight)
				]
				// Button to manage your profile
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.Padding(SPadding::Left)
				[
					SNew(SButton)
					.Text(Settings::AwsAccount::kAddNewProfileButtonText)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
					.Visibility_Lambda([&]
					{
						// Show the button only when we're not adding a new profile.
						return SSelectionComboBox::CastToSharedRef(ProfileModificationComboBox)->GetSelectedId() != 0
							? EVisibility::Visible
							: EVisibility::Hidden;
					})
					.OnClicked_Lambda([&]
					{
						ResetModificationUI();
						return FReply::Handled();
					})
				]
				// Hyperlink
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Right)
				.Padding(SPadding::Right)  // move the link left a bit
				[
					SNew(SOnlineHyperlink)
					.Text(Settings::AwsAccount::kHowToCreateAccountHyperLinkText)
					.Link(Settings::AwsAccount::kHowToCreateAccountHyperLinkUrl)
				]
			)
		];
	
	return VerticalBox;
}

TSharedRef<SWidget> SGameLiftSettingsAwsAccountMenu::MakeProfileBootstrappingWidget()
{
	BootstrapStatus = SNew(SBootstrapStatus)
		.OnUpdateState_Lambda([&](auto NewState)
		{
			OnBootstrapStateChanged(NewState);
			return NewState;
		});

	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	if (!ShowBootstrapStatusOnly)
	{
		VerticalBox->AddSlot()
			.AutoHeight()
			.Padding(SPadding::Bottom + SPadding::Right2x)
			[
				MakeProfileDescriptionChildWidget(
					Settings::AwsAccount::kProfileBootstrappingTitleText,
					Settings::AwsAccount::kProfileBootstrappingDescriptionText)
			];
	}

	// Profile selection
	VerticalBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Settings::AwsAccount::kProfileModificationProfileSelectionText)
			.RowWidget(
				SAssignNew(ProfileBootstrapComboBox, SSelectionComboBox)
				.OnListBuilding_Raw(this, &SGameLiftSettingsAwsAccountMenu::BuildAccountsForBootstrappingValues)
				.OnItemSelected_Raw(this, &SGameLiftSettingsAwsAccountMenu::OnProfileSelectedForBootstrapping)
			)
		];

	// Bootstrap status
	VerticalBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Right2x)
		[
			BootstrapStatus.ToSharedRef()
		];

	// Buttons and hyperlink
	VerticalBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.Visibility_Lambda([&]
			{
				UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
				return !HideButtonsWhenBootstrapped || EBootstrapMessageStateFromInt(Settings->BootstrapStatus) != EBootstrapMessageState::ActiveMessage ? EVisibility::Visible : EVisibility::Collapsed;
			})
			.RowWidget(
				SNew(SHorizontalBox)
				// Button to bootstrap profile
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.Padding(SPadding::Right2x)
				[
					SNew(SButton)
					.Text(Settings::AwsAccount::kBootstrapProfileButtonText)
					.OnClicked_Lambda([&]()
					{
						return BootstrapAccount(
							SSelectionComboBox::CastToSharedRef(ProfileBootstrapComboBox)->GetSelectedPair().Text.ToString());
					})
					.IsEnabled_Lambda([&]
					{
						UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
						return EBootstrapMessageStateFromInt(Settings->BootstrapStatus) != EBootstrapMessageState::InProgressMessage;
					})
					.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonLight)
					.Visibility_Lambda([&]
					{
						UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
						return EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::ActiveMessage ? EVisibility::Collapsed : EVisibility::Visible;
					})
				]
				// Button to manage your profile 
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				[
					SNew(SButton)
					.Text(Settings::AwsAccount::kManageYourProfileButtonText)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
					.OnClicked_Lambda([&]
					{
						UpdateAccountManagementState(EAccountManagementState::ModifyAccount);

						FText SelectedProfileName = SSelectionComboBox::CastToSharedRef(ProfileBootstrapComboBox)->GetSelectedName();
						UpdateModificationUI(SelectedProfileName);
						
						SBootstrapStatus::CastToSharedRef(BootstrapStatus)->OnNeedBootstrap();

						return FReply::Handled();
					})
					.IsEnabled_Lambda([&]
					{
						UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
						return EBootstrapMessageStateFromInt(Settings->BootstrapStatus) != EBootstrapMessageState::InProgressMessage;
					})
					.Visibility_Lambda([&]
					{
						return ProfileManagementEnabled ?  EVisibility::Visible : EVisibility::Collapsed;
					})
				]
				// Hyperlink
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Right)
				.Padding(SPadding::Right) // move the link left a bit
				[
					SNew(SOnlineHyperlink)
					.Text(Settings::AwsAccount::kViewS3ConsoleHyperLinkText)
					.Link(Settings::AwsAccount::kViewS3ConsoleHyperLinkUrl)
					.Visibility(HideButtonsWhenBootstrapped ? EVisibility::Hidden : EVisibility::Visible)
				]
			)
		];

	return VerticalBox;
}

void SGameLiftSettingsAwsAccountMenu::AddAwsAccountProfiles(TArray<FTextIntPair>& Items)
{
	TSharedRef<IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();
	const auto AwsAccountsNames = Configurator->GetProfileNames();

	for (int Index = 0; Index < AwsAccountsNames.Num(); Index++)
	{
		Items.Add(FTextIntPair(FText::FromString(AwsAccountsNames[Index]), Index + 1));
	}
}

void SGameLiftSettingsAwsAccountMenu::BuildAccountsForBootstrappingValues(TArray<FTextIntPair>& Items)
{
	Items.Reset();
	AddAwsAccountProfiles(Items);
}

void SGameLiftSettingsAwsAccountMenu::OnProfileSelectedForBootstrapping(int SelectionId, const FTextIntPair& Item)
{
	const FText& SelectedProfileName = Item.Text;
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();

	if (SelectedProfileName.EqualTo(Settings->ProfileName))
	{
		if (!Settings->S3Bucket.IsEmpty() && !Settings->AwsRegion.IsEmpty())
		{
			SBootstrapStatus::CastToSharedRef(BootstrapStatus)->OnSucceeded();
		}
	}
	else
	{
		// Unlike profile modification, widgets are embedded in SBootstrapStatus and automatically updated based on the info in Settings.
		TSharedRef<IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();

		Settings->ProfileName = SelectedProfileName;
		Settings->S3Bucket = FText::GetEmpty();
		Settings->AwsRegion = FText::FromString(Configurator->GetRegion(SelectedProfileName.ToString()));
		Settings->BootstrapError = FText::GetEmpty();
		Settings->SaveConfig();

		SBootstrapStatus::CastToSharedRef(BootstrapStatus)->OnNeedBootstrap(); // This will reset the BootstrapState in Settings

		// Broadcast profile selection change notification
		OnProfileSelectionChangedMultiDelegate.Broadcast(this);
	}
}

void SGameLiftSettingsAwsAccountMenu::BuildAccountsForModificationValues(TArray<FTextIntPair>& Items)
{
	Items.Reset();
	Items.Add(FTextIntPair(Settings::AwsAccount::kAddNewProfileSelectionText, Settings::AwsAccount::kAddNewProfileSelectionId));
	AddAwsAccountProfiles(Items);
}

void SGameLiftSettingsAwsAccountMenu::OnProfileSelectedForModification(int SelectionId, const FTextIntPair& Items)
{
	if (SelectionId == Settings::AwsAccount::kAddNewProfileSelectionId)
	{
		ResetModificationUI();
	}
	else
	{
		const FText& ProfileName = Items.Text;
		UpdateModificationUI(ProfileName);
	}

	// Broadcast profile selection change notification
	OnProfileSelectionChangedMultiDelegate.Broadcast(this);
}

void SGameLiftSettingsAwsAccountMenu::ResetModificationUI()
{
	SSelectionComboBox::CastToSharedRef(ProfileModificationComboBox)->SetSelectedId(Settings::AwsAccount::kAddNewProfileSelectionId);
	SInputTextBox::CastToSharedRef(AwsProfileNameInput)->SetInputText("");
	SInputTextBox::CastToSharedRef(AwsAccessKeyIdInput)->SetInputText("");
	SInputTextBox::CastToSharedRef(AwsSecretKeyInput)->SetInputText("");
	SSelectionComboBox::CastToSharedRef(AwsRegionInput)->SetSelectedByName(FText::FromString(RegionToString(Aws::ERegions::us_east_1)));
}

void SGameLiftSettingsAwsAccountMenu::UpdateModificationUI(const FText& ProfileName)
{
	SSelectionComboBox::CastToSharedRef(ProfileModificationComboBox)->SetSelectedByName(ProfileName);

	TSharedRef<IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();
	const FString& AccessKey = Configurator->GetAccessKey(ProfileName.ToString());
	const FString& SecretKey = Configurator->GetSecretAccessKey(ProfileName.ToString());
	const FString& Region = Configurator->GetRegion(ProfileName.ToString());

	SInputTextBox::CastToSharedRef(AwsProfileNameInput)->SetInputText(ProfileName);
	SInputTextBox::CastToSharedRef(AwsAccessKeyIdInput)->SetInputText(AccessKey);
	SInputTextBox::CastToSharedRef(AwsSecretKeyInput)->SetInputText(SecretKey);
	SSelectionComboBox::CastToSharedRef(AwsRegionInput)->SetSelectedByName(FText::FromString(Region));
}

void SGameLiftSettingsAwsAccountMenu::BuildRegionValues(TArray<FTextIntPair>& Items)
{
	Items.Reset();

	int id = 0;
	auto AddToList = [&](Aws::ERegions InRegion)
	{
		Items.Add(FTextIntPair(
			FText::FromString(Aws::RegionToString(InRegion)), 
			id++, 
			FText::FromString(Aws::RegionToNameString(InRegion))
		));
	};

	AddToList(Aws::ERegions::us_east_2);
	AddToList(Aws::ERegions::us_east_1);
	AddToList(Aws::ERegions::us_west_1);
	AddToList(Aws::ERegions::us_west_2);
	//AddToList(Aws::ERegions::af_south_1);
	//AddToList(Aws::ERegions::ap_east_1);
	//AddToList(Aws::ERegions::ap_southeast_3);
	AddToList(Aws::ERegions::ap_south_1);
	//AddToList(Aws::ERegions::ap_northeast_3);
	AddToList(Aws::ERegions::ap_northeast_2);
	AddToList(Aws::ERegions::ap_southeast_1);
	AddToList(Aws::ERegions::ap_southeast_2);
	AddToList(Aws::ERegions::ap_northeast_1);
	AddToList(Aws::ERegions::ca_central_1);
	AddToList(Aws::ERegions::eu_central_1);
	AddToList(Aws::ERegions::eu_west_1);
	AddToList(Aws::ERegions::eu_west_2);
	//AddToList(Aws::ERegions::eu_south_1);
	//AddToList(Aws::ERegions::eu_west_3);
	//AddToList(Aws::ERegions::eu_north_1);
	//AddToList(Aws::ERegions::me_south_1);
	AddToList(Aws::ERegions::sa_east_1);

	Items.Sort([](const FTextIntPair& LeftValue, const FTextIntPair& RightValue)
	{
		return LeftValue.Text.CompareTo(RightValue.Text) < 0;
	});
}

void SGameLiftSettingsAwsAccountMenu::OnGetRegion(int SelectionId, const FTextIntPair& Item)
{
	/**/
}

void SGameLiftSettingsAwsAccountMenu::ModifyAwsAccountProfile(const FString& ProfileName, const FString& AccessKey, const FString& SecretKey, const FString& Region)
{
	FString SelectedAccountName = SSelectionComboBox::CastToSharedRef(ProfileModificationComboBox)->GetSelectedPair().Text.ToString();
	bool IsNameChanged = SelectedAccountName != ProfileName;
	
	{
		TSharedRef<IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();

		if (IsNameChanged)
		{
			Configurator->RenameProfile(SelectedAccountName, ProfileName);
		}

		Configurator->SetAccessKey(ProfileName, AccessKey);
		Configurator->SetSecretAccessKey(ProfileName, SecretKey);
		Configurator->SetRegion(ProfileName, Region);
		Configurator->Save();
	}
}

void SGameLiftSettingsAwsAccountMenu::CreateAwsAccountProfile(const FString& ProfileName, const FString& AccessKey, const FString& SecretKey, const FString& Region)
{
	TSharedRef<IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();

	Configurator->CreateProfile(ProfileName);
	Configurator->SetAccessKey(ProfileName, AccessKey);
	Configurator->SetSecretAccessKey(ProfileName, SecretKey);
	Configurator->SetRegion(ProfileName, Region);
	Configurator->Save();
}

void SGameLiftSettingsAwsAccountMenu::ValidateAwsAccountProfileSettings()
{
	// Check that selected profile still exists
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();

	FText& CurrentProfileName = Settings->ProfileName;
	bool CurrentProfileExists = false;
	if (!CurrentProfileName.IsEmpty() && CurrentProfileName.ToString() != "")
	{
		TSharedRef<IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();
		const TArray<FString>& AwsAccountsNames = Configurator->GetProfileNames();

		for (int Index = 0; Index < AwsAccountsNames.Num(); Index++)
		{
			if (CurrentProfileName.EqualTo(FText::FromString(AwsAccountsNames[Index])))
			{
				CurrentProfileExists = true;
				break;
			}
		}
	}

	if (!CurrentProfileExists)
	{
		// Invalidate current profile settings
		Settings->ProfileName = FText::GetEmpty();
		Settings->S3Bucket = FText::GetEmpty();
		Settings->AwsRegion = FText::GetEmpty();
		Settings->BootstrapError = FText::GetEmpty();
		Settings->BootstrapStatus = (int)EBootstrapMessageState::NoBootstrappedMessage;
		Settings->SaveConfig();
	}
}

bool SGameLiftSettingsAwsAccountMenu::CanCreateAccountProfile() const
{
	const auto& Name = SInputTextBox::CastToSharedRef(AwsProfileNameInput)->GetInputText();
	const auto& AccessKey = SInputTextBox::CastToSharedRef(AwsAccessKeyIdInput)->GetInputText();
	const auto& SecretKey = SInputTextBox::CastToSharedRef(AwsSecretKeyInput)->GetInputText();
	return !(Name.IsEmptyOrWhitespace() || SecretKey.IsEmptyOrWhitespace() || AccessKey.IsEmptyOrWhitespace());
}

FText SGameLiftSettingsAwsAccountMenu::GetCreateAndBootstrapAccountText() const
{
	int SelectedId = SSelectionComboBox::CastToSharedRef(ProfileModificationComboBox)->GetSelectedId();

	// Show different button texts based on the selection.
	if (SelectedId == Settings::AwsAccount::kAddNewProfileSelectionId)
	{
		return Settings::AwsAccount::kBootstrapAndCreateProfileButtonText;
	}
	else
	{
		return Settings::AwsAccount::kBootstrapAndUpdateProfileButtonText;
	}
}

FReply SGameLiftSettingsAwsAccountMenu::CreateAndBootstrapAccount()
{
	auto ManageAccount = [&](auto& Name, auto& AccessKey, auto& SecretKey, auto& Region)
	{
		TSharedRef<IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();
		int SelectedId = SSelectionComboBox::CastToSharedRef(ProfileModificationComboBox)->GetSelectedId();

		if (SelectedId == Settings::AwsAccount::kAddNewProfileSelectionId)
		{
			CreateAwsAccountProfile(Name, AccessKey, SecretKey, Region);
		}
		else
		{
			ModifyAwsAccountProfile(Name, AccessKey, SecretKey, Region);
		}

		SSelectionComboBox::CastToSharedRef(ProfileModificationComboBox)->RequestToRebuildList();
		SSelectionComboBox::CastToSharedRef(ProfileBootstrapComboBox)->RequestToRebuildList();
		ResetModificationUI();
	}; 

	FText ProfileName = SInputTextBox::CastToSharedRef(AwsProfileNameInput)->GetInputText();
	FText AwsKeyAccessId = SInputTextBox::CastToSharedRef(AwsAccessKeyIdInput)->GetInputText();
	FText AwsSecretKey = SInputTextBox::CastToSharedRef(AwsSecretKeyInput)->GetInputText();
	FText AwsRegion = SSelectionComboBox::CastToSharedRef(AwsRegionInput)->GetSelectedPair().Text;

	ManageAccount(ProfileName.ToString(), AwsKeyAccessId.ToString(), AwsSecretKey.ToString(), AwsRegion.ToString());

	return BootstrapAccount(ProfileName.ToString());
}

FReply SGameLiftSettingsAwsAccountMenu::BootstrapAccount(const FString& ProfileName)
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();

	TSharedRef < IAWSConfigFileProfile> Configurator = IGameLiftCoreModule::Get().MakeAWSConfigFileProfile();

	Settings->S3Bucket = FText::GetEmpty();
	Settings->BootstrapError = FText::GetEmpty();
	Settings->ProfileName = FText::FromString(ProfileName);
	Settings->AwsRegion = FText::FromString(Configurator->GetRegion(ProfileName));
	Settings->SaveConfig();

	UpdateAccountManagementState(EAccountManagementState::BootstrapAccount);
	RefreshSelectedProfile(Settings->ProfileName);

	// Broadcast profile selection change notification
	OnProfileSelectionChangedMultiDelegate.Broadcast(this);

	TSharedPtr<SBootstrapStatus> BootstrapStatusPtr = StaticCastSharedPtr<SBootstrapStatus>(BootstrapStatus);
	BootstrapStatusPtr->OnBootstrap();
	Async(EAsyncExecution::Thread, [
		BootstrapStatus = std::move(BootstrapStatusPtr), Settings
	]() {
			auto& Bootstrapper = IGameLiftCoreModule::Get().GetProfileBootstrap();
			auto IsConfigured = Bootstrapper.ConfigureAccount(Settings->ProfileName.ToString(),
				IGameLiftCoreModule::Get().MakeAWSConfigFileProfile());
			if (IsConfigured)
			{
				auto IsBootstrapped = Bootstrapper.Bootstrap();
				if (IsBootstrapped)
				{
					UE_LOG(GameLiftPluginLog, Log, TEXT("%s"), Settings::Logs::kBootstrapSucceed);
					const FString BucketName = Bootstrapper.GetAccountInstance()->GetBucketName();
					Async(EAsyncExecution::TaskGraphMainThread,
						[BootstrapStatus, BucketName]()
						{
							BootstrapStatus->OnSucceeded(BucketName);
						});
					return;
				}
			}
			UE_LOG(GameLiftPluginLog, Log, TEXT("%s"), Settings::Logs::kBootstrapFailed);
			const FText ErrorMessage = Utils::BuildLastestErrorMessage(Bootstrapper);
			Async(EAsyncExecution::TaskGraphMainThread,
				[BootstrapStatus, ErrorMessage]()
				{
					BootstrapStatus->OnFailure(ErrorMessage);
				});
	});

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
