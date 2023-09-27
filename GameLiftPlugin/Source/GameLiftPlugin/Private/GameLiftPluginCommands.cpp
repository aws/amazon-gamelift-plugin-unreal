// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "GameLiftPluginCommands.h"

#define LOCTEXT_NAMESPACE "FGameLiftPluginModule"

void FGameLiftPluginCommands::RegisterCommands()
{
	// Deployment section
	UI_COMMAND(OpenSettings, "Set AWS User Profiles", "Set AWS User Profiles", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(DeployAnywhere, "Host with Anywhere", "Deploy the game with Amazon GameLift Anywhere", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(DeployManagedEC2, "Host with Managed EC2", "Deploy the game with Amazon GameLift Managed EC2", EUserInterfaceActionType::Button, FInputChord());

	// Help section
	UI_COMMAND(OpenGameLiftDocumentation, "Documentation", "Open Amazon GameLift Documentation", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenAwsGameTechForum, "AWS GameTech Forum", "Open AWS GameTech Forum", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ReportIssues, "Report Issues", "Report issues you have found", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenServiceAPIReference, "Open Service API Reference", "Open Service API Reference", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenServerSDKReference, "Open Server SDK Reference", "Open Server SDK Reference", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
