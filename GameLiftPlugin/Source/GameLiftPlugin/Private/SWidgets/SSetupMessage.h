// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "Styling/SlateColor.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SWidget.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"
#include "Types/ESetupMessageState.h"

class SSetupMessage;

DECLARE_DELEGATE_RetVal_OneParam(ESetupMessageState, FOnUpdateSetupState, ESetupMessageState);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetupMessageStateChanged, const SSetupMessage* /* Sender */);

// Display a message banner to indicate the setup status.
class SSetupMessage : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SSetupMessage) {}
    
	// Help
	SLATE_ARGUMENT_DEFAULT(FText, HelpText) { FText() };

	SLATE_ARGUMENT_DEFAULT(FText, HelpButtonText) { FText::GetEmpty() };

	SLATE_ARGUMENT_DEFAULT(const char*, HelpButtonStyle) { Style::Button::kNormalButtonStyleName };

	SLATE_ARGUMENT_DEFAULT(FName, HelpIcon) { Style::Brush::kStatusHelpIconName };

	SLATE_ARGUMENT_DEFAULT(TSharedPtr<SWidget>, HelpRowWidget) { nullptr };

	// Info
	SLATE_ARGUMENT(FText, InfoText)

	SLATE_ARGUMENT_DEFAULT(FText, InfoButtonText) { FText::GetEmpty() };

	SLATE_ARGUMENT_DEFAULT(const char*, InfoButtonStyle) { Style::Button::kNormalButtonStyleName };

	SLATE_ARGUMENT_DEFAULT(FName, InfoIcon) { Style::Brush::kStatusInfoIconName };

	SLATE_ARGUMENT_DEFAULT(TSharedPtr<SWidget>, InfoRowWidget) { nullptr };

	// Warning
	SLATE_ARGUMENT_DEFAULT(FText, WarningText) { FText() };

	SLATE_ARGUMENT_DEFAULT(FText, WarningButtonText) { FText::GetEmpty() };

	SLATE_ARGUMENT_DEFAULT(const char*, WarningButtonStyle) { Style::Button::kNormalButtonStyleName };

	SLATE_ARGUMENT_DEFAULT(FName, WarningIcon) { Style::Brush::kStatusWarningIconName };

	SLATE_ARGUMENT_DEFAULT(TSharedPtr<SWidget>, WarningRowWidget) { nullptr };

	// Failure
	SLATE_ARGUMENT(FText, FailureText)

	SLATE_ARGUMENT_DEFAULT(FText, FailureButtonText) { FText::GetEmpty() };

	SLATE_ARGUMENT_DEFAULT(const char*, FailureButtonStyle) { Style::Button::kNormalButtonStyleName };

	SLATE_ARGUMENT_DEFAULT(FName, FailureIcon) { Style::Brush::kStatusErrorIconName };

	SLATE_ARGUMENT_DEFAULT(TSharedPtr<SWidget>, FailureRowWidget) { nullptr };

	// Success
	SLATE_ARGUMENT(FText, ReadyToGoText)

	SLATE_ARGUMENT_DEFAULT(FText, ReadyToGoButtonText) { FText::GetEmpty() };

	SLATE_ARGUMENT_DEFAULT(const char*, ReadyToGoButtonStyle) { Style::Button::kNormalButtonStyleName };

	SLATE_ARGUMENT_DEFAULT(FName, ReadyToGoIcon) { Style::Brush::kStatusSuccessIconName };

	SLATE_ARGUMENT_DEFAULT(TSharedPtr<SWidget>, ReadyToGoRowWidget) { nullptr };

	SLATE_ARGUMENT_DEFAULT(bool, IconVAlignTop) { false };

	SLATE_ARGUMENT_DEFAULT(bool, ButtonVAlignTop) { false };

	SLATE_ARGUMENT_DEFAULT(ESetupMessageState, SetState) { ESetupMessageState::WarningMessage };

	SLATE_EVENT(FSimpleDelegate, OnButtonClicked)

	SLATE_EVENT(FOnUpdateSetupState, OnUpdateStateEachTick)

	SLATE_EVENT(FOnUpdateSetupState, OnUpdateState)

	SLATE_END_ARGS()

public:
	static constexpr const char* NoIcon = "";
	static constexpr const char* GoToSettingsButton = "GoToSettings";
	static constexpr const char* GoToDeploymentMenuButton = "GotToDeploymentMenu";

	void Construct(const FArguments& InArgs);

	TAttribute<bool> GetReadyToGoAttribute() const;

	// SWidget interface
	virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;
	// End of Swidget interface

	void Tick();

	void SetSetupState(ESetupMessageState state);
	ESetupMessageState GetCurrentState() const;
	void DisableAfterTime(double ms);

private:
	int32 GetSetupStateAsInt() const;
	bool IsReadyToGo() const;
	FSlateColor GetBorderColor() const;
	FSlateColor GetTextColor() const;

	TSharedRef<SWidget> MakeRow(FName IconName, const FText& Message, const FText& ButtonMessage, const char* ButtonStyle, TSharedPtr<SWidget> RowWidget, bool IconVAlignTop, bool ButtonVAlignTop);

	FReply OnButtonPressed();

	// Callback that handles message state changes from another instance
	void OnSetupMessageStateChanged(const SSetupMessage* Sender);

	// Updates the cache CachedSetupState 
	void UpdateCache();

	// Helper to change the state and send notification
	void ChangeSetupStateAndSendNotification(ESetupMessageState state);

private:
	ESetupMessageState CachedSetupState;
	FSimpleDelegate OnButtonClicked;
	FOnUpdateSetupState OnUpdateState;
	FOnUpdateSetupState OnUpdateStateEachTick;
	double StartingPointTimeSec = 0;
	double DisableAfterTimeSec = 0;

	static FOnSetupMessageStateChanged OnSetupMessageStateChangedMultiDelegate;
};
