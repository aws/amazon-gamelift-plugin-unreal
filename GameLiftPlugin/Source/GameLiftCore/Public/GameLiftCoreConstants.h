// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"

namespace Menu
{
	namespace DeploymentServer
	{
		static const auto kSingleRegionFleet = NSLOCTEXT("SGameLiftDeploymentMenu", "SingleRegionFleet_Scenario", "Single-region fleet");
		static const auto kSpotFleets = NSLOCTEXT("SGameLiftDeploymentMenu", "SpotFleets_Scenario", "Spot fleet"); 
		static const auto kFlexMatch = NSLOCTEXT("SGameLiftDeploymentMenu", "FlexMath_Scenario", "FlexMatch fleet");
		static const auto kContainersSingleRegionFleet = NSLOCTEXT("SGameLiftDeploymentMenu", "ContainersSingleRegionFleet_Scenario", "Single-region Containers Fleet");
		static const auto kContainersFlexMatch = NSLOCTEXT("SGameLiftDeploymentMenu", "ContainersFlexMath_Scenario", "FlexMatch Containers Fleet");
		static const auto kCustom = NSLOCTEXT("SGameLiftDeploymentMenu", "Custom_Scenario", "Custom");

		static const auto kSingleRegionFleetTooltip = NSLOCTEXT("SGameLiftDeploymentMenu", "SingleRegionFleet_ToolTip",
			"Use this scenario to deploy a minimal managed EC2 fleet for your game server. This scenario also sets up player authentication for your game and creates a backend service for game clients to start and join game sessions.");
		
		static const auto kSpotFleetsTooltip = NSLOCTEXT("SGameLiftDeploymentMenu", "SpotFleets_ToolTip",
			"Forms matches by using Amazon GameLift queues and a custom matchmaker and configures three fleets.");

		static const auto kFlexMatchTooltip = NSLOCTEXT("SGameLiftDeploymentMenu", "FlexMath_ToolTip",
			"Use this scenario to deploy a fully configured set of managed EC2 fleets with matchmaking. This scenario also sets up a queue to manage game session placement across Spot and On-Demand fleets, handles player authentication and creates a backend service for game clients to request matchmaking and join matches.");

		static const auto kContainersSingleRegionFleetTooltip = NSLOCTEXT("SGameLiftDeploymentMenu", "ContainersSingleRegionFleet_ToolTip",
			"Creates a game backend service with a single Amazon GameLift Containers fleet.");

		static const auto kContainersFlexMatchTooltip = NSLOCTEXT("SGameLiftDeploymentMenu", "ContainersFlexMath_ToolTip",
			"Uses FlexMatch, a managed matchmaking service, to match game players together across Amazon GameLift Containers fleets.");

		static const auto kCustomTooltip = NSLOCTEXT("SGameLiftDeploymentMenu", "Custom_ToolTip",
			"This is a custom user scenario.");

		static const auto kSingleRegionFleetFolder = TEXT("scenario1_single_fleet");
		static const auto kSpotFleetsFolder = TEXT("scenario2_spot_fleets");
		static const auto kFlexMatchFolder = TEXT("scenario3_flexmatch");
		static const auto kContainersSingleRegionFleetFolder = TEXT("scenario3_containers_single_fleet");
		static const auto kContainersFlexMatchFolder = TEXT("scenario4_containers_flexmatch");
		static const auto kCurrentScenarioFolder = TEXT("scenario_current");		
		static const auto kCustomScenarioFolder = TEXT("scenario_custom");
	}
} // namespace Menu

namespace Bootstrap
{
	namespace Logs
	{
		static const auto kLogReceived = TEXT("Native log message: ");
		static const auto kReceiveBucketNameCallback = TEXT("AWSBootstrapProfile: Received a bucket name:");

		static const auto kBootstrapStarted = TEXT("AWSBootstrapProfile: Bootstrapping.........");
		static const auto kBootstrapCompleted = TEXT("AWSBootstrapProfile: Bootstrapped.");
		static const auto kBootstrapFailedCreateAccount = TEXT("AWSBootstrapProfile: Unable to create AWS credentials profile with an error: ");
		static const auto kBootstrapFailedBootstrap = TEXT("AWSBootstrapProfile:Unable to bootstrap account with an error: ");
		static const auto kBootstrapFailedAccountNotValid = TEXT("AWSBootstrapProfile: Account does not contain valid data.");
	}
} // namespace Bootstrap

namespace Deploy
{
	static const auto kMaxGameNameWithPrefixLength = 30;

	namespace Logs
	{
		static const auto kLogReceived = TEXT("Native log message:");
		static const auto kReceiveReplacementIdCallback = TEXT("AWSScenariosDeployer: Received a function replacement id:");
		static const auto kReceiveClientConfigPathCallback = TEXT("AWSScenariosDeployer: Received a client config path:");

		static const auto kRunAwsScenario = TEXT("AWSScenariosDeployer: Run scenario:");
		static const auto kRunCustomScenario = TEXT("AWSScenariosDeployer: Run custom scenario path:");

		static const auto kAccountInstanceIsNull = TEXT("AWSScenariosDeployer: Invalid account instance, bootstrap is required.");
		static const auto kCreateAndSetFunctionsReplacementIdFailed = TEXT("GameLiftAccountCreateAndSetFunctionsReplacementId failed with error:");
		static const auto kGetMainFunctionsReplacementIdFailed = TEXT("kGetMainFunctionsReplacementIdFailed failed with error:");
		static const auto kCreateLaunchPathParameterFailed = TEXT("CreateLaunchPathParameter failed with error:");
		static const auto kInvalidServerFilePath = TEXT("Game Server File Path has to be a subpath of Game Server Build Folder.");
		static const auto kSaveFeatureInstanceTemplatesFailed = TEXT("GameLiftAccountSaveFeatureInstanceTemplates failed with error:");
		static const auto kAccountUploadFunctionsFailed = TEXT("GameLiftAccountUploadFunctions failed with error:");
		static const auto kUploadGameServerFailed = TEXT("GameLiftAccountUploadGameServer failed with error:");
		static const auto kCreateOrUpdateMainStackFailed = TEXT("GameLiftAccountCreateOrUpdateMainStack failed with error:");
		static const auto kDeployApiGatewayStageFailed = TEXT("GameLiftAccountDeployApiGatewayStage failed with error:");
		static const auto kDeploymentStackStatusFailed = TEXT("Deployment stack status failed with error:");
		static const auto kDeploymentHasBeenStopped = TEXT("Deployment has been cancelled by user.");
		static const auto kDeploymentStackStatus = TEXT("Deployment stack status is:");

		static const auto kDeploymentStop = TEXT("Stop deployment...");
	}

	namespace Errors
	{
		static const auto kAccountIsInvalidText = NSLOCTEXT("SGameLiftDeploymentMenu", "AccountIsInvalidText", "This account is invalid. Please check your credentials.");
		static const auto kGameNameIsTooLongText = NSLOCTEXT("SGameLiftDeploymentMenu", "GameNameIsTooLongText", "Game name is too long. Game name must have 1-16 characters.");
		static const auto kNoStacksToStopDeployment = NSLOCTEXT("SGameLiftDeploymentMenu", "kNoStacksToStopDeployment", "Currently no active stacks are available.");
		static const auto kUnableToStopDeployment = NSLOCTEXT("SGameLiftDeploymentMenu", "kUnableToStopDeployment", "Currently it is not possible to stop deployment.");		
	}
} // namespace Deploy

namespace Account
{
	namespace Logs
	{
		static const auto kLogReceived = TEXT("Native log message: ");
		static const auto kUnableToBuildCredentials = TEXT("AwsAccountInstanceManager: Unable to build credentials.");
		static const auto kUnableToBuildAccountInfo = TEXT("AwsAccountInstanceManager: Unable to build account info.");
		static const auto kAccountIsNotCreated = TEXT("AwsAccountInstanceManager: Account is not created.");
		static const auto kAccountIsInvalid = TEXT("AwsAccountInstanceManager: Account is invalid.");
	}
} // namespace Account

namespace Credentials
{
	namespace Logs
	{
		static const auto kLogReceived = TEXT("Native log message: ");
		static const auto kUnableToGetAccountId = TEXT("AwsAccountCredentials: Unable to get account id with an error:");
	}
} // namespace Credentials

namespace Aws
{
	namespace Config
	{
		static const auto kUserPoolClientIdYamlName = "user_pool_client_id";
		static const auto kApiGatewayEndpointYamlName = "identity_api_gateway_base_url";
	}

	namespace Status
	{
		static const auto kStackUndeployed = "UNDEPLOYED";
		static const auto kStackUpdateComplete = "UPDATE_COMPLETE";
		static const auto kStackCreateComplete = "CREATE_COMPLETE";
	}
} // namespace Aws

namespace Process
{
	static const auto kWaitForProcMs = 5000;
} // namespace Process

namespace Core
{
	static const auto sGameLiftCoreName = TEXT("GameLiftCore");
	static const auto sGameLiftPluginName = TEXT("GameLiftPlugin");

	namespace Logs
	{
		static const auto kStartupModule = TEXT("FGameLiftCoreModule StartupModule");
		static const auto kShutdownModule = TEXT("FGameLiftCoreModule Shutting down");
		static const auto kDllLoaded = TEXT("DLL loaded");
	}
} // namespace Core

namespace Anywhere
{
	static const auto kCustomLocationPrefix = TEXT("custom-location-unreal");
	static const auto kAnywhereFleetDescription = TEXT("Deployed by the Amazon GameLift Plug-in for Unreal.");
	static const auto kAnywhereFleetTagKey = TEXT("CreatedBy");
	static const auto kAnywhereFleetTagValue = TEXT("AmazonGameLiftUnrealPlugin");
}
