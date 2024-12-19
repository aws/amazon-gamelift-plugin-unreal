// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "GameLiftPluginCommands.h"

#define LOCTEXT_NAMESPACE "FGameLiftPluginModule"

void FGameLiftPluginCommands::RegisterCommands()
{
	// Profile Setup section
	UI_COMMAND(OpenSettings, "AWS Access Credentials", "Set up your AWS Access Credentials", EUserInterfaceActionType::Button, FInputChord());

	// Hosting Solutions section
	UI_COMMAND(DeployAnywhere, "Anywhere", "Deploy the game with Amazon GameLift Anywhere", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(DeployManagedEC2, "Managed EC2", "Deploy the game with Amazon GameLift Managed EC2", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(DeployContainers, "Managed Containers", "Deploy the game with Amazon GameLift Managed Containers", EUserInterfaceActionType::Button, FInputChord());

	// Help section
	UI_COMMAND(OpenGameLiftDocumentation, "Documentation", "Open Amazon GameLift Documentation", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenAwsGameTechForum, "AWS GameTech Forum", "Open AWS GameTech Forum", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ReportIssues, "Report Issues", "Report issues you have found", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenServiceAPIReference, "Open Service API Reference", "Open Service API Reference", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenServerSDKReference, "Open Server SDK Reference", "Open Server SDK Reference", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
