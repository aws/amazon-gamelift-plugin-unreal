// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

#include "Types/FTextIntPair.h"

class SWindow;
class SSetProfileSection;
class SIntegrateGameSection;
class SConnectAnywhereFleetMenu;
class SAnywhereRegisterComputeMenu;
class SAnywhereGenerateAuthTokenMenu;
class SPathInput;

class SGameLiftDeployAnywhereMenu : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SGameLiftDeployAnywhereMenu) { }
	
	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SWidget> CreateConnectToFleetSection();
	TSharedRef<SWidget> CreateRegisterComputeSection();
	TSharedRef<SWidget> CreateAuthTokenSection();
	TSharedRef<SWidget> CreateGameServerAndClientSection();

	bool CanLaunchServer() const;
	bool CanLaunchClient() const;

	void OnFleetChanged();
	void OnComputeChanged();

	FReply OnLaunchServerButtonClicked();
	FReply OnLaunchClientButtonClicked();

private:
	TSharedPtr<SSetProfileSection> SetProfileSection;
	TSharedPtr<SIntegrateGameSection> IntegrateGameSection;
	TSharedPtr<SConnectAnywhereFleetMenu> AnywhereConnectFleetSection;
	TSharedPtr<SAnywhereRegisterComputeMenu> AnywhereRegisterComputeSection;
	TSharedPtr<SAnywhereGenerateAuthTokenMenu> AnywhereGenerateAuthTokenSection;

	TWeakPtr<SWindow> ContextWindow;

	bool IsLaunchingGameServer = false;
	bool IsLaunchingGameClient = false;
};
