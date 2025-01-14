// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "Styling/SlateColor.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#include "Types/EBootstrapMessageState.h"

class SBootstrapStatus;

// Display the profile bootstraping information.
class SBootstrapStatus : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SBootstrapStatus) {}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	void OnNeedBootstrap();
	void OnBootstrap();
	void OnFailure();
	void OnSucceeded();

	void UpdateState(int NewState);

	static TSharedRef<SBootstrapStatus> CastToSharedRef(TSharedPtr<SWidget> WidgetToCast)
	{
		return StaticCastSharedRef<SBootstrapStatus>(WidgetToCast.ToSharedRef());
	}

private:
	int32 GetSetupStateAsInt() const;

private:
	EBootstrapMessageState BootstrapState;
};
