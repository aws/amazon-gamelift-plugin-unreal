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

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	// Widget Makers
	TSharedRef<SWidget> MakeHeaderWidget();
	TSharedRef<SWidget> MakeSetupMessageWidget();

	// Make profile configuration and bootstrapping widgets that will be added to a switcher widget.
	TSharedRef<SWidget> MakeProfileSwitcherWidget();
	TSharedRef<SWidget> MakeProfileStartupWidget();
	TSharedRef<SWidget> MakeProfileModificationWidget();
	TSharedRef<SWidget> MakeProfileBootstrappingWidget();
	TSharedRef<SWidget> MakeProfileDescriptionChildWidget(const FText& HeaderText, const FText& DescriptionText);

	// Callbacks that handle account and bootstrap status changes.
	ESetupMessageState DetectBootstrapSetup(ESetupMessageState CurrentState);
	void OnBootstrapStateChanged(EBootstrapMessageState NewState);

	// Callback that handles profile selection changes from another instance
	void OnProfileSelectionChanged(const SGameLiftSettingsAwsAccountMenu* Sender);

	void SetupMenu();
	void RefreshSelectedProfile(const FText& ProfileName);

	void UpdateAccountManagementState(EAccountManagementState NewState);
	int32 GetAccountManagementStateAsInt() const;

	// Set up data in the profile bootstrapping widget.
	void BuildAccountsForBootstrappingValues(TArray<FTextIntPair>& Items);
	void OnProfileSelectedForBootstrapping(int SelectionId, const FTextIntPair& Item);

	// Set up data in the profile modification widget.
	void BuildAccountsForModificationValues(TArray<FTextIntPair>& Items);
	void OnProfileSelectedForModification(int SelectionId, const FTextIntPair& Item);

	// Helpers that update data in profile modification widget.
	void ResetModificationUI();
	void UpdateModificationUI(const FText& ProfileName);

	void BuildRegionValues(TArray<FTextIntPair>& Items);
	void OnGetRegion(int SelectionId, const FTextIntPair& Item);

	// Functions that interact with the AWS profile configurator to set up values in a profile.
	void AddAwsAccountProfiles(TArray<FTextIntPair>& Items);
	void ModifyAwsAccountProfile(const FString& ProfileName, const FString& AccessKey, const FString& SecretKey, const FString& Region);
	void CreateAwsAccountProfile(const FString& ProfileName, const FString& AccessKey, const FString& SecretKey, const FString& Region);
	void ValidateAwsAccountProfileSettings();

	// Button callbacks
	FText GetCreateAndBootstrapAccountText() const;
	FReply CreateAndBootstrapAccount();
	FReply BootstrapAccount(const FString& ProfileName);
	bool CanCreateAccountProfile() const;

private:
	TWeakPtr<SWindow> ContextWindow;
	bool ProfileManagementEnabled = true;
	bool HideButtonsWhenBootstrapped = false;
	bool ShowBootstrapStatusOnly = false;

	// Delegates
	static FOnProfileSelectionChanged OnProfileSelectionChangedMultiDelegate;

	EAccountManagementState AccountManagementState;

	// Message widget
	TSharedPtr<SSetupMessage> AwsProfileSetupMessage;

	// Modification widgets
	TSharedPtr<SWidget> ProfileModificationComboBox;
	TSharedPtr<SWidget> AwsProfileNameInput;
	TSharedPtr<SWidget> AwsAccessKeyIdInput;
	TSharedPtr<SWidget> AwsSecretKeyInput;
	TSharedPtr<SWidget> AwsRegionInput;

	// Bootstrap widgets
	TSharedPtr<SWidget> ProfileBootstrapComboBox;
	TSharedPtr<SWidget> BootstrapStatus;
};
