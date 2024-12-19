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

TSharedRef<SWidget> SSetupMessage::MakeRow(FName IconName, const FText& Message, const FText& ButtonMessage, const char* ButtonStyle, TSharedPtr<SWidget> RowWidget, bool IconVAlignTop, bool ButtonVAlignTop)
{
	const int IconSize = 18;

	TSharedRef<SHorizontalBox> Result = SNew(SHorizontalBox)
		// Status icon
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(SPadding::SetupMessageIconPadding)
		.VAlign(IconVAlignTop ? VAlign_Top : VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(SBox)
				.WidthOverride(IconSize)
				.HeightOverride(IconSize)
				[
					SNew(SImage)
						.Image(FGameLiftPluginStyle::Get().GetBrush(IconName))
				]
		];

		if (RowWidget != nullptr)
		{
			Result->AddSlot()
				.FillWidth(1)
				.Padding(SPadding::SetupMessageContentPadding)
				[
					RowWidget.ToSharedRef()
				];
		}
		else
		{
			// Status text
			Result->AddSlot()
				.VAlign(VAlign_Center)
				.Padding(SPadding::SetupMessageContentPadding)
				[
					SNew(STextBlock)
						.ColorAndOpacity(this, &SSetupMessage::GetTextColor)
						.Text(Message)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
						.AutoWrapText(true)
				];
		}
		
	if (!ButtonMessage.IsEmpty() || !FText::FromString(ButtonStyle).IsEmpty())
	{
		Result->AddSlot()
			.HAlign(HAlign_Right)
			.VAlign(ButtonVAlignTop ? VAlign_Top : VAlign_Center)
			.Padding(ButtonVAlignTop ? SPadding::CloseButtonTopPadding : SPadding::Right2x)
			.AutoWidth()
			[
				SNew(SButton)
				.OnClicked(this, &SSetupMessage::OnButtonPressed)
				.Text(ButtonMessage)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
				.ButtonStyle(FGameLiftPluginStyle::Get(), ButtonStyle)
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

	TSharedRef<SWidget> HelpWidget = MakeRow(InArgs._HelpIcon, InArgs._HelpText, InArgs._HelpButtonText,
		InArgs._HelpButtonStyle, InArgs._HelpRowWidget, InArgs._IconVAlignTop, InArgs._ButtonVAlignTop);
	TSharedRef<SWidget> InfoWidget = MakeRow(InArgs._InfoIcon, InArgs._InfoText, InArgs._InfoButtonText, 
		InArgs._InfoButtonStyle, InArgs._InfoRowWidget, InArgs._IconVAlignTop, InArgs._ButtonVAlignTop);
	TSharedRef<SWidget> WarningWidget = MakeRow(InArgs._WarningIcon, InArgs._WarningText, InArgs._WarningButtonText, 
		InArgs._WarningButtonStyle, InArgs._WarningRowWidget, InArgs._IconVAlignTop, InArgs._ButtonVAlignTop);
	TSharedRef<SWidget> FailureWidget = MakeRow(InArgs._FailureIcon, InArgs._FailureText, InArgs._FailureButtonText, 
		InArgs._FailureButtonStyle, InArgs._FailureRowWidget, InArgs._IconVAlignTop, InArgs._ButtonVAlignTop);
	TSharedRef<SWidget> ReadyToGoWidget = MakeRow(InArgs._ReadyToGoIcon, InArgs._ReadyToGoText, InArgs._ReadyToGoButtonText, 
		InArgs._ReadyToGoButtonStyle, InArgs._ReadyToGoRowWidget, InArgs._IconVAlignTop, InArgs._ButtonVAlignTop);

	ChildSlot
	[
		SNew(SBorder)
		.BorderBackgroundColor(this, &SSetupMessage::GetBorderColor)
		.BorderImage(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kBorderImageName))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(SPadding::Border)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor::Black)
			.BorderImage(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kBorderImageName))
			[
				SNew(SWidgetSwitcher)
				.WidgetIndex(this, &SSetupMessage::GetSetupStateAsInt)

				// Locked slot
				+ SWidgetSwitcher::Slot()
				[
					HelpWidget
				]
				+ SWidgetSwitcher::Slot()
				[
					InfoWidget
				]
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
		case ESetupMessageState::HelpMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kHelpBackground);
		case ESetupMessageState::InfoMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kInfoBackground);
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
		case ESetupMessageState::HelpMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kHelpForeground);
		case ESetupMessageState::InfoMessage:
			return FGameLiftPluginStyle::Get().GetColor(Style::Color::kInfoForeground);
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
