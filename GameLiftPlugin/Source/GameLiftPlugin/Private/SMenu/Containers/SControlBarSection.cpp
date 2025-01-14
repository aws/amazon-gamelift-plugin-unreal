// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SControlBarSection.h"
#include "SResetDeploymentModal.h"
#include "SGameLiftDeployContainersMenu.h"

#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SSetupMessage.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

#include "Settings/UGameLiftContainersStatus.h"
#include "Settings/UGameLiftSettings.h"

#include "Types/EContainersDeploymentScenario.h"
#include "Types/EBootstrapMessageState.h"
#include "Types/EDeploymentMessageState.h"

#include "Utils/Misc.h"
#include "Utils/Notifier.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftCoreConstants.h"
#include "IGameLiftCoreModule.h"

#include <GenericPlatform/GenericPlatformMisc.h>

#define LOCTEXT_NAMESPACE "SControlBarSection"

FNewDeployment SControlBarSection::OnNewDeploymentMultiDelegate;

void SControlBarSection::Construct(const FArguments& InArgs)
{
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	bool isDockerInstalled = FPlatformMisc::OsExecute(TEXT("open"), TEXT("docker"), TEXT("-v"));

	if (!isDockerInstalled)
	{
		VerticalBox->AddSlot()
			.AutoHeight()
			[
				SNew(SBox)
					.Padding(SPadding::Bottom3x)
					.Visibility_Lambda([&]
						{
							UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
							bool IsVisible = IsAccountBootstrapped()
								&& (ContainersStatus->ContainerFleetDeploymentStatus == (int)EContainerFleetDeploymentStatus::DeploymentNotStart)
								&& (ContainersStatus->DeploymentScenario != (int)EContainersDeploymentScenario::HaveContainerImageInEcr);

							return IsVisible ? EVisibility::Visible : EVisibility::Collapsed;
						})
					[
						CreateDockerInstallWarningMessage()
					]
			];
	}

	VerticalBox->AddSlot()
		.AutoHeight()
		[
			SNew(SBox)
				.Padding(SPadding::Bottom3x)
				.Visibility_Lambda([&]()
					{
						UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
						return (IsAccountBootstrapped() && ContainersStatus->ContainerFleetDeploymentStatus == (int)EContainerFleetDeploymentStatus::DeploymentNotStart) ? EVisibility::Visible : EVisibility::Collapsed;
					})
				[
					CreateDeploymentTimeNotificationBar()
				]
		];

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		.HAlign(HAlign_Right)
		[
			CreateDeploymentButtonsRow()
		];

	ChildSlot
		[
			VerticalBox
		];
}

bool SControlBarSection::IsContainerDeploymentStatusActive()
{
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	return EDeploymentMessageStateFromString(ContainersStatus->Status.ToString()) == EDeploymentMessageState::ActiveMessage;
}


TSharedRef<SWidget> SControlBarSection::CreateDockerInstallWarningMessage()
{
	TSharedPtr<SVerticalBox> RowWidget = SNew(SVerticalBox);
	RowWidget->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Bottom2x)
		[
			SNew(STextBlock)
				.Text(Menu::DeployContainers::kMissingDockerWarningTitle)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kSubtitleStyleName)
				.AutoWrapText(true)
		];

	RowWidget->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Bottom2x)
		[
			SNew(STextBlock)
				.Text(Menu::DeployContainers::kMissingDockerWarningDescription)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
				.AutoWrapText(true)
		];

	RowWidget->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Bottom)
		[
			SNew(SOnlineHyperlink)
				.Text(Menu::DeployContainers::kInstallDockerText)
				.Link(Url::kInstallDockerUrl)
		];

	return SAssignNew(DeploymentTimeNotification, SSetupMessage)
		.WarningRowWidget(RowWidget)
		.IconVAlignTop(true);
}

TSharedRef<SWidget> SControlBarSection::CreateDeploymentTimeNotificationBar()
{
	TSharedPtr<SVerticalBox> RowWidget = SNew(SVerticalBox);
	RowWidget->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Bottom2x)
		[
			SNew(STextBlock)
				.Text(Menu::DeployContainers::kDeploymentTimeNotification)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
				.AutoWrapText(true)
		];

	RowWidget->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Bottom)
		[
			SNew(SOnlineHyperlink)
				.Text(Settings::AwsAccount::kAWSFreeTierLinkText)
				.Link(Settings::AwsAccount::kAWSFreeTierLinkUrl)
		];

	return SAssignNew(DeploymentTimeNotification, SSetupMessage)
		.InfoRowWidget(RowWidget)
		.InfoButtonStyle(Style::Button::kCloseButtonStyleName)
		.OnButtonClicked_Lambda([&]
			{
				DeploymentTimeNotification->SetVisibility(EVisibility::Collapsed);
			})
		.SetState(ESetupMessageState::InfoMessage);
}

TSharedRef<SWidget> SControlBarSection::CreateDeploymentButtonsRow()
{
	return SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Right)
		.Padding(SPadding::Right2x)
		[
			CreateAWSConsoleButton()
		]

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Right)
		[
			CreateDeploymentButtonSwitcher()
		];
}

TSharedRef<SWidget> SControlBarSection::CreateAWSConsoleButton()
{
	return SNew(SButton)
		.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
		.OnClicked_Lambda([]
			{
				UGameLiftSettings* Settings = GetMutableDefault<UGameLiftSettings>();
				FPlatformProcess::LaunchURL(*FString::Format(Url::kAWSConsoleUrlContainerFleetFormat, { Settings->AwsRegion.ToString()}), nullptr, nullptr);
				return FReply::Handled();
			})
		.Content()
		[
			SNew(SBox)
				.HeightOverride(OverrideButtonHeight)
				.HAlign(HAlign_Center)
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
								.Text(Menu::DeployContainers::kAWSConsoleButtonText)
								.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(SPadding::Left)
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						[
							SNew(SBox)
								.WidthOverride(Style::kLinkIconSize)
								.HeightOverride(Style::kLinkIconSize)
								[
									SNew(SImage)
										.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kExternalLinkIconName))
#if(ENGINE_MAJOR_VERSION == 4)
										.ColorAndOpacity(FColor::Black)
#endif
								]
						]
				]
		];
}

TSharedRef<SWidget> SControlBarSection::CreateDeploymentButtonSwitcher()
{
	return SNew(SWidgetSwitcher)
		.WidgetIndex_Lambda([&]
			{
				UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
				return ContainersStatus->ContainerFleetDeploymentStatus;
			})
		+ SWidgetSwitcher::Slot()
		[
			SNew(SBox)
				.HeightOverride(OverrideButtonHeight)
				.HAlign(HAlign_Center)
				[
					SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(Menu::DeployContainers::kDeployContainerFleetButtonText)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
						.IsEnabled_Raw(this, &SControlBarSection::IsAccountBootstrapped)
						.ToolTipText_Lambda([&]()
							{
								if (!IsAccountBootstrapped())
								{
									return Menu::DeployCommon::kDeploymentDisabledNeedBootstrapTooltip;
								}

								return Menu::DeployCommon::kDeploymentEnabledTooltip;
							})
						.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
						.OnClicked_Lambda([this]
							{
								UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
								ContainersStatus->ContainerFleetDeploymentStatus = (int)EContainerFleetDeploymentStatus::DeploymentInProgress;
								ContainersStatus->SaveConfig();
								OnNewDeploymentMultiDelegate.Broadcast();
								return FReply::Handled();
							})
				]
		]
		+ SWidgetSwitcher::Slot()
		[
			SNew(SBox)
				.HeightOverride(OverrideButtonHeight)
				.HAlign(HAlign_Center)
				[
					SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(Menu::DeployContainers::kResetDeploymentButtonText)
						.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
						.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kErrorButtonStyleName)
						.OnClicked_Lambda([this]
							{
								DisplayResetModal();
								return FReply::Handled();
							})
				]
		]
		+ SWidgetSwitcher::Slot()
		[
			SNew(SButton)
				.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
				.OnClicked_Lambda([]
					{
						UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
						ContainersStatus->ContainerFleetDeploymentStatus = (int)EContainerFleetDeploymentStatus::DeploymentNotStart;
						ContainersStatus->SaveConfig();
						return FReply::Handled();
					})
				.Content()
				[
					SNew(SBox)
						.HeightOverride(OverrideButtonHeight)
						.HAlign(HAlign_Center)
						[
							SNew(SHorizontalBox)
								+ SHorizontalBox::Slot()
								.AutoWidth()
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(SBox)
										.WidthOverride(Style::kResetIconSize)
										.HeightOverride(Style::kResetIconSize)
										[
											SNew(SImage)
												.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kResetIconName))
#if(ENGINE_MAJOR_VERSION == 4)
												.ColorAndOpacity(FColor::Black)
#endif
										]
								]

								+ SHorizontalBox::Slot()
								.AutoWidth()
								.Padding(SPadding::Left)
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
										.Text(Menu::DeployContainers::kResetDeploymentButtonText)
										.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
								]
						]
				]
		];
}

bool SControlBarSection::IsAccountBootstrapped() const
{
	auto* Settings = GetMutableDefault<UGameLiftSettings>();
	return EBootstrapMessageStateFromInt(Settings->BootstrapStatus) == EBootstrapMessageState::ActiveMessage;
}

void SControlBarSection::DisplayResetModal()
{
	UGameLiftContainersStatus* ContainersStatus = GetMutableDefault<UGameLiftContainersStatus>();
	TSharedPtr<SWindow> TopLevelWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
	
	if (TopLevelWindow.IsValid() && !ContainersStatus->IsResetContainerFleetModalOpen) {
		TSharedRef<SWindow> ModalWindow = SNew(SWindow)
			.IsPopupWindow(true)
			.SupportsMinimize(false)
			.SupportsMaximize(false)
			.bDragAnywhere(true)
			.SizingRule(ESizingRule::Autosized);

		TSharedRef<SResetDeploymentModal> ModalContent = SNew(SResetDeploymentModal)
			.OwnerWindow(ModalWindow);

		ModalWindow->SetContent(ModalContent);
		ModalWindow->SetAsModalWindow();

		FSlateApplication::Get().AddWindowAsNativeChild(ModalWindow, TopLevelWindow.ToSharedRef(), true);

		ContainersStatus->IsResetContainerFleetModalOpen = true;
		ContainersStatus->SaveConfig();

		SGameLiftDeployContainersMenu::OnModalOpened.ExecuteIfBound();
	}
}

#undef LOCTEXT_NAMESPACE