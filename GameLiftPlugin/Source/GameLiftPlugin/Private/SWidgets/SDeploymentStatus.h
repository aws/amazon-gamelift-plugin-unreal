// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Input/Reply.h"
#include "Styling/SlateColor.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#include "Types/EDeploymentMessageState.h"

DECLARE_DELEGATE_RetVal_OneParam(EDeploymentMessageState, FOnUpdateDeploymentState, EDeploymentMessageState);

class SDeploymentStatus : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SDeploymentStatus) {}

	SLATE_EVENT(FOnUpdateDeploymentState, OnUpdateState)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	// SWidget interface
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	// End of Swidget interface

	void OnDeploy();
	void OnAbort();
	void OnFailure();
	void OnSucceeded();

	EDeploymentMessageState GetCurrentState() const;
	void SetState(EDeploymentMessageState NewState);

private:
	int32 GetSetupStateAsInt() const;
	
	void UpdateCache(EDeploymentMessageState);
	void UpdateCache();

private:
	EDeploymentMessageState CachedSetupState;
	FOnUpdateDeploymentState OnUpdateState;

	TSharedPtr<SWidget> LoadingWidget;
};

inline TSharedRef<SDeploymentStatus> AsSDeploymentStatusRef(TSharedPtr<SWidget> WidgetToCast)
{
	return StaticCastSharedRef<SDeploymentStatus>(WidgetToCast.ToSharedRef());
}

inline TSharedRef<SDeploymentStatus> AsSDeploymentStatusRef(TSharedRef<SWidget> WidgetToCast)
{
	return StaticCastSharedRef<SDeploymentStatus>(WidgetToCast);
}
