// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftDeployAnywhereMenu.h"

#include <Widgets/SBoxPanel.h>
#include <Widgets/Layout/SSeparator.h>
#include <Framework/MetaData/DriverMetaData.h>
#include <Async/Async.h>

#include "SAnywhereGenerateAuthTokenMenu.h"
#include "SAnywhereRegisterComputeMenu.h"
#include "SCommonMenuSections.h"
#include "SConnectAnywhereFleetMenu.h"
#include "SWidgets/SPathInput.h"
#include "SWidgets/STextStatus.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SSetupMessage.h"
#include "SWidgets/SBootstrapStatus.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SSectionsWithHeaders.h"

#include "IGameLiftAnywhereHandler.h"
#include "IGameLiftCoreModule.h"
#include "GameLiftPlugin.h"
#include "GameLiftPluginStyle.h"
#include <Developer/Settings/Public/ISettingsModule.h>

#include "Settings/UGameLiftAnywhereStatus.h"
#include "Settings/UGameLiftDeploymentStatus.h"
#include "Settings/UGameLiftSettings.h"
#include "Utils/Misc.h"

#define LOCTEXT_NAMESPACE "SGameLiftDeploymentAnywhereMenu"

void SGameLiftDeployAnywhereMenu::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	
	// Create the widgets
	TSharedPtr<SSectionsWithHeaders> SectionsWithHeaders = SNew(SSectionsWithHeaders);
	SectionsWithHeaders->AddSection((SAssignNew(SetProfileSection, SSetProfileSection))->GetSectionInfo());
	SectionsWithHeaders->AddSection((SAssignNew(IntegrateGameSection, SIntegrateGameSection).HowToIntegrateYourGameLinkUrl(Url::kHowToIntegrateYourGameForAnywhereUrl))->GetSectionInfo());
	SectionsWithHeaders->AddSection(Menu::DeployAnywhere::kConnectToFleetHeader, CreateConnectToFleetSection(), false);
	SectionsWithHeaders->AddSection(Menu::DeployAnywhere::kRegisterComputeHeader, CreateRegisterComputeSection(), false);
	SectionsWithHeaders->AddSection(Menu::DeployAnywhere::kGenerateAuthTokenHeader, CreateAuthTokenSection(), false);
	SectionsWithHeaders->AddSection(Menu::DeployAnywhere::kLaunchGameServerAndClientHeader, CreateGameServerAndClientSection(), false);

	ChildSlot
		.Padding(SPadding::Top_Bottom + SPadding::Extra_For_Page_End) // This adds more space at the bottom so users can scroll down further.
		[
			SectionsWithHeaders.ToSharedRef()
		];
}

TSharedRef<SWidget> SGameLiftDeployAnywhereMenu::CreateConnectToFleetSection()
{
	return SAssignNew(AnywhereConnectFleetSection, SConnectAnywhereFleetMenu)
		.OnFleetChangedDelegate(this, &SGameLiftDeployAnywhereMenu::OnFleetChanged);
}

TSharedRef<SWidget> SGameLiftDeployAnywhereMenu::CreateRegisterComputeSection()
{
	return SAssignNew(AnywhereRegisterComputeSection, SAnywhereRegisterComputeMenu)
		.OnComputeChangedDelegate(this, &SGameLiftDeployAnywhereMenu::OnComputeChanged);
}

TSharedRef<SWidget> SGameLiftDeployAnywhereMenu::CreateAuthTokenSection()
{
	return SAssignNew(AnywhereGenerateAuthTokenSection, SAnywhereGenerateAuthTokenMenu);
}

bool SGameLiftDeployAnywhereMenu::CanLaunchServer() const
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	return AnywhereStatus->IsAnywhereReady() && !IsLaunchingGameServer && !IntegrateGameSection->GetGameServerPath().IsEmpty();
}

bool SGameLiftDeployAnywhereMenu::CanLaunchClient() const
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	return AnywhereStatus->IsAnywhereReady() && !IsLaunchingGameClient && !IntegrateGameSection->GetGameClientPath().IsEmpty();
}

void SGameLiftDeployAnywhereMenu::OnFleetChanged()
{
	AnywhereRegisterComputeSection->InvalidateCompute();
	AnywhereGenerateAuthTokenSection->InvalidateAuthToken();
}

void SGameLiftDeployAnywhereMenu::OnComputeChanged()
{
	AnywhereGenerateAuthTokenSection->InvalidateAuthToken();
}

FReply SGameLiftDeployAnywhereMenu::OnLaunchServerButtonClicked()
{
	FString GameServerPath = IntegrateGameSection->GetGameServerPath();

	IsLaunchingGameServer = true;

	Async(EAsyncExecution::Thread,
		[this, GameServerPath = MoveTemp(GameServerPath)]
		{
			bool bGenerateResult = AnywhereGenerateAuthTokenSection->GenerateAuthTokenSync();

			if (!bGenerateResult)
			{
				IsLaunchingGameServer = false;

				UE_LOG(GameLiftPluginLog, Error, TEXT("Launch aborted. Failed to generate auth token when launching server."));
				return;
			}

			UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

			TArray<FString> LaunchParameters;
			LaunchParameters.Add(Menu::DeployAnywhere::kGameServerLaunchParameterLog);
			LaunchParameters.Add(Menu::DeployAnywhere::kGameServerLaunchParameterEnableAnywhere);
			LaunchParameters.Add(FString::Format(Menu::DeployAnywhere::kGameServerLaunchParameterFleetId, { *AnywhereStatus->FleetId }));
			LaunchParameters.Add(FString::Format(Menu::DeployAnywhere::kGameServerLaunchParameterHostId, { *AnywhereStatus->ComputeName }));
			LaunchParameters.Add(FString::Format(Menu::DeployAnywhere::kGameServerLaunchParameterAuthToken, { *AnywhereStatus->AuthToken }));

			FString WebSocketUrl = FString::Format(Menu::DeployAnywhere::kGameServerWebSocketUrlFormat, { *AnywhereStatus->DeployedRegion });
			LaunchParameters.Add(FString::Format(Menu::DeployAnywhere::kGameServerLaunchParameterWebSocketUrl, { *WebSocketUrl }));

			auto Runner = IGameLiftCoreModule::Get().MakeRunner();
			bool bIsLaunched = Runner->LaunchProcess(GameServerPath, LaunchParameters);

			if (bIsLaunched)
			{
				UE_LOG(GameLiftPluginLog, Log, TEXT("Launched game server: %s"), *GameServerPath);
			}
			else
			{
				UE_LOG(GameLiftPluginLog, Error, TEXT("Failed to launch game server: %s"), *GameServerPath);
			}

			IsLaunchingGameServer = false;
		});

	return FReply::Handled();
}

FReply SGameLiftDeployAnywhereMenu::OnLaunchClientButtonClicked()
{
	FString GameClientPath = IntegrateGameSection->GetGameClientPath();

	IsLaunchingGameClient = true;

	Async(EAsyncExecution::Thread,
		[this, GameClientPath = MoveTemp(GameClientPath)]
		{
			UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
			UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();

			TArray<FString> LaunchParameters;
			LaunchParameters.Add(Menu::DeployAnywhere::kGameClientLaunchParameterWindowMode);

			// Pass credential profile name to the client build so the client can set it to call Amazon GameLift APIs.
			LaunchParameters.Add(FString::Format(Menu::DeployAnywhere::kGameClientLaunchParameterCredentialsName, { *Settings->ProfileName.ToString() }));
			LaunchParameters.Add(FString::Format(Menu::DeployAnywhere::kGameClientLaunchParameterFleetId, { *AnywhereStatus->FleetId }));
			LaunchParameters.Add(FString::Format(Menu::DeployAnywhere::kGameClientLaunchParameterCustomLocation, { *AnywhereStatus->CustomLocation }));

			auto Runner = IGameLiftCoreModule::Get().MakeRunner();
			bool bIsLaunched = Runner->LaunchProcess(GameClientPath, LaunchParameters);

			if (bIsLaunched)
			{
				UE_LOG(GameLiftPluginLog, Log, TEXT("Launched game client: %s"), *GameClientPath);
			}
			else
			{
				UE_LOG(GameLiftPluginLog, Error, TEXT("Failed to launch game client: %s"), *GameClientPath);
			}

			IsLaunchingGameClient = false;
		});

	return FReply::Handled();
}

TSharedRef<SWidget> SGameLiftDeployAnywhereMenu::CreateGameServerAndClientSection()
{
	return SNew(SVerticalBox)
		// Game server
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployAnywhere::kGameServerLaunchTitle)
			.RowWidget(
				SNew(SHorizontalBox)
				// Button to launch server
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.Padding(SPadding::Right2x)
				[
					SNew(SButton)
					.Text(Menu::DeployAnywhere::kGameServerLaunchButtonText)
					.OnClicked_Raw(this, &SGameLiftDeployAnywhereMenu::OnLaunchServerButtonClicked)
					.IsEnabled_Raw(this, &SGameLiftDeployAnywhereMenu::CanLaunchServer)
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
						return IsLaunchingGameServer ? EVisibility::Visible : EVisibility::Hidden;
					})
				]
			)
		]
		// Game client
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployAnywhere::kGameClientLaunchTitle)
			.RowWidget(
				SNew(SHorizontalBox)
				// Button to launch client
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.Padding(SPadding::Right2x)
				[
					SNew(SButton)
					.Text(Menu::DeployAnywhere::kGameClientLaunchButtonText)
					.OnClicked_Raw(this, &SGameLiftDeployAnywhereMenu::OnLaunchClientButtonClicked)
					.IsEnabled_Raw(this, &SGameLiftDeployAnywhereMenu::CanLaunchClient)
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
						return IsLaunchingGameClient ? EVisibility::Visible : EVisibility::Hidden;
					})
				]
			)
		]
		// Launch note
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.SecondaryColumnLeftPadding(true)
			.RowWidget(
				SNew(STextBlock)
				.Text(Menu::DeployAnywhere::kGameLaunchNoteText)
				.AutoWrapText(true)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote)
			)
		];
}

#undef LOCTEXT_NAMESPACE
