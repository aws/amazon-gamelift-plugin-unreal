// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "FGameLiftSettingsCustomization.h"

#include <PropertyHandle.h>
#include <DetailLayoutBuilder.h>
#include <DetailWidgetRow.h>
#include <IDetailPropertyRow.h>
#include <DetailCategoryBuilder.h>

#include "GameLiftPluginConstants.h"
#include "UGameLiftSettings.h"

#include "SMenu/SGameLiftSettingsAwsAccountMenu.h"
#include "SMenu/SGameLiftSettingsGameLiftMenu.h"
#include "SMenu/SGameLiftSettingsHelpMenu.h"

#define LOCTEXT_NAMESPACE "FGameLiftSettingsCustomization"

TSharedRef<IDetailCustomization> FGameLiftSettingsCustomization::MakeInstance()
{
	return MakeShareable(new FGameLiftSettingsCustomization);
}

void FGameLiftSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	SavedLayoutBuilder = &DetailLayout;

	BuildGameLiftSettingsPage(DetailLayout);
}

void FGameLiftSettingsCustomization::BuildGameLiftSettingsPage(IDetailLayoutBuilder& DetailLayout)
{
	// AWS User Profiles
	IDetailCategoryBuilder& AwsProfileCategory = DetailLayout.EditCategory(Settings::Category::kAwsProfileCategory,
		Settings::Category::kAwsProfileCategoryText);

	AwsProfileCategory.AddCustomRow(Settings::Category::kAwsProfileCategoryText, false)
		.WholeRowWidget
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom2x + SPadding::Bottom) // The account widget is also used in Anywhere and EC2 pages. This padding setting is needed in the settings page.
			[
				SNew(SGameLiftSettingsAwsAccountMenu)
			]
		];

	// Hide the properties as we are using custom widgets...
	DetailLayout.HideProperty(GET_MEMBER_NAME_CHECKED(UGameLiftSettings, ProfileName));
	DetailLayout.HideProperty(GET_MEMBER_NAME_CHECKED(UGameLiftSettings, AwsRegion));
	DetailLayout.HideProperty(GET_MEMBER_NAME_CHECKED(UGameLiftSettings, S3Bucket));
	DetailLayout.HideProperty(GET_MEMBER_NAME_CHECKED(UGameLiftSettings, BootstrapStatus));
	DetailLayout.HideProperty(GET_MEMBER_NAME_CHECKED(UGameLiftSettings, BootstrapError));

	// GameLift Overview
	IDetailCategoryBuilder& GameLiftCategory = DetailLayout.EditCategory(Settings::Category::kGameLiftOverviewCategory, 
		Settings::Category::kGameLiftOverviewCategoryText);

	GameLiftCategory.AddCustomRow(Settings::Category::kGameLiftOverviewCategoryText, false)
		.WholeRowWidget
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				SNew(SGameLiftSettingsGameLiftMenu)
			]
		];

	// Additional Resources
	IDetailCategoryBuilder& AdditionalResourcesCategory = DetailLayout.EditCategory(Settings::Category::kAdditionalResourcesCategory,
		Settings::Category::kAdditionalResourcesCategoryText);

	AdditionalResourcesCategory.AddCustomRow(Settings::Category::kAdditionalResourcesCategoryText, false)
		.WholeRowWidget
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(SPadding::Top_Bottom)
			[
				SNew(SGameLiftSettingsHelpMenu)
			]
		];
}

#undef LOCTEXT_NAMESPACE
