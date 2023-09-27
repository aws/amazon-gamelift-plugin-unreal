// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SDeploymentStatus.h"

#include <Widgets/SBoxPanel.h>
#include <Widgets/Layout/SBorder.h>
#include <EditorStyleSet.h>
#include <Widgets/Layout/SWidgetSwitcher.h>

#include "SWidgets/STextStatus.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SNamedRow.h"

#include "Settings/UGameLiftDeploymentStatus.h"
#include "Settings/UGameLiftSettings.h"

#include "GameLiftPluginStyle.h"

namespace Internal
{
	TSharedRef<SWidget> MakeAWSRegionStatus()
	{
		return SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kAwsRegionText)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(SEditableText)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
				.IsReadOnly(true)
				.Text_Lambda([]
				{
					UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
					return Settings->DeployedRegion;
				})
			);
	}

	TSharedRef<SWidget> MakeScenarioStatus()
	{
		return SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kScenarioText)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(SEditableText)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
				.IsReadOnly(true)
				.Text_Lambda([]
				{
					UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
					return Settings->Scenario;
				})
			);
	}

	TSharedRef<SWidget> MakeGameNameStatus()
	{
		return SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kBuildNameText)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(SEditableText)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
				.IsReadOnly(true)
				.Text_Lambda([]
				{
					UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
					return Settings->BuildName;
				})
			);
	}

	TSharedRef<SWidget> MakeDeploymentStatus(FString &&Text, STextStatus::EIconState IconState, FName Color = FName())
	{
		TSharedPtr<STextStatus> TextStatus = SNew(STextStatus)
			.StatusText(FText::FromString(Text))
			.StatusTextStyle(Style::Text::kFieldBold)
			.IconState(IconState);

		if (!Color.IsNone())
		{
			TextStatus->SetStatusTextColor(FGameLiftPluginStyle::Get().GetColor(Color));
		}

		return SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kDeploymentStatusText)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				[
					TextStatus.ToSharedRef()
				]
			);
	}

	TSharedRef<SWidget> MakeNeedDeploymentWidget()
	{
		TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);
		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)
			[
				MakeDeploymentStatus(Menu::DeployManagedEC2::kNoDeployment, STextStatus::EIconState::Inactive)
			];

		return VerticalBox;
	}

	TSharedRef<SVerticalBox> AddInProgressStatuses(TSharedRef<SVerticalBox> VerticalBox)
	{
		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)[MakeScenarioStatus()];
		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)[MakeGameNameStatus()];
		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)[MakeAWSRegionStatus()];
		return VerticalBox;
	}

	TSharedRef<SWidget> MakeInProgressWidget()
	{
		TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

		AddInProgressStatuses(VerticalBox);

		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			MakeDeploymentStatus(Menu::DeployManagedEC2::kInProgressDeployment, STextStatus::EIconState::Loading)
		];

		return VerticalBox;
	}

	TSharedRef<SWidget> MakeAbortInProgressWidget()
	{
		TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

		AddInProgressStatuses(VerticalBox);

		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			MakeDeploymentStatus(Menu::DeployManagedEC2::kAbortInProgressDeployment, STextStatus::EIconState::Loading)
		];

		return VerticalBox;
	}

	TSharedRef<SWidget> MakeActiveWidget()
	{
		TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);
		AddInProgressStatuses(VerticalBox);

		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			MakeDeploymentStatus(Menu::DeployManagedEC2::kActiveDeployment, STextStatus::EIconState::Success, Style::Color::kSuccess)
		];

		UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
		Settings->LastUpdated = FDateTime::Now();
		Settings->SaveConfig();

		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kLastUpdatedText)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(SEditableText)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
				.IsReadOnly(true)
				.Text_Lambda([]
				{
					UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
					return FText::AsDateTime(Settings->LastUpdated, EDateTimeStyle::Short, EDateTimeStyle::Medium);
				})
			)
		];

		VerticalBox->AddSlot().AutoHeight().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kCognitoClientIdText)
			.NameTooltipText(Menu::DeployManagedEC2::kCognitoClientIdTooltip)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(SEditableText)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
				.IsReadOnly(true)
				.Text_Lambda([]
				{
					UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
					return Settings->CognitoClientId;
				})
			)
		];

		VerticalBox->AddSlot().AutoHeight().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kApiGatewayEndpointText)
			.NameTooltipText(Menu::DeployManagedEC2::kApiGatewayEndpointTooltip)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(SEditableText)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
				.IsReadOnly(true)
				.Text_Lambda([]
				{
					UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
					return Settings->ApiGatewayEndpoint;
				})
			)
		];

		return VerticalBox;
	}

	TSharedRef<SWidget> MakeFailureWidget()
	{
		TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);
		AddInProgressStatuses(VerticalBox);

		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			MakeDeploymentStatus(Menu::DeployManagedEC2::kFailedDeployment, STextStatus::EIconState::Error, Style::Color::kError)
		];

		TSharedPtr<STextBlock> ErrorMessage;
		SAssignNew(ErrorMessage, STextBlock)
			.Text_Lambda([]
			{
				UGameLiftDeploymentStatus* DeploymentStatus = GetMutableDefault<UGameLiftDeploymentStatus>();
				return DeploymentStatus->LatestError;
			})
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote);
		ErrorMessage->SetColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kError));

		VerticalBox->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kErrorMessageText)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				ErrorMessage
			)
			.Visibility_Lambda([]
			{
				UGameLiftDeploymentStatus* DeploymentStatus = GetMutableDefault<UGameLiftDeploymentStatus>();
				return DeploymentStatus->LatestError.IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible;
			})
		];

		return VerticalBox;
	}
}

#define LOCTEXT_NAMESPACE "SDeploymentStatus"

void SDeploymentStatus::Construct(const FArguments& InArgs)
{
	OnUpdateState = InArgs._OnUpdateState;	

	TSharedRef<SWidget> NeedDeploymentWidget = Internal::MakeNeedDeploymentWidget();
	TSharedRef<SWidget> InProgressWidget = Internal::MakeInProgressWidget();
	TSharedRef<SWidget> AbortInProgressWidget = Internal::MakeAbortInProgressWidget();
	TSharedRef<SWidget> ActiveWidget = Internal::MakeActiveWidget();
	TSharedRef<SWidget> FailureWidget = Internal::MakeFailureWidget();

	UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
	CachedSetupState = EDeploymentMessageState::NoDeploymentMessage;

	ChildSlot
	[
		SNew(SBox)
		[
			SNew(SWidgetSwitcher)
			.WidgetIndex(this, &SDeploymentStatus::GetSetupStateAsInt)
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
				AbortInProgressWidget
			]
			+ SWidgetSwitcher::Slot()
			[
				FailureWidget
			]
			+ SWidgetSwitcher::Slot()
			[
				ActiveWidget
			]
		]
	];

	UpdateCache();
}

void SDeploymentStatus::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
	auto NewState = EDeploymentMessageStateFromString(Settings->Status.ToString());

	if (NewState != CachedSetupState)
	{
		CachedSetupState = NewState;
		UpdateCache();
	}

	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

void SDeploymentStatus::OnDeploy()
{
	UpdateCache(EDeploymentMessageState::InProgressMessage);	
}

void SDeploymentStatus::OnAbort()
{
	UpdateCache(EDeploymentMessageState::AbortInProgressMessage);
}

void SDeploymentStatus::OnFailure()
{
	UpdateCache(EDeploymentMessageState::FailureMessage);
}

void SDeploymentStatus::OnSucceeded()
{
	UpdateCache(EDeploymentMessageState::ActiveMessage);
}

EDeploymentMessageState SDeploymentStatus::GetCurrentState() const
{
	return CachedSetupState;
}

void SDeploymentStatus::SetState(EDeploymentMessageState NewState)
{
	CachedSetupState = NewState;
}

int32 SDeploymentStatus::GetSetupStateAsInt() const
{
	return (int32)CachedSetupState;
}

void SDeploymentStatus::UpdateCache(EDeploymentMessageState NewState)
{
	UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
	Settings->Status = FText::FromString(EDeploymentMessageStateToString(NewState));
	Settings->SaveConfig();

	CachedSetupState = NewState;
	UpdateCache();
}

void SDeploymentStatus::UpdateCache()
{
	if (OnUpdateState.IsBound())
	{
		CachedSetupState = OnUpdateState.Execute(CachedSetupState);
	}
}

#undef LOCTEXT_NAMESPACE
