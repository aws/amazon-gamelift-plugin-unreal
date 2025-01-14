// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

#include "Types/EAccountManagementState.h"
#include "Types/EBootstrapMessageState.h"
#include "Types/ESetupMessageState.h"
#include "Types/FTextIntPair.h"

class SWindow;
class SSetupMessage;
class SGameLiftSettingsAwsAccountMenu;
class SBootstrapModal;

DECLARE_DELEGATE_OneParam(FOnAccountStateChanged, EAccountManagementState);
DECLARE_DELEGATE_OneParam(FOnBootstrapStateChanged, EBootstrapMessageState);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnProfileSelectionChanged, const SGameLiftSettingsAwsAccountMenu* /* Sender */);

class SGameLiftSettingsAwsAccountMenu : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SGameLiftSettingsAwsAccountMenu) {}

	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT_DEFAULT(bool, ProfileManagementEnabled) { true };

	SLATE_ARGUMENT_DEFAULT(bool, HideButtonsWhenBootstrapped) { false };

	SLATE_ARGUMENT_DEFAULT(bool, ShowBootstrapStatusOnly) { false };

	SLATE_ARGUMENT_DEFAULT(FString, ReadDeveloperGuideLink) { TEXT("") };

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	// Delegates
	static FOnProfileSelectionChanged OnProfileSelectionChangedMultiDelegate;

	static void RestoreAccount();

	void SetContainersRegionSupported(bool ContainersSupported);

private:
	// Widget Makers
	TSharedRef<SWidget> MakeHeaderWidget();
	TSharedRef<SWidget> MakeSetupMessageWidget();
	TSharedRef<SBootstrapModal> MakeBootstrapModal();

	// Make profile configuration and bootstrapping widgets that will be added to a switcher widget.
	TSharedRef<SWidget> MakeProfileSwitcherWidget();
	TSharedRef<SWidget> MakeProfileStartupWidget();
	TSharedRef<SWidget> MakeProfileModificationWidget();
	TSharedRef<SWidget> MakeProfileBootstrappingWidget();
	TSharedRef<SWidget> MakeProfileDescriptionChildWidget(const FText& HeaderText, const FText& DescriptionText);
	TSharedRef<SWidget> MakeAddProfileWidget(bool BootstrapPage);
	TSharedRef<SWidget> MakeProfileTableHeader();
	TSharedRef<SWidget> MakeOpenCredentialsPageButtonSwitcher();
	TSharedRef<SWidget> CreateAccessCredentialsInstructionsSection();
	TSharedRef<SWidget> MakeContainersUnsupportedWidget();
	void MakeAccessCredentialsHelpWidget();

	// Callbacks that handle account and bootstrap status changes.
	ESetupMessageState DetectBootstrapSetup(ESetupMessageState CurrentState);
	void OnBootstrapStateChanged();

	// Callback that handles profile selection changes from another instance
	void OnProfileSelectionChanged(const SGameLiftSettingsAwsAccountMenu* Sender);

	void SetupMenu();
	void RefreshProfileList();

	void UpdateAccountManagementState(EAccountManagementState NewState);
	int32 GetAccountManagementStateAsInt() const;

	// Helpers that update data in profile modification widget.
	void ResetModificationUI();
	void UpdateModificationUI(const FText& ProfileName);

	void BuildRegionValues(TArray<FTextIntPair>& Items);
	void OnGetRegion(int SelectionId, const FTextIntPair& Item);

	// Functions that interact with the AWS profile configurator to set up values in a profile.
	void ModifyAwsAccountProfile(const FString& ProfileName, const FString& AccessKey, const FString& SecretKey, const FString& Region);
	void CreateAwsAccountProfile(const FString& ProfileName, const FString& AccessKey, const FString& SecretKey, const FString& Region);
	void SyncFromCredentialsFile();

	// Button callbacks
	FReply CreateAccount(bool BootstrapPage);
	void BootstrapAccount(FString BucketName);
	bool CanCreateAccountProfile(bool BootstrapPage) const;
	void ResetAddProfileUI(bool BootstrapPage);

	ECheckBoxState IsRadioChecked(FString ProfileName) const;
	void OnRadioChanged(ECheckBoxState NewRadioState, FString ProfileName);
	FReply OnSetProfileAsSelectedButtonClicked();
	static void CopyProfileInfoFromMapToCurrentSettings();

	TSharedRef<SWidget> CreateStatusWidget(FString ProfileName) const;
	TSharedRef<SWidget> CreateProfileRow(const FString& ProfileName, const FString& AwsRegion, const FString& BucketName, bool IsSelectedProfile, bool ShowProfileRow);

	TSharedRef<SWidget> MakeDocumentationLinkWidget(FString ReadDeveloperGuideLink);
private:
	TWeakPtr<SWindow> ContextWindow;
	bool ProfileManagementEnabled = true;
	bool HideButtonsWhenBootstrapped = false;
	bool ShowBootstrapStatusOnly = false;
	bool ShowAddProfile = false;
	bool ProfileSelectedActive = false;
	bool ContainersRegionSupported = true;

	EAccountManagementState AccountManagementState;

	// Message widgets
	TSharedPtr<SSetupMessage> AwsProfileSetupMessage;
	TSharedPtr<SSetupMessage> AccessCredentialsHelpMessage;
	TSharedPtr<SSetupMessage> ContainersUnsupportedMessage;

	// Modification widgets
	TSharedPtr<SWidget> ProfileModificationComboBox;
	TSharedPtr<SWidgetSwitcher> ProfileHeaderSwitcher;
	TSharedPtr<SWidget> AwsProfileNameInput;
	TSharedPtr<SWidget> AwsAccessKeyIdInput;
	TSharedPtr<SWidget> AwsSecretKeyInput;
	TSharedPtr<SWidget> AwsRegionInput;

    TSharedPtr<SVerticalBox> ProfileListContainer;
    FString RadioButtonSelectedProfile = "";

	// Bootstrap widgets
	TSharedPtr<SWidget> ProfileBootstrapComboBox;
	TSharedPtr<SWidget> CurrentBootstrapStatusWidget;
	TSharedPtr<SWidget> BootstrapPageAwsProfileNameInput;
	TSharedPtr<SWidget> BootstrapPageAwsAccessKeyIdInput;
	TSharedPtr<SWidget> BootstrapPageAwsSecretKeyInput;
	TSharedPtr<SWidget> BootstrapPageAwsRegionInput;

	// Modals
	TSharedPtr<SBootstrapModal> BootstrapModal;
};
