// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SBootstrapStatus.h"

#include <EditorStyleSet.h>
#include <Widgets/SBoxPanel.h>
#include <Widgets/Layout/SBorder.h>
#include <Widgets/Layout/SWidgetSwitcher.h>

#include "Settings/UGameLiftDeploymentStatus.h"
#include "Settings/UGameLiftSettings.h"

#include "SWidgets/SNamedRow.h"
#include "SWidgets/STextStatus.h"

#include "GameLiftPluginStyle.h"

namespace Internal
{
	TSharedRef<SWidget> MakeRegionInfoWidget()
	{
		TSharedPtr<SWidget> RowWidget = SNew(SEditableText)
			.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
			.IsReadOnly(true)
			.Text_Lambda([&]
			{
				UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
				return Settings->AwsRegion;
			});

		return SNew(SNamedRow)
			.NameText(Settings::AwsAccount::kRegionNameText)
			.RowWidget(RowWidget)
			.SecondaryColumnLeftPadding(true);
	}

	TSharedRef<SWidget> MakeBucketNameWidget()
	{
		TSharedPtr<SWidget> RowWidget = SNew(SEditableText)
			.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
			.IsReadOnly(true)
			.Text_Lambda([&]
			{
				UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
				return Settings->S3Bucket.IsEmpty() ? Settings::AwsAccount::kEmptyBucketNameText : Settings->S3Bucket;
			});

		return SNew(SNamedRow)
			.NameText(Settings::AwsAccount::kBucketNameText)
			.RowWidget(RowWidget)
			.SecondaryColumnLeftPadding(true);
	}

	TSharedRef<SWidget> MakeNoBootstrapStatusWidget()
	{
		TSharedRef<STextStatus> TextStatus = SNew(STextStatus)
			.StatusText(Settings::AwsAccount::kNoBootstrapMessage)
			.StatusTextStyle(Style::Text::kFieldBold)
			.IconState(STextStatus::EIconState::Inactive);

		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				MakeBucketNameWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				MakeRegionInfoWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				SNew(SNamedRow)
				.NameText(Settings::AwsAccount::kBootstrapStatusText)
				.RowWidget(TextStatus)
				.SecondaryColumnLeftPadding(true)
			];
	}

	TSharedRef<SWidget> MakeInProgressStatusWidget()
	{
		TSharedRef<STextStatus> LoadingStatus = SNew(STextStatus)
			.StatusText(Settings::AwsAccount::kBootstrapInProgressMessage)
			.StatusTextStyle(Style::Text::kFieldBold)
			.IconState(STextStatus::EIconState::Loading);

		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				MakeBucketNameWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				MakeRegionInfoWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				SNew(SNamedRow)
				.NameText(Settings::AwsAccount::kBootstrapStatusText)
				.RowWidget(LoadingStatus)
				.SecondaryColumnLeftPadding(true)
			];
	}

	TSharedRef<SWidget> MakeActiveStatusWidget()
	{
		TSharedRef<STextStatus> TextStatus = SNew(STextStatus)
			.StatusText(Settings::AwsAccount::kActiveBootstrapMessage)
			.StatusTextStyle(Style::Text::kFieldBold)
			.IconState(STextStatus::EIconState::Success);

		TextStatus->SetStatusTextColor(FGameLiftPluginStyle::Get().GetColor(Style::Color::kSuccess));

		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				MakeBucketNameWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				MakeRegionInfoWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				SNew(SNamedRow)
				.NameText(Settings::AwsAccount::kBootstrapStatusText)
				.RowWidget(TextStatus)
				.SecondaryColumnLeftPadding(true)
			];
	}

	TSharedRef<SWidget> MakeFailureStatusWidget()
	{
		TSharedRef<STextStatus> TextStatus = SNew(STextStatus)
			.StatusText(Settings::AwsAccount::kFailedBootstrapMessage)
			.StatusTextStyle(Style::Text::kFieldBold)
			.IconState(STextStatus::EIconState::Error);

		TextStatus->SetStatusTextColor(FGameLiftPluginStyle::Get().GetColor(Style::Color::kError));

		TSharedPtr<STextBlock> ErrorMessage;
		SAssignNew(ErrorMessage, STextBlock)
			.Text_Lambda([]() 
			{
				return GetMutableDefault<UGameLiftSettings>()->BootstrapError;
			})
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote);
		ErrorMessage->SetColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kError));

		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				MakeBucketNameWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				MakeRegionInfoWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				SNew(SNamedRow)
				.NameText(Settings::AwsAccount::kBootstrapStatusText)
				.RowWidget(TextStatus)
				.SecondaryColumnLeftPadding(true)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Bottom)
			[
				SNew(SNamedRow)
				.RowWidget(ErrorMessage)
				.SecondaryColumnLeftPadding(true)
			];
	}
} // namespace Internal

#define LOCTEXT_NAMESPACE "SBootstrapStatus"

FOnBootstrapStatusChanged SBootstrapStatus::OnBootstrapStatusChangedMultiDelegate;

void SBootstrapStatus::Construct(const FArguments& InArgs)
{
	OnUpdateState = InArgs._OnUpdateState;	

	TSharedRef<SWidget> NeedDeploymentWidget = Internal::MakeNoBootstrapStatusWidget();
	TSharedRef<SWidget> InProgressWidget = Internal::MakeInProgressStatusWidget();
	TSharedRef<SWidget> ActiveWidget = Internal::MakeActiveStatusWidget();
	TSharedRef<SWidget> FailureWidget = Internal::MakeFailureStatusWidget();

	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	CachedSetupState = EBootstrapMessageStateFromInt(Settings->BootstrapStatus);

	ChildSlot
	[
		SNew(SWidgetSwitcher)
		.WidgetIndex(this, &SBootstrapStatus::GetSetupStateAsInt)
		+ SWidgetSwitcher::Slot()
		[
			NeedDeploymentWidget
		]
		+ SWidgetSwitcher::Slot()
		[
			InProgressWidget
		]
		+ SWidgetSwitcher::Slot()
		[
			FailureWidget
		]
		+ SWidgetSwitcher::Slot()
		[
			ActiveWidget
		]
	];

	UpdateCache();

	// Listen to "bootstrap status change" notifications to update the UI when the change comes from another instance.
	// Keeps a weak reference to the object
	OnBootstrapStatusChangedMultiDelegate.AddSP(this, &SBootstrapStatus::OnBootstrapStatusChanged);
}

void SBootstrapStatus::OnNeedBootstrap()
{
	UpdateState(EBootstrapMessageState::NoBootstrappedMessage);
}

void SBootstrapStatus::OnBootstrap()
{
	UpdateState(EBootstrapMessageState::InProgressMessage);
}

void SBootstrapStatus::OnFailure(const FText& ErrorMessage)
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	Settings->BootstrapError = ErrorMessage;
	UpdateState(EBootstrapMessageState::FailureMessage);
}

void SBootstrapStatus::OnSucceeded(const FString& BucketName)
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	Settings->S3Bucket = FText::FromString(BucketName);
	OnSucceeded();
}

void SBootstrapStatus::OnSucceeded()
{
	UpdateState(EBootstrapMessageState::ActiveMessage);
}

void SBootstrapStatus::OnBootstrapStatusChanged(const SBootstrapStatus* Sender)
{
	if (this != Sender)
	{
		// Bootstrap status has changed externally, udpate the cache
		UpdateCache();
	}
}

int32 SBootstrapStatus::GetSetupStateAsInt() const
{
	return (int32)CachedSetupState;
}

void SBootstrapStatus::UpdateState(EBootstrapMessageState NewState)
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	if (Settings->BootstrapStatus != int(NewState))
	{
		Settings->BootstrapStatus = int(NewState);
		Settings->SaveConfig();

		UpdateCache();

		// Broadcast change
		OnBootstrapStatusChangedMultiDelegate.Broadcast(this);
	}
}

void SBootstrapStatus::UpdateCache()
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	CachedSetupState = EBootstrapMessageStateFromInt(Settings->BootstrapStatus);

	if (OnUpdateState.IsBound())
	{
		CachedSetupState = OnUpdateState.Execute(CachedSetupState);
	}
}

#undef LOCTEXT_NAMESPACE
