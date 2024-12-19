// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SAnywhereGenerateAuthTokenMenu.h"

#include <Async/Async.h>

#include "SMenu/SGameLiftSettingsAwsAccountMenu.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/STextStatus.h"

#include "IGameLiftCoreModule.h"
#include "GameLiftPlugin.h"
#include "GameLiftPluginStyle.h"
#include <Developer/Settings/Public/ISettingsModule.h>

#include "Settings/UGameLiftAnywhereStatus.h"
#include "Settings/UGameLiftSettings.h"

#define LOCTEXT_NAMESPACE "SAnywhereGenerateAuthTokenMenu"

void SAnywhereGenerateAuthTokenMenu::Construct(const FArguments& InArgs)
{
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployAnywhere::kAuthTokenTitle)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Fill)
				[
					SAssignNew(AuthTokenTextView, SEditableText)
					.Text(Menu::DeployAnywhere::kAuthTokenNotGeneratedText)
					.Style(FGameLiftPluginStyle::Get(), Style::EditableText::kFieldMedium)
					.IsReadOnly(true)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Fill)
				.Padding(SPadding::Top)
				[
					SAssignNew(AuthTokenNoteView, STextBlock)
					.Text(Menu::DeployAnywhere::kAuthTokenGenerateNoteText)
					.AutoWrapText(true)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote)
				]
			)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Left)
		.Padding(SPadding::Top_Bottom)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SNamedRow)
				.RowWidget(
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Left)
					.Padding(SPadding::Right2x)
					[
						SNew(SButton)
						.Text(Menu::DeployAnywhere::kAuthTokenGenerateButtonText)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
						.IsEnabled_Raw(this, &SAnywhereGenerateAuthTokenMenu::CanGenerateAuthToken)
						.OnClicked_Raw(this, &SAnywhereGenerateAuthTokenMenu::OnGenerateAuthTokenButtonClicked)
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
				)
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.Padding(SPadding::Top_Bottom)
		[
			SAssignNew(GenerateAuthTokenErrorRow, SNamedRow)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SAssignNew(GenerateAuthTokenErrorTextBlock, STextBlock)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote)
				.AutoWrapText(true)
			)
			.Visibility(EVisibility::Collapsed)
		];

	SSectionStep::Construct(
		SSectionStep::FArguments()
		.HeaderTitle(Menu::DeployAnywhere::kGenerateAuthTokenHeader)
		.HeaderDescription(FText::FromString("DESCRIPTION TODO"))
		.BodyContent()
		[
			VerticalBox
		]);

	GenerateAuthTokenErrorTextBlock->SetColorAndOpacity(FGameLiftPluginStyle::Get().GetColor(Style::Color::kError));

	// Listen to profile changes
	SGameLiftSettingsAwsAccountMenu::OnProfileSelectionChangedMultiDelegate.AddSP(this, &SAnywhereGenerateAuthTokenMenu::OnBootstrapStatusChanged);

	// Initialize section UI based on state
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	if (AnywhereStatus->AuthToken.IsEmpty())
	{
		ResetAndCollapseSection();
	}
}

void SAnywhereGenerateAuthTokenMenu::OnBootstrapStatusChanged(const SGameLiftSettingsAwsAccountMenu* /* Sender */)
{
	UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
	if (EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::NoBootstrappedMessage)
	{
		InvalidateAuthToken();
	}
}

void SAnywhereGenerateAuthTokenMenu::UpdateUI()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	if (!AnywhereStatus->AuthToken.IsEmpty())
	{
		FString AuthTokenExpirationString = FText::AsDateTime(AnywhereStatus->AuthTokenExpirationTime, EDateTimeStyle::Short, EDateTimeStyle::Medium).ToString();
		FString DisplayString = FString::Format(TEXT("{0}  |  Valid until {1}"), { AnywhereStatus->AuthToken, AuthTokenExpirationString });

		AuthTokenTextView->SetText(FText::FromString(DisplayString));
		AuthTokenNoteView->SetVisibility(EVisibility::Visible);
		SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressComplete);
		StartNextSection();
	}
	else
	{
		AuthTokenTextView->SetText(Menu::DeployAnywhere::kAuthTokenNotGeneratedText);
		AuthTokenNoteView->SetVisibility(EVisibility::Collapsed);
	}
}

void SAnywhereGenerateAuthTokenMenu::StartSection()
{
	InvalidateAuthToken();
}

void SAnywhereGenerateAuthTokenMenu::InvalidateAuthToken()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	AnywhereStatus->AuthToken = FString();
	AnywhereStatus->AuthTokenExpirationTime = FDateTime();

	AnywhereStatus->SaveConfig();

	UpdateUI();
}

bool SAnywhereGenerateAuthTokenMenu::CanGenerateAuthToken() const
{
	const UGameLiftAnywhereStatus& AnywhereStatus = *GetMutableDefault<UGameLiftAnywhereStatus>();

	return AnywhereStatus.IsFleetDeployed && AnywhereStatus.IsComputeRegistered && !IsLoading;
}

bool SAnywhereGenerateAuthTokenMenu::GenerateAuthTokenSync()
{
	IsLoading = true;

	TTuple<bool, FString> GenerateResult = GenerateAuthToken();

	Async(EAsyncExecution::TaskGraphMainThread,
		[this, GenerateResult = MoveTemp(GenerateResult)]()
		{
			if (GenerateResult.Get<0>())
			{
				UpdateUI();

				UpdateErrorMessage(FText::GetEmpty());
			}
			else
			{
				UpdateErrorMessage(FText::FromString(GenerateResult.Get<1>()));
				SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressError);
			}
		});

	IsLoading = false;

	return GenerateResult.Get<0>();
}

FReply SAnywhereGenerateAuthTokenMenu::OnGenerateAuthTokenButtonClicked()
{
	ResetAndCollapseNextSections();

	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	IsLoading = true;

	Async(EAsyncExecution::Thread,
		[this]()
		{
			TTuple<bool, FString> GenerateResult = GenerateAuthToken();

			Async(EAsyncExecution::TaskGraphMainThread,
				[this, GenerateResult = MoveTemp(GenerateResult)]()
				{
					if (GenerateResult.Get<0>())
					{
						UpdateUI();

						UpdateErrorMessage(FText::GetEmpty());
					}
					else
					{
						UpdateErrorMessage(FText::FromString(GenerateResult.Get<1>()));
					}
				});

			IsLoading = false;
		});

	return FReply::Handled();
}

TTuple<bool, FString> SAnywhereGenerateAuthTokenMenu::GenerateAuthToken()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	IGameLiftAnywhereHandler& Handler = IGameLiftCoreModule::Get().GetGameLiftAnywhereHandler();

	GameLiftAnywhereAuthTokenResult AuthTokenResult = Handler.GenerateAuthToken(AnywhereStatus->FleetId, AnywhereStatus->ComputeName);

	if (AuthTokenResult.bIsSuccessful)
	{
		AnywhereStatus->AuthToken = AuthTokenResult.AuthToken;
		AnywhereStatus->AuthTokenExpirationTime = AuthTokenResult.ExpirationTime;

		AnywhereStatus->SaveConfig();

		return MakeTuple(true, TEXT(""));
	}
	else
	{
		return MakeTuple(false, AuthTokenResult.ErrorMessage);
	}
}

void SAnywhereGenerateAuthTokenMenu::UpdateErrorMessage(const FText& ErrorMessage)
{
	if (ErrorMessage.IsEmpty())
	{
		GenerateAuthTokenErrorRow->SetVisibility(EVisibility::Collapsed);
		GenerateAuthTokenErrorTextBlock->SetText(FText::GetEmpty());
	}
	else
	{
		GenerateAuthTokenErrorRow->SetVisibility(EVisibility::Visible);
		GenerateAuthTokenErrorTextBlock->SetText(ErrorMessage);
	}			
}

#undef LOCTEXT_NAMESPACE
