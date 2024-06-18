// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SContainerDeploymentFields.h"

#include <Widgets/SBoxPanel.h>
#include <Widgets/Layout/SBorder.h>

#include "SWidgets/SPathInput.h"
#include "SWidgets/SNamedRow.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

namespace Internal
{
	TSharedPtr<SPathInput> MakeGameName()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployContainers::kGameNameText)
			.PathHint(Menu::DeployContainers::kGameNameHint)
			.ButtonVisibility(EVisibility::Collapsed);
	}
	
	TSharedPtr<SPathInput> MakeFleetName()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployContainers::kFleetNameText)
			.PathHint(Menu::DeployContainers::kFleetNameHint)
			.ButtonVisibility(EVisibility::Collapsed);
	}

	TSharedPtr<SPathInput> MakeContainerImageURI()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployContainers::kContainerImageURIText)
			.PathHint(Menu::DeployContainers::kContainerImageURIHint)
			.ButtonVisibility(EVisibility::Collapsed);
	}

	TSharedPtr<SPathInput> MakeIntraContainerLaunchPath()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployContainers::kIntraContainerLaunchPathText)
			.PathHint(Menu::DeployContainers::kIntraContainerLaunchPathHint)
			.ButtonVisibility(EVisibility::Collapsed);
	}

	TSharedPtr<SPathInput> MakeContainerExtraServerResourcesPath()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployManagedEC2::kExtraServerResourcesPathTitle)
			.IsFileSelection(false)
			.ToolTipText(Menu::DeployManagedEC2::kExtraServerResourcesPathTooltip);
	}

	TSharedPtr<SPathInput> MakeContainerOutConfigFilePath()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployManagedEC2::kOutConfigFilePathTitle)
			.PathHint(Menu::DeployManagedEC2::kOutConfigFilePathHint)
			.IsFileSelection(false);
	}
} // namespace Internal

#define LOCTEXT_NAMESPACE "SContainerDeploymentFields"

void SContainerDeploymentFields::Construct(const FArguments& InArgs)
{
	GameNameInput = Internal::MakeGameName();
	FleetNameInput = Internal::MakeFleetName();
	ContainerImageURIInput = Internal::MakeContainerImageURI();
	IntraContainerLaunchPathInput = Internal::MakeIntraContainerLaunchPath();
	ExtraServerResourcesPathInput = Internal::MakeContainerExtraServerResourcesPath();
	OutConfigFilePathInput = Internal::MakeContainerOutConfigFilePath();

	TSharedPtr<SWidget> GameNameInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployContainers::kGameNameTitle)
		.RowWidget(GameNameInput);

	TSharedPtr<SWidget> GameNameInstructionsRow = SNew(SNamedRow)
		.SecondaryColumnLeftPadding(true)
		.RowWidget(
			SNew(STextBlock)
			.Text(Menu::DeployContainers::kGameNameInstructionText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote)
			.AutoWrapText(true)
			);

	TSharedPtr<SWidget> FleetNameInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployContainers::kFleetNameTitle)
		.RowWidget(FleetNameInput);
	
	TSharedPtr<SWidget> ContainerImageURIInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployContainers::kContainerImageURITitle)
		.RowWidget(ContainerImageURIInput);
	
	TSharedPtr<SWidget> IntraContainerLaunchPathInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployContainers::kIntraContainerLaunchPathTitle)
		.RowWidget(IntraContainerLaunchPathInput);

	TSharedPtr<SWidget> ExtraServerResourcesPathInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployManagedEC2::kExtraServerResourcesPathTitle)
		.RowWidget(ExtraServerResourcesPathInput);

	// Currently, this field does not work, so we hide it from users.
	ExtraServerResourcesPathInputRow->SetVisibility(EVisibility::Collapsed);

	TSharedPtr<SWidget> OutConfigFilePathInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployManagedEC2::kOutConfigFilePathTitle)
		.NameTooltipText(Menu::DeployManagedEC2::kOutConfigFilePathTooltip)
		.RowWidget(OutConfigFilePathInput);

	TSharedPtr<SWidget> FullWidget =
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()
		[
			GameNameInputRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight()
		[
			GameNameInstructionsRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight()
		[
			FleetNameInputRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			ContainerImageURIInputRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			IntraContainerLaunchPathInputRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			ExtraServerResourcesPathInputRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(SPadding::Top)
		[
			OutConfigFilePathInputRow.ToSharedRef()
		];

	ChildSlot
	[
		SNew(SBox)
		[
			FullWidget.ToSharedRef()
		]
	];
}

void SContainerDeploymentFields::SetGameName(const FText& Name)
{
	GameNameInput->SetSelectedPath(Name);
}

void SContainerDeploymentFields::SetFleetName(const FText& Name)
{
	FleetNameInput->SetSelectedPath(Name);
}

void SContainerDeploymentFields::SetContainerImageURI(const FText& Path)
{
	ContainerImageURIInput->SetSelectedPath(Path);
}

void SContainerDeploymentFields::SetIntraContainerLaunchPath(const FText& Path)
{
	IntraContainerLaunchPathInput->SetSelectedPath(Path);
}

void SContainerDeploymentFields::SetExtraServerResourcesPath(const FText& Path)
{
	ExtraServerResourcesPathInput->SetSelectedPath(Path);
}

void SContainerDeploymentFields::SetOutConfigFilePath(const FText& Path)
{
	OutConfigFilePathInput->SetSelectedPath(Path);
}

const FText& SContainerDeploymentFields::GetGameName() const
{
	return GameNameInput->GetSelectedPathRef();
}

const FText& SContainerDeploymentFields::GetFleetName() const
{
	return FleetNameInput->GetSelectedPathRef();
}

const FText& SContainerDeploymentFields::GetContainerImageURI() const
{
	return ContainerImageURIInput->GetSelectedPathRef();
}

const FText& SContainerDeploymentFields::GetIntraContainerLaunchPath() const
{
	return IntraContainerLaunchPathInput->GetSelectedPathRef();
}

const FText& SContainerDeploymentFields::GetExtraServerResourcesPath() const
{
	return ExtraServerResourcesPathInput->GetSelectedPathRef();
}

const FText& SContainerDeploymentFields::GetOutConfigFilePath() const
{
	return OutConfigFilePathInput->GetSelectedPathRef();
}

#undef LOCTEXT_NAMESPACE
