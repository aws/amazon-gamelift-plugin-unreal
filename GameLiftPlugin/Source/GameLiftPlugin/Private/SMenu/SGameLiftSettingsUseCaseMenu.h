// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

// Display games that use GameLift.
class SGameLiftSettingsUseCaseMenu : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SGameLiftSettingsUseCaseMenu) {}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	void LoadImages();

	TSharedRef<SWidget> MakeUseCaseWidget(const FText& GameName, const FText& DeveloperName, const FString& BlogLink, const FSlateBrush* ImageBrush, FVector2D ImageSize) const;

	TSharedPtr<FSlateBrush> GameImageBrush_1;
	TSharedPtr<FSlateBrush> GameImageBrush_2;
	TSharedPtr<FSlateBrush> GameImageBrush_3;
};
