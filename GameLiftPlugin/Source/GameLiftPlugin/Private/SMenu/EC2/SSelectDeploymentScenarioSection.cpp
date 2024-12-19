// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SSelectDeploymentScenarioSection.h"

#include "Settings/UGameLiftDeploymentStatus.h"
#include "SWidgets/SDeploymentFields.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/STextSeparator.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"
#include "IGameLiftCoreModule.h"
#include "Types/EManagedEC2DeploymentScenario.h"
#include "Types/EDeploymentMessageState.h"

#include "SGameLiftDeployManagedEC2Menu.h"
#include "SDeployScenarioSection.h"

#define LOCTEXT_NAMESPACE "SSelectDeploymentScenarioSection"

void SSelectDeploymentScenarioSection::Construct(const FArguments& InArgs)
{
	DeploymentFields = InArgs._SetDeploymentFields;
	BuildScenarioValues(IAWSScenariosCategory::ManagedEC2);

	SSectionStep::Construct(
		SSectionStep::FArguments()
		.HeaderTitle(Menu::DeployManagedEC2::kSelectScenarioHeader)
		.HeaderDescription(Menu::DeployManagedEC2::kSelectScenarioDescription)
		.BodyContent()
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Left)
						[
							SNew(SOnlineHyperlink)
								.Text(Menu::DeployManagedEC2::kGameLiftChooseLocationLinkText)
								.Link(Url::kGameLiftChooseLocationsUrl)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Center)
						[
							SNew(STextSeparator).Separator(TEXT("|"))
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Left)
						[
							SNew(SOnlineHyperlink)
								.Text(Menu::DeployManagedEC2::kGameLiftPricingPlanLinkText)
								.Link(Url::kGameLiftPricingPlanUrl)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Center)
						[
							SNew(STextSeparator).Separator(TEXT("|"))
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Left)
						[
							SNew(SOnlineHyperlink)
								.Text(Settings::AwsAccount::kAWSFreeTierLinkText)
								.Link(Settings::AwsAccount::kAWSFreeTierLinkUrl)
						]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(SPadding::Top3x)
				[
					SAssignNew(SectionSwitcher, SWidgetSwitcher)
						+ SWidgetSwitcher::Slot()
						[
							SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									CreateDeploymentScenarioChoice()
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								.HAlign(HAlign_Left)
								.Padding(SPadding::Top)
								[
									CreateSubmissionButton()
								]
						]
						+ SWidgetSwitcher::Slot()
						[
							SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									CreateScenarioSubmittedDetails()
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								.HAlign(HAlign_Left)
								[
									CreateModifyButton()
								]
						]
				]
		]
	);

	SDeployScenarioSection::OnEC2DeploymentProgressChangedMultiDelegate.AddSP(this, &SSelectDeploymentScenarioSection::UpdateUIBasedOnCurrentState);

	SetDefaultValues();
	UpdateUIBasedOnCurrentState();
}

FReply SSelectDeploymentScenarioSection::OnSubmissionButtonClicked()
{
	CompleteSection();
	StartNextSection();

	return FReply::Handled();
}

void SSelectDeploymentScenarioSection::UpdateUIBasedOnCurrentState()
{
	// TODO: Add state for each section completion
	UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();
	EDeploymentMessageState State = EDeploymentMessageStateFromString(DeploySettings->Status.ToString());

	ModifyButton->SetEnabled(State != EDeploymentMessageState::InProgressMessage);

	if (State != EDeploymentMessageState::NoDeploymentMessage)
	{
		CompleteSection();
	}
	else
	{
		ResetAndCollapseSection();
	}
}

void SSelectDeploymentScenarioSection::CompleteSection()
{
	auto DeploymentInfo = AsSDeploymentFieldsRef(DeploymentFields);
	DeploymentInfo->SetDeploymentScenario(ScenarioNames[CurrentScenarioSelected]);
	SectionSwitcher->SetActiveWidgetIndex((int32)ESectionUIState::Complete);
	SetProgressBarState(SProgressBar::EProgressBarUIState::ProgressComplete);
}

void SSelectDeploymentScenarioSection::StartSection()
{
	SectionSwitcher->SetActiveWidgetIndex((int32)ESectionUIState::InComplete);
}

void SSelectDeploymentScenarioSection::BuildScenarioValues(IAWSScenariosCategory Category)
{
	ScenarioNames.Reset();
	ScenarioDescriptions.Reset();

	auto& Deployer = IGameLiftCoreModule::Get().GetScenarioDeployer();
	TArray<FText> Scenarios = Deployer.GetScenarios(Category);

	for (int i = 0; i < Scenarios.Num(); i++)
	{
		ScenarioNames.Add(Scenarios[i]);
		ScenarioDescriptions.Add(Deployer.GetToolTip(Scenarios[i], IAWSScenariosCategory::ManagedEC2));
	}
}

void SSelectDeploymentScenarioSection::SetDefaultValues()
{
	UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();

	int previousScenarioSelected = ScenarioNames.FindLastByPredicate([&](const FText& name)
		{
			return name.EqualTo(DeploySettings->Scenario);
		});
	if (previousScenarioSelected != INDEX_NONE)
	{
		CurrentScenarioSelected = previousScenarioSelected;
	}
}

TSharedRef<SWidget> SSelectDeploymentScenarioSection::CreateModifyButton()
{
	return SAssignNew(ModifyButton, SButton)
		.Text(Menu::DeployManagedEC2::kModifyScenarioButtonText)
		.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
		.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
		.OnClicked_Raw(this, &SSelectDeploymentScenarioSection::OnModifyButtonClicked);
}

TSharedRef<SWidget> SSelectDeploymentScenarioSection::CreateSubmissionButton()
{
	return SAssignNew(SubmissionButton, SButton)
		.Text(Menu::DeployManagedEC2::kConfigureParametersButtonText)
		.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kSuccessButtonStyleName)
		.OnClicked_Raw(this, &SSelectDeploymentScenarioSection::OnSubmissionButtonClicked);
}

FReply SSelectDeploymentScenarioSection::OnModifyButtonClicked()
{
	SectionSwitcher->SetActiveWidgetIndex((int32)ESectionUIState::InComplete);

	ResetAndCollapseNextSections();
	
	return FReply::Handled();
}

TSharedRef<SWidget> SSelectDeploymentScenarioSection::CreateScenarioSubmittedDetails()
{
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);
	
	VerticalBox->AddSlot()
		.AutoHeight()
		[
			SNew(SNamedRow)
				.NameText(Menu::DeployManagedEC2::kFleetTypeTitle)
				.RowWidget(
					SNew(STextBlock).Text_Lambda([&]
						{
							return ScenarioNames[CurrentScenarioSelected];
						})
				)
		];

	VerticalBox->AddSlot()
		.AutoHeight()
		[
			SNew(SNamedRow)
				.RowWidget(
					SNew(STextBlock)
					.AutoWrapText(true)
					.Text_Lambda([&]
						{
							return ScenarioDescriptions[CurrentScenarioSelected];
						})
				)
		];

	return VerticalBox;

}

TSharedRef<SWidget> SSelectDeploymentScenarioSection::CreateDeploymentScenarioChoice()
{
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Bottom)
		[
			SNew(SCheckBox)
				.Style(FCoreStyle::Get(), "RadioButton")
				.IsChecked(this, &SSelectDeploymentScenarioSection::IsRadioChecked, EDeploymentScenarioFleetChoice::SingleRegion)
				.OnCheckStateChanged(this, &SSelectDeploymentScenarioSection::OnRadioChanged, EDeploymentScenarioFleetChoice::SingleRegion)
				.Content()
				[
					SNew(STextBlock).Text(ScenarioNames[(int)EDeploymentScenarioFleetChoice::SingleRegion])
				]
		];

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Bottom2x)
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(5)
				.HAlign(HAlign_Left)
				[
					SNew(SBox)
						.Padding(SPadding::Left4x)
						.WidthOverride(Style::kMessageTextBoxWidth)
						[
							SNew(STextBlock)
								.Text(ScenarioDescriptions[(int)EDeploymentScenarioFleetChoice::SingleRegion])
								.AutoWrapText(true)
						]
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1)
				.HAlign(HAlign_Left)
				.Padding(SPadding::Left2x)
				[
					SNew(SOnlineHyperlink)
						.Text(Menu::DeployManagedEC2::kDeploymentScenarioLearnMoreLinkText)
						.Link(Url::kSingleRegionLearnMoreUrl)
				]
		];

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Bottom)
		[
			SNew(SCheckBox)
				.Style(FCoreStyle::Get(), "RadioButton")
				.IsChecked(this, &SSelectDeploymentScenarioSection::IsRadioChecked, EDeploymentScenarioFleetChoice::FlexMatch)
				.OnCheckStateChanged(this, &SSelectDeploymentScenarioSection::OnRadioChanged, EDeploymentScenarioFleetChoice::FlexMatch)
				.Content()
				[
					SNew(STextBlock).Text(ScenarioNames[(int)EDeploymentScenarioFleetChoice::FlexMatch])
				]
		];

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(SPadding::Bottom2x)
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(5)
				.HAlign(HAlign_Left)
				[
					SNew(SBox)
						.Padding(SPadding::Left4x)
						.WidthOverride(Style::kMessageTextBoxWidth)
						[
							SNew(STextBlock)
								.Text(ScenarioDescriptions[(int)EDeploymentScenarioFleetChoice::FlexMatch])
								.AutoWrapText(true)
						]
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1)
				.HAlign(HAlign_Left)
				.Padding(SPadding::Left2x)
				[
					SNew(SOnlineHyperlink)
						.Text(Menu::DeployManagedEC2::kDeploymentScenarioLearnMoreLinkText)
						.Link(Url::kFlexMatchLearnMoreUrl)
				]
		];

	return VerticalBox;
}

ECheckBoxState SSelectDeploymentScenarioSection::IsRadioChecked(EDeploymentScenarioFleetChoice RadioButtonChoice) const
{
	return (CurrentScenarioSelected == (int)RadioButtonChoice) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SSelectDeploymentScenarioSection::OnRadioChanged(ECheckBoxState NewRadioState, EDeploymentScenarioFleetChoice RadioButtonChoice)
{
	if (NewRadioState == ECheckBoxState::Checked)
	{
		CurrentScenarioSelected = (int)RadioButtonChoice;
		auto DeploymentInfo = AsSDeploymentFieldsRef(DeploymentFields);
		DeploymentInfo->SetDeploymentScenario(ScenarioNames[CurrentScenarioSelected]);
	}
}

#undef LOCTEXT_NAMESPACE