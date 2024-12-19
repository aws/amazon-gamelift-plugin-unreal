// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

DECLARE_DELEGATE(FOnProfileNumberUpdated);

class IDetailLayoutBuilder;

class FGameLiftSettingsCustomization : public IDetailCustomization
{
public:
	// Makes a new instance of this detail layout class for a specific detail view requesting it
	static TSharedRef<IDetailCustomization> MakeInstance();

	void RefreshDetails();
	static FOnProfileNumberUpdated OnProfileNumberUpdated;

	// IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;
	// End of IDetailCustomization interface

private:
	FGameLiftSettingsCustomization() = default;

	void BuildGameLiftSettingsPage(IDetailLayoutBuilder& DetailLayout);

private:
	IDetailLayoutBuilder* SavedLayoutBuilder;
};
