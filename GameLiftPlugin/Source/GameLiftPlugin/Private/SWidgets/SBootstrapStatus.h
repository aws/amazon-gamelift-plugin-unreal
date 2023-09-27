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

DECLARE_DELEGATE_RetVal_OneParam(EBootstrapMessageState, FOnUpdateBootstrapState, EBootstrapMessageState);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBootstrapStatusChanged, const SBootstrapStatus* /* Sender */);

// Display the profile bootstraping information.
class SBootstrapStatus : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SBootstrapStatus) {}

	SLATE_EVENT(FOnUpdateBootstrapState, OnUpdateState)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	void OnNeedBootstrap();
	void OnBootstrap();
	void OnFailure(const FText& ErrorMessage);
	void OnSucceeded(const FString& BucketName);
	void OnSucceeded();

	// Callback that handles bootstrap status changes from another instance
	void OnBootstrapStatusChanged(const SBootstrapStatus* sender);

	void UpdateState(EBootstrapMessageState);

	static TSharedRef<SBootstrapStatus> CastToSharedRef(TSharedPtr<SWidget> WidgetToCast)
	{
		return StaticCastSharedRef<SBootstrapStatus>(WidgetToCast.ToSharedRef());
	}

	static FOnBootstrapStatusChanged OnBootstrapStatusChangedMultiDelegate;

private:
	int32 GetSetupStateAsInt() const;
	
	void UpdateCache();

private:
	EBootstrapMessageState CachedSetupState;
	FOnUpdateBootstrapState OnUpdateState;
};
