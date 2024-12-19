// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftDeployManagedEC2Menu.h"

#include "SMenu/SCommonMenuSections.h"
#include "SWidgets/SDeploymentFields.h"
#include "SWidgets/SDeploymentStatus.h"
#include "SWidgets/SLaunchBar.h"
#include "SWidgets/SExpandableSection.h"

#include "SSelectDeploymentScenarioSection.h"
#include "SDeployScenarioSection.h"
#include "SGameParametersSection.h"

#include "Settings/UGameLiftDeploymentStatus.h"

#include "Utils/Misc.h"
#include "Utils/Notifier.h"

#include "IGameLiftCoreModule.h"

#define LOCTEXT_NAMESPACE "SGameLiftDeployManagedEC2Content"

namespace Internal
{
	bool IsDeployed()
	{
		auto* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
		return EDeploymentMessageStateFromString(Settings->Status.ToString()) == EDeploymentMessageState::ActiveMessage;
	}
} // namespace Internal

void SGameLiftDeployManagedEC2Menu::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	DeploymentFields = SNew(SDeploymentFields);

	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);
	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Left5x_Right5x + SPadding::Top5x_Bottom5x)
		[
			SNew(SSetProfileSection).ReadDeveloperGuideLink(Url::kHelpDeployEC2LinkUrl)
		];

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Left5x_Right5x + SPadding::Bottom5x)
		[
			CreateDivider()
		];

	SectionsWithProgressBars = SNew(SSectionsWithProgressBars);
	SectionsWithProgressBars->AddSection(CreateIntegrateGameSection());
	SectionsWithProgressBars->AddSection(CreateSelectDeploymentScenarioSection());
	SectionsWithProgressBars->AddSection(CreateGameParametersSection());
	SectionsWithProgressBars->AddSection(CreateDeployScenarioSection());

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Left5x_Right5x + SPadding::Extra_For_Page_End) // This adds more space at the bottom so users can scroll down further.
		[
			SectionsWithProgressBars.ToSharedRef()
		];

	VerticalBox->AddSlot()
		.AutoHeight()
		[
			CreateLaunchBar()
		];

	ChildSlot
		[
			VerticalBox
		];
}

void SGameLiftDeployManagedEC2Menu::ResetFlow()
{
	SectionsWithProgressBars->ResetUI();
	UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
	Settings->ResetStatus();
	Settings->SaveConfig();
}

TSharedRef<SWidget> SGameLiftDeployManagedEC2Menu::CreateDivider()
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			SNew(SImage).Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kGameLiftDivider))
		];
}

TSharedRef<SSectionStep> SGameLiftDeployManagedEC2Menu::CreateIntegrateGameSection()
{
	return SNew(SIntegrateGameSection)
		.HideBuildPathInput(true)
		.HowToIntegrateYourGameLinkUrl(Url::kHowToIntegrateYourGameForEC2Url);;
}

TSharedRef<SSectionStep> SGameLiftDeployManagedEC2Menu::CreateSelectDeploymentScenarioSection()
{
	return SNew(SSelectDeploymentScenarioSection)
		.SetDeploymentFields(DeploymentFields);
}

TSharedRef<SSectionStep> SGameLiftDeployManagedEC2Menu::CreateGameParametersSection()
{
	return SNew(SGameParametersSection)
		.SetDeploymentFields(DeploymentFields);
}

TSharedRef<SSectionStep> SGameLiftDeployManagedEC2Menu::CreateDeployScenarioSection()
{
	return SNew(SDeployScenarioSection)
		.SetDeploymentFields(DeploymentFields);
}

TSharedRef<SWidget> SGameLiftDeployManagedEC2Menu::CreateLaunchBar()
{
	UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
	FString GameClientPath = Settings->GameClientFilePath.ToString();

	return SAssignNew(LaunchBar, SLaunchBar)
		.MenuType(EMenuType::EC2)
		.ParentWidget(this->AsWeak())
		.IsEnabled_Raw(this, &SGameLiftDeployManagedEC2Menu::CanLaunchGameClient)
		.DefaultClientBuildExecutablePath(GameClientPath)
		.OnStartClientButtonClicked(FStartClient::CreateRaw(this, &SGameLiftDeployManagedEC2Menu::OnLaunchClientButtonClicked));
}

void SGameLiftDeployManagedEC2Menu::SwitchDeploymentFields()
{
	AsSDeploymentFieldsRef(DeploymentFields)->SetFullMode();
}

bool SGameLiftDeployManagedEC2Menu::CanLaunchGameClient() const
{
	return !IsLaunchingGameClient && Internal::IsDeployed();
}

FText SGameLiftDeployManagedEC2Menu::TooltipLaunchGameClient() const
{
	if (!Internal::IsDeployed())
	{
		return Menu::DeployManagedEC2::kCannotLaunchGameClientNoDeploymentTooltipText;
	}

	return Menu::DeployManagedEC2::kCanLaunchGameClientTooltipText;
}

void SGameLiftDeployManagedEC2Menu::OnLaunchClientButtonClicked(FString GameClientPath)
{
	UGameLiftDeploymentStatus* Settings = GetMutableDefault<UGameLiftDeploymentStatus>();
	Settings->GameClientFilePath = FText::FromString(GameClientPath);
	Settings->SaveConfig();

	if (LaunchBar.IsValid())
	{
		LaunchBar->ChangeStartClientButtonUIState(SLaunchBar::EStartButtonUIState::Loading);
	}

	IsLaunchingGameClient = true;

	TArray<FString> Args;
	FString RunPath = Utils::Splitters::ExtractPathArgs(Settings->GameClientFilePath, Args);

	Async(EAsyncExecution::Thread, [this, RunPath = MoveTemp(RunPath), Args = MoveTemp(Args), GameClientPath]()
		{
			auto runner = IGameLiftCoreModule::Get().MakeRunner();
			bool bIsLaunched = runner->LaunchProcess(RunPath, Args);

			IsLaunchingGameClient = false;

			// Added delay for loading button visibility
			FPlatformProcess::Sleep(Menu::DeployCommon::kStartClientLoadingButtonDelay);

			Async(EAsyncExecution::TaskGraphMainThread, [this, bIsLaunched, GameClientPath]()
				{
					if (bIsLaunched)
					{
						UE_LOG(GameLiftPluginLog, Log, TEXT("Launched game client: %s"), *GameClientPath);
					}
					else
					{
						UE_LOG(GameLiftPluginLog, Error, TEXT("Failed to launch game client: %s. As an alternative, try launching the client manually."), *GameClientPath);
						Notifier::ShowFailedNotification(Menu::DeployCommon::kLaunchedGameClientFailureMessage);
					}

					if (LaunchBar.IsValid())
					{
						LaunchBar->ChangeStartClientButtonUIState(SLaunchBar::EStartButtonUIState::Start);
					}
				});
		});
}

#undef LOCTEXT_NAMESPACE