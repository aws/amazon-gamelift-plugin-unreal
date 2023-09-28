// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SSetupMessage.h"

#include "EditorStyleSet.h"
#include "Framework/Notifications/NotificationManager.h"
#include "HAL/PlatformFilemanager.h"
#include "ISourceControlProvider.h"
#include "ISourceControlModule.h"

#include "GenericPlatform/GenericPlatformFile.h"
#include "SourceControlHelpers.h"

#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#include "GameLiftPluginStyle.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "SSetupMessage"

FOnSetupMessageStateChanged SSetupMessage::OnSetupMessageStateChangedMultiDelegate;

TSharedRef<SWidget> SSetupMessage::MakeRow(FName IconName, const FText& Message, const FText& ButtonMessage)
{
	TSharedRef<SHorizontalBox> Result = SNew(SHorizontalBox)
		// Status icon
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(8.0f)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(SBox)
			.WidthOverride(16)
			.HeightOverride(16)
			[
				SNew(SImage)
				.Image(FGameLiftPluginStyle::Get().GetBrush(IconName))
			]
		]

		// Status text
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.ColorAndOpacity(this, &SSetupMessage::GetTextColor)
			.Text(Message)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
		];
		
	if (!ButtonMessage.IsEmpty())
	{
		Result->AddSlot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(SPadding::Right2x)
		[
			SNew(SButton)
			.OnClicked(this, &SSetupMessage::OnButtonPressed)
			.Text(ButtonMessage)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
		];
	}

	return Result;
}

void SSetupMessage::Construct(const FArguments& InArgs)
{
	OnButtonClicked = InArgs._OnButtonClicked;
	OnUpdateState = InArgs._OnUpdateState;
	OnUpdateStateEachTick = InArgs._OnUpdateStateEachTick;
	CachedSetupState = InArgs._SetState;

	TSharedRef<SWidget> WarningWidget = MakeRow(InArgs._WarningIcon, InArgs._WarningText, InArgs._WarningButtonText);
	TSharedRef<SWidget> FailureWidget = MakeRow(InArgs._FailureIcon, InArgs._FailureText, InArgs._FailureButtonText);
	TSharedRef<SWidget> ReadyToGoWidget = MakeRow(InArgs._ReadyToGoIcon, InArgs._ReadyToGoText, InArgs._ReadyToGoButtonText);

	ChildSlot
	[
		SNew(SBorder)
		.BorderBackgroundColor(this, &SSetupMessage::GetBorderColor)
		.BorderImage(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kBorderImageName))
		[
			SNew(SWidgetSwitcher)
			.WidgetIndex(this, &SSetupMessage::GetSetupStateAsInt)

			// Locked slot
			+ SWidgetSwitcher::Slot()
			[
				WarningWidget
			]
			+ SWidgetSwitcher::Slot()
			[
				FailureWidget
			]
			+ SWidgetSwitcher::Slot()
			[
				ReadyToGoWidget
			] 
			+ SWidgetSwitcher::Slot()
			[
				SNew(SBox)
			]
		]
	];

	UpdateCache();

	// Listen to "message state change" notifications to update the UI when the change comes from another instance.
	// Keeps a weak reference to the object
	OnSetupMessageStateChangedMultiDelegate.AddSP(this, &SSetupMessage::OnSetupMessageStateChanged);
}

// InCurrentTime is FPlatformTime::Seconds() by SlateApplication.cpp
void SSetupMessage::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (OnUpdateStateEachTick.IsBound())
	{
		ChangeSetupStateAndSendNotification(OnUpdateStateEachTick.Execute(CachedSetupState));
	}

	if (DisableAfterTimeSec > 0 && InCurrentTime - StartingPointTimeSec > DisableAfterTimeSec)
	{
		DisableAfterTimeSec = 0;
		ChangeSetupStateAndSendNotification(ESetupMessageState::DismissedMessage);
	}
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

void SSetupMessage::Tick()
{
	if (OnUpdateState.IsBound())
	{
		ChangeSetupStateAndSendNotification(OnUpdateState.Execute(CachedSetupState));
	}
}

void SSetupMessage::SetSetupState(ESetupMessageState NewState)
{
	ChangeSetupStateAndSendNotification(NewState);
}

ESetupMessageState SSetupMessage::GetCurrentState() const
{
	return CachedSetupState;
}

int32 SSetupMessage::GetSetupStateAsInt() const
{
	return (int32)CachedSetupState;
}

void SSetupMessage::UpdateCache()
{
	if (OnUpdateState.IsBound())
	{
		CachedSetupState = OnUpdateState.Execute(CachedSetupState);
	}
}

void SSetupMessage::ChangeSetupStateAndSendNotification(ESetupMessageState state)
{
	CachedSetupState = state;

	// Broadcast change
	OnSetupMessageStateChangedMultiDelegate.Broadcast(this);
}

FSlateColor SSetupMessage::GetBorderColor() const
{
	switch (CachedSetupState)
	{
		case ESetupMessageState::DismissedMessage:
			return FLinearColor().Transparent;
		case ESetupMessageState::WarningMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kWarningBackground);
		case ESetupMessageState::FailureMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kErrorBackground);
		case ESetupMessageState::ReadyToGoMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kSuccessBackground);
		default:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kWarningBackground);
	}
}

FSlateColor SSetupMessage::GetTextColor() const
{
	switch (CachedSetupState)
	{
		case ESetupMessageState::WarningMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kWarningForeground);
		case ESetupMessageState::FailureMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kErrorForeground);
		case ESetupMessageState::ReadyToGoMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kSuccessForeground);
		default:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kWarningForeground);
	}
}

FReply SSetupMessage::OnButtonPressed()
{
	OnButtonClicked.ExecuteIfBound();
	return FReply::Handled();
}

void SSetupMessage::OnSetupMessageStateChanged(const SSetupMessage* Sender)
{
	if (this != Sender)
	{
		// Message state has changed externally, udpate the cache
		UpdateCache();
	}
}

void SSetupMessage::DisableAfterTime(double seconds)
{
	StartingPointTimeSec = FPlatformTime::Seconds();
	DisableAfterTimeSec = seconds;
}

bool SSetupMessage::IsReadyToGo() const
{
	return CachedSetupState == ESetupMessageState::ReadyToGoMessage;
}

TAttribute<bool> SSetupMessage::GetReadyToGoAttribute() const
{
	return TAttribute<bool>(this, &SSetupMessage::IsReadyToGo);
}

#undef LOCTEXT_NAMESPACE
