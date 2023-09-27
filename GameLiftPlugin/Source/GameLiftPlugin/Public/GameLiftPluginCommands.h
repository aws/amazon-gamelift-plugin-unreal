// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GameLiftPluginStyle.h"

class FGameLiftPluginCommands : public TCommands<FGameLiftPluginCommands>
{
public:

	FGameLiftPluginCommands()
		: TCommands<FGameLiftPluginCommands>(TEXT("GameLiftPlugin"), NSLOCTEXT("Contexts", "GameLiftPlugin", "GameLiftPlugin Plugin"), NAME_None, FGameLiftPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenSettings;
	TSharedPtr<FUICommandInfo> DeployAnywhere;
	TSharedPtr<FUICommandInfo> DeployManagedEC2;

	TSharedPtr<FUICommandInfo> OpenGameLiftDocumentation;
	TSharedPtr<FUICommandInfo> OpenAwsGameTechForum;
	TSharedPtr<FUICommandInfo> ReportIssues;
	TSharedPtr<FUICommandInfo> OpenServiceAPIReference;
	TSharedPtr<FUICommandInfo> OpenServerSDKReference;
};
