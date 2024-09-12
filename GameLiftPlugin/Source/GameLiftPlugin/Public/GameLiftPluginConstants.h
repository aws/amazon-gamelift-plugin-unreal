// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"

namespace Plugin
{
	static const auto sGameLiftPluginName = TEXT("GameLiftPlugin");
	static const FName GameLiftPluginTabName("GameLiftPlugin");

	static const auto kGameLiftProductName = NSLOCTEXT("Plugin", "GameLiftProductName", "Amazon GameLift");
} // namespace Plugin

namespace Settings
{
	static const auto kSettingsSectionName = "GameLiftPlugin";
	static const auto kSettingsSectionTooltip = NSLOCTEXT("Settings", "SectionTooltip", "Edit AWS User Profiles");

	static const auto kRichTextBlockNoteText = NSLOCTEXT("FGameLiftSettingsCustomization", "kRichTextBlockNoteText", "Note");

	namespace Category
	{
		static const auto kAwsProfileCategory = "AWS User Profiles";
		static const auto kAwsProfileCategoryText = NSLOCTEXT("FGameLiftSettingsCustomization", "kAwsProfileCategoryText", "AWS User Profiles");

		static const auto kGameLiftOverviewCategory = "Getting Started";
		static const auto kGameLiftOverviewCategoryText = NSLOCTEXT("FGameLiftSettingsCustomization", "kGameLiftOverviewCategoryText", "Getting Started");

		static const auto kUseCaseCategory = "Games Using Amazon GameLift";
		static const auto kUseCaseCategoryText = NSLOCTEXT("FGameLiftSettingsCustomization", "kUseCaseCategoryText", "Games Using Amazon GameLift");

		static const auto kAdditionalResourcesCategory = "Additional Resources";
		static const auto kAdditionalResourcesCategoryText = NSLOCTEXT("FGameLiftSettingsCustomization", "kAdditionalResourcesCategoryText", "Additional Resources");
	}

	namespace AwsAccount
	{
		// Setup message
		static const auto kNotConfiguredText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "AwsAccountNotConfigured", "To use Amazon GameLift features, create a user profile linked to your AWS account.");
		static const auto kConfigurationFailedText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "AwsAccountConfigurationFailed", "Failed to configure your AWS user profile.");
		static const auto kConfiguredText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "AwsAccountConfigured", "Successfully configured your AWS user profile.");
		static const auto kSetPathInfoText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "AwsAccountInfoMessageText", "Setup credentials used for account bootstrapping and CloudFormation deployment. Choose already existing AWS account or create a new one selecting \"Import or Update new credentials profile\" from the dropdown list.");
		static const auto kAddNewAccountInfoText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "AwsAddNewAccountInfoText", "To Add a new AWS account you just need to copy credentials created through the AWS console");

		// Header
		static const auto kHeaderTitleText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "HeaderTitleText", "Manage AWS user profiles");
		static const auto kHeaderDescriptionText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "HeaderDescriptionText", "Create a profile to link to an AWS account, store your user credentials, and set a default AWS Region. You can have multiple user profiles.");
		static const auto kHeaderDocumentationLinkText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "HeaderDocumentationLinkText", "Documentation");
		static const auto kHeaderForumLinkText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "HeaderForumLinkText", "AWS GameTech forum");
		static const auto kHeaderPricePlanLinkText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "HeaderPricePlanLinkText", "Amazon GameLift pricing");

		// Profile startup
		static const auto kProfileStartupAccountMissingText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileStartupAccountMissingText", "I need a new AWS account for this project");
		static const auto kProfileStartupAccountMissingButtonText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileStartupAccountMissingButtonText", "Create an AWS account");
		static const auto kProfileStartupAccountMissingLinkText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileStartupAccountMissingLinkText", "Return here to complete configuration");

		static const auto kProfileStartupAccountText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileStartupAccountText", "I have an AWS account for this project");
		static const auto kProfileStartupAccountButtonText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileStartupAccountButtonText", "Add a new profile");

		// Profile modification
		static const auto kProfileModificationTitleText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileModificationTitleText", "Manage your profile");
		static const auto kProfileModificationDescriptionText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileModificationDescriptionText", "Select an existing profile from the dropdown list, or enter a profile name to create a new profile.");

		static const auto kProfileModificationProfileSelectionText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileModificationProfileSelectionText", "Choose a user profile");
		static const auto kProfileModificationProfileNameText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileModificationProfileNameText", "New profile name");
		static const auto kProfileModificationAccessKeyText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileModificationAccessKeyText", "AWS access key ID");
		static const auto kProfileModificationSecretKeyText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileModificationSecretKeyText", "AWS secret key");
		static const auto kProfileModificationRegionText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileModificationRegionText", "AWS Region");

		static const auto kAddNewProfileSelectionId = 0;
		static const auto kAddNewProfileSelectionText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "AddNewProfileSelectionText", "<New profile>");

		// Profile bootstrapping
		static const auto kProfileBootstrappingTitleText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileBootstrappingTitleText", "Bootstrap your profile");
		static const auto kProfileBootstrappingDescriptionText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ProfileBootstrappingDescriptionText", "Create an Amazon S3 bucket for this profile. Amazon GameLift stores build artifacts, AWS Lambda function code, and other data. This action can incur costs unless you have AWS Free Tier usage available.");

		// Buttons
		static const auto kBootstrapProfileButtonText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "BootstrapAccountButtonText", "Bootstrap profile");
		static const auto kBootstrapAndCreateProfileButtonText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "BootstrapAndCreateAccountText", "Bootstrap and create profile");
		static const auto kBootstrapAndUpdateProfileButtonText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "BootstrapAndUpdateAccountText", "Bootstrap and update profile");
		static const auto kAddNewProfileButtonText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "AddNewProfileButtonText", "Add new profile");
		static const auto kManageYourProfileButtonText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "ManageYourProfileButtonText", "Manage your profile");

		// Hyperlinks
		static const auto kHowToCreateAccountHyperLinkText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "HowToCreateAccountHyperLinkText", "How do I get my AWS credentials?");
		static const auto kHowToCreateAccountHyperLinkUrl = TEXT("https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html");
		static const auto kViewS3ConsoleHyperLinkText = NSLOCTEXT("SGameLiftSettingsAwsAccountMenu", "BootstrapS3BucketHyperLinkText", "View Amazon S3 Console");
		static const auto kViewS3ConsoleHyperLinkUrl = TEXT("https://s3.console.aws.amazon.com/s3/");

		// Bootstrap status
		static const auto kNoBootstrapMessage = NSLOCTEXT("SBootstrapStatus", "NoBootstrapMessage", "Inactive");
		static const auto kBootstrapInProgressMessage = NSLOCTEXT("SBootstrapStatus", "BootstrapInProgressMessage", "In Progress  (typically 5-8 seconds)");
		static const auto kActiveBootstrapMessage = NSLOCTEXT("SBootstrapStatus", "ActiveBootstrapMessage", "Active");
		static const auto kFailedBootstrapMessage = NSLOCTEXT("SBootstrapStatus", "FailedBootstrapMessage", "Failed");

		static const auto kBootstrapStatusText = NSLOCTEXT("SBootstrapStatus", "BootstrapStatusText", "Bootstrap status");
		static const auto kLoadingStatusText = NSLOCTEXT("SBootstrapStatus", "LoadingStatusText", "Loading status");
		static const auto kRegionNameText = NSLOCTEXT("SBootstrapStatus", "RegionNameText", "AWS Region");
		static const auto kBucketNameText = NSLOCTEXT("SBootstrapStatus", "BucketNameText", "Amazon S3 bucket");
		static const auto kEmptyBucketNameText = NSLOCTEXT("SBootstrapStatus", "EmptyBucketNameText", "No bucket created");
	} // namespace AwsAccount

	namespace GameLift
	{
		static const auto kGameLiftIntroDescriptionText = NSLOCTEXT("SGameLiftSettingsGameLiftMenu", "GameLiftIntroDescriptionText",
			"<RichTextBlock.Bold>Amazon GameLift</> is a dedicated game server hosting solution that deploys, operates, and scales cloud servers for session-based, multiplayer games. Use as a fully managed solution or for specific features. Leveraging the power of AWS, Amazon GameLift delivers the lowest possible latency, low player wait times, and maximum cost savings.");

		static const auto kGameLiftGetStartedTitleText = NSLOCTEXT("SGameLiftSettingsGameLiftMenu", "GameLiftGetStartedTitleText", "Get started with Amazon GameLift");

		static const auto kGameLiftSetUpAnywhereButtonText = NSLOCTEXT("SGameLiftSettingsGameLiftMenu", "GameLiftSetUpAnywhereButtonText", "Set up an Anywhere fleet");
		static const auto kGameLiftSetUpAnywhereDescriptionText = NSLOCTEXT("SGameLiftSettingsGameLiftMenu", "GameLiftSetUpAnywhereDescriptionText", "Test your game with your own hardware.");

		static const auto kGameLiftSetUpManagedEC2ButtonText = NSLOCTEXT("SGameLiftSettingsGameLiftMenu", "GameLiftSetUpManagedEC2ButtonText", "Set up a managed EC2 fleet");
		static const auto kGameLiftSetUpManagedEC2DescriptionText = NSLOCTEXT("SGameLiftSettingsGameLiftMenu", "GameLiftSetUpManagedEC2DescriptionText", "Deploy your game onto Amazon GameLift hosting servers.");

		static const auto kGameLiftLogoFile = TEXT("Editor/Images/GameLiftLogo.png");
	}

	namespace UseCase
	{
		static const auto kUseCaseTitleFormatText = NSLOCTEXT("SGameLiftSettingsUseCaseMenu", "UseCaseTitleFormatText", "<RichTextBlock.Bold>{0}</> developed <RichTextBlock.Bold>[{1}]</> using Amazon GameLift");
		static const auto kUseCaseLearnMoreText = NSLOCTEXT("SGameLiftSettingsUseCaseMenu", "UseCaseLearnMoreText", "Learn more");
	}

	namespace Help
	{
		static const auto kHelpGameLiftDocumentationLinkText = NSLOCTEXT("SGameLiftSettingsHelpMenu", "HelpGameLiftDocumentationLinkText", "Amazon GameLift documentation");
		static const auto kHelpAwsGameTechForumLinkText = NSLOCTEXT("SGameLiftSettingsHelpMenu", "HelpAwsGameTechForumLinkText", "AWS GameTech forum");
		static const auto kHelpTroubleshootAccountAccessIssuesLinkText = NSLOCTEXT("SGameLiftSettingsHelpMenu", "HelpTroubleshootAccountAccessIssuesLinkText", "Troubleshooting account access issues");

		static const auto kHelpAboutAmazonGameLiftLinkText = NSLOCTEXT("SGameLiftSettingsHelpMenu", "HelpAboutAmazonGameLift", "About Amazon GameLift");
		static const auto kHelpAwsForGamesBlogLinkText = NSLOCTEXT("SGameLiftSettingsHelpMenu", "HelpAwsForGamesBlogLinkText", "AWS for Games blog");
		static const auto kHelpAwsForGamesLinkText = NSLOCTEXT("SGameLiftSettingsHelpMenu", "HelpAwsForGamesLinkText", "AWS for Games");
		static const auto kHelpReportIssuesLinkText = NSLOCTEXT("SGameLiftSettingsHelpMenu", "HelpReportIssuesLinkText", "Report issues");
		static const auto kHelpContributingGuidelinesLinkText = NSLOCTEXT("SGameLiftSettingsHelpMenu", "HelpContributingGuidelinesLinkText", "Contributing guidelines");
	}

	namespace Logs
	{
		static const auto kBootstrapSucceed = TEXT("Bootstrap Account succeed");
		static const auto kBootstrapFailed = TEXT("Bootstrap Account failed");
	}

	static const auto kGoToSettingsButtonText = NSLOCTEXT("SSetupMessage", "GoToSettingsButtonText", "Manage Settings");
	static const auto kGoToDeploymentMenuText = NSLOCTEXT("SSetupMessage", "GoToDeploymentMenuText", "Deployment Menu");
} // namespace Settings

namespace ContextMenu
{
	// Amazon Section
	static const auto kAmazonSectionText = NSLOCTEXT("FGameLiftPluginModule", "AmazonSectionText", "Amazon");

	// Plugin Main Menu
	static const auto kPluginMainMenuText = NSLOCTEXT("FGameLiftPluginModule", "PluginMainMenuText", "GameLift Plugin");
	static const auto kPluginMainMenuTooltip = NSLOCTEXT("FGameLiftPluginModule", "PluginMainMenuTooltip", "Launch GameLift plugin");

	// Deployment Section
	static const auto kDeploymentSectionText = NSLOCTEXT("FGameLiftPluginModule", "DeploymentSectionText", "Amazon GameLift");

	// Help Section
	static const auto kHelpSectionText = NSLOCTEXT("FGameLiftPluginModule", "HelpSectionText", "Help");
	static const auto kHelpSubMenuText = NSLOCTEXT("FGameLiftPluginModule", "HelpSubMenuText", "Help");
	static const auto kHelpSubMenuTooltip = NSLOCTEXT("FGameLiftPluginModule", "HelpSubMenuTooltip", "Ask for help");

	static const auto kHelpDocumentationSectionText = NSLOCTEXT("FGameLiftPluginModule", "DocumentationSectionText", "Amazon GameLift");
	static const auto kHelpSdkSectionText = NSLOCTEXT("FGameLiftPluginModule", "SdkSectionText", "SDK");
}

namespace Menu
{
	static const auto kStatusMessageActiveTimeSec = 10;

	namespace DeployCommon
	{
		// Profile settings section
		static const auto kSetProfileHeader = NSLOCTEXT("SDeployCommon", "SetProfileHeader", "1. Set your profile");

		// Game integration section
		static const auto kIntegrateGameHeader = NSLOCTEXT("SDeployCommon", "IntegrateGameHeader", "2. Set up your Game with Amazon GameLift");
		static const auto kIntegrateGameDescription = NSLOCTEXT("SDeployCommon", "IntegrateGameDescription", "Integrate Amazon GameLift and build your game server and client. If you don't already have a source-built version of the UE editor, follow the steps to build it and update your game project to use it.");
		
		// New or existing Project
		static const auto kNewProjectDescription = NSLOCTEXT("SDeployCommon", "NewProjectDescription", "To generate Server and Client builds of your game, you will need to use a source-built version of Unreal Engine. Skip the first two steps if you already fulfill this prerequisite.");
		
		static const auto kNewProjectStep1 = NSLOCTEXT("SDeployCommon", "NewProjectStep1", "1. Get access to the Unreal repo");
		static const auto kNewProjectStep1_Button = NSLOCTEXT("SDeployCommon", "NewProjectStep1_Button", "How to get and build the UE editor from source");
		static const auto kNewProjectStep1_Url = TEXT("https://www.unrealengine.com/en-US/ue-on-github");
		
		static const auto kNewProjectStep2 = NSLOCTEXT("SDeployCommon", "NewProjectStep2", "2. Get and build the UE editor from source");
		static const auto kNewProjectStep2_Button = NSLOCTEXT("SDeployCommon", "NewProjectStep2_Button", "Download source");
		static const auto kNewProjectStep2_Url = TEXT("https://github.com/EpicGames/UnrealEngine");
		
		static const auto kNewProjectStep3 = NSLOCTEXT("SDeployCommon", "NewProjectStep3", "3. Integrate your game server and client");
		static const auto kNewProjectStep3_Button = NSLOCTEXT("SDeployCommon", "NewProjectStep3_Button", "How to integrate your game");
		static const auto kNewProjectStep3_Url = TEXT("");
		
		// Server and Client paths
		static const auto kGameServerPathTitle = NSLOCTEXT("SDeployCommon", "GameServerPathTitle", "Path to server build");
		static const auto kGameServerPathHint = NSLOCTEXT("SDeployCommon", "GameServerPathHint", "Path to server build executable");
		static const auto kGameServerPathTooltip = NSLOCTEXT("SDeployCommon", "GameServerPathTooltip", "Specify path to server build executable");

		static const auto kGameClientPathTitle = NSLOCTEXT("SDeployCommon", "GameClientTitle", "Path to client build");
		static const auto kGameClientPathHint = NSLOCTEXT("SDeployCommon", "GameClientPathHint", "Path to client build executable");
		static const auto kGameClientPathTooltip = NSLOCTEXT("SDeployCommon", "GameClientPathTooltip", "Specify path to client build executable");

		static const auto kDeploymentShowOutputLog = NSLOCTEXT("SDeployCommon", "DeploymentShowOutputLog", "Show Output Log");
	}

	namespace DeployAnywhere
	{
		static const auto kConnectToFleetHeader = NSLOCTEXT("DeployAnywhere", "ConnectToFleetHeader", "3. Connect to Anywhere Fleet");
		static const auto kRegisterComputeHeader = NSLOCTEXT("DeployAnywhere", "RegisterComputeHeader", "4. Register your workstation");
		static const auto kGenerateAuthTokenHeader = NSLOCTEXT("DeployAnywhere", "GenerateAuthTokenHeader", "5. Generate Auth Token - optional");
		static const auto kLaunchGameServerAndClientHeader = NSLOCTEXT("DeployAnywhere", "LaunchGameServerAndClientHeader", "6. Launch game server and client");

		// Connect section
		static const auto kFleetSectionDescription = NSLOCTEXT("SConnectAnywhereFleetMenu", "FleetSectionDescription", "This action can incur costs to your account unless you have AWS Free Tier usage available.");
		static const auto kNewFleetNameTitle = NSLOCTEXT("SConnectAnywhereFleetMenu", "AnywhereFleetNameTitle", "Fleet name");
		static const auto kUnselectedFleetDropDownText = NSLOCTEXT("SConnectAnywhereFleetMenu", "UnselectedFleetDropDownText", "Choose an Anywhere fleet");
		static const auto kLoadingFleetDropDownText = NSLOCTEXT("SConnectAnywhereFleetMenu", "LoadingFleetDropDownText", "Loading fleets...");
		static const auto kLoadingFleetErrorText = NSLOCTEXT("SConnectAnywhereFleetMenu", "LoadingFleetErrorText", "An error occurred when trying to load available fleets.");
		static const auto kLoadingFleetRetryText = NSLOCTEXT("SConnectAnywhereFleetMenu", "LoadingFleetRetryText", "Reload fleets");
		static const auto kSelectedFleetTitle = NSLOCTEXT("SConnectAnywhereFleetMenu", "AnywhereSelectedFleetTitle", "Fleet name");
		static const auto kSelectedFleetIDTitle = NSLOCTEXT("SConnectAnywhereFleetMenu", "AnywhereSelectedFleetIdTitle", "Fleet ID");
		static const auto kCreateFleetButtonText = NSLOCTEXT("SConnectAnywhereFleetMenu", "AnywhereCreateFleetButtonText", "Create Anywhere fleet");
		static const auto kGoToCreateFleetButtonText = NSLOCTEXT("SConnectAnywhereFleetMenu", "AnywhereGoToCreateFleetButtonText", "Create new Anywhere fleet");
		static const auto kFleetNameInstructionText = NSLOCTEXT("SConnectAnywhereFleetMenu", "FleetNameInstructionText", "The fleet name must have 1-1024 characters. Valid characters are A-Z, a-z, 0-9, _ and - (hyphen).");
		static const auto kAnywhereFleetActiveText = NSLOCTEXT("SConnectAnywhereFleetMenu", "AnywhereFleetActiveText", "Active");
		static const auto kNewFleetNameTextBoxHint = NSLOCTEXT("SConnectAnywhereFleetMenu", "NewFleetNameTextBoxHint", "Fleet name");

		// Auth token section
		static const auto kAuthTokenTitle = NSLOCTEXT("SDeployAnywhereMenu", "AuthTokenTitle", "Auth token");
		static const auto kAuthTokenNotGeneratedText = NSLOCTEXT("SDeployAnywhereMenu", "AuthTokenNotGeneratedText", "The auth token is generated when you launch your game.");
		static const auto kAuthTokenGenerateNoteText = NSLOCTEXT("SDeployAnywhereMenu", "AuthTokenGenerateNoteText", "Auth tokens are valid for 3 hours and must be refreshed.");
		static const auto kAuthTokenGenerateButtonText = NSLOCTEXT("SDeployAnywhereMenu", "AuthTokenGenerateButtonText", "Generate auth token");

		// Register compute section
		static const auto kComputeNameTitle = NSLOCTEXT("SAnywhereRegisterComputeMenu", "ComputeNameTitle", "Compute name");
		static const auto kComputeNameTextHint = NSLOCTEXT("SAnywhereRegisterComputeMenu", "ComputeNameTextHint", "Compute name");
		static const auto kComputeNameDefault = NSLOCTEXT("SAnywhereRegisterComputeMenu", "ComputeNameDefault", "AnywhereCompute");
		static const auto kComputeIPTitle = NSLOCTEXT("SAnywhereRegisterComputeMenu", "ComputeIPTitle", "IP address");
		static const auto kComputeIPTextHint = NSLOCTEXT("SAnywhereRegisterComputeMenu", "ComputeIPTextHint", "0 . 0 . 0 . 0");
		static const auto kComputeIPTextTooltip = NSLOCTEXT("SAnywhereRegisterComputeMenu", "ComputeIPTextTooltip", "Default to local IP address. You can use localhost (127.0.0.1) as the IP address. If your machine is accessible via a public IP address, change that value as appropriate.");
		static const auto kComputeStatusRegisteredText = NSLOCTEXT("SAnywhereRegisterComputeMenu", "ComputeStatusRegisteredText", "Registered");
		static const auto kRegisterNewComputeButtonText = NSLOCTEXT("SAnywhereRegisterComputeMenu", "RegisterNewComputeButtonText", "Register new compute");
		static const auto kRegisterFirstComputeButtonText = NSLOCTEXT("SAnywhereRegisterComputeMenu", "RegisterFirstComputeButtonText", "Register compute");

		// Launch game server and client section
		static const auto kGameServerLaunchTitle = NSLOCTEXT("SDeployAnywhereMenu", "GameServerLaunchTitle", "Launch game server");
		static const auto kGameServerLaunchButtonText = NSLOCTEXT("SDeployAnywhereMenu", "GameServerLaunchButtonText", "Run server");

		static const auto kGameClientLaunchTitle = NSLOCTEXT("SDeployAnywhereMenu", "GameClientLaunchTitle", "Launch game client");
		static const auto kGameClientLaunchButtonText = NSLOCTEXT("SDeployAnywhereMenu", "GameClientLaunchButtonText", "Run client");

		static const auto kGameLaunchNoteText = NSLOCTEXT("SDeployAnywhereMenu", "GameLaunchNoteText", "You may need to wait 30 secs after fleet creation.");

		static const auto kGameServerLaunchParameterLog = TEXT("-log");
		static const auto kGameServerLaunchParameterEnableAnywhere = TEXT("-glAnywhere");
		static const auto kGameServerLaunchParameterWebSocketUrl = TEXT("-glAnywhereWebSocketUrl={0}");
		static const auto kGameServerLaunchParameterFleetId = TEXT("-glAnywhereFleetId={0}");
		static const auto kGameServerLaunchParameterHostId = TEXT("-glAnywhereHostId={0}");
		static const auto kGameServerLaunchParameterAuthToken = TEXT("-glAnywhereAuthToken={0}");

		static const auto kGameClientLaunchParameterWindowMode = TEXT("-windowed");
		static const auto kGameClientLaunchParameterCredentialsName = TEXT("-glAnywhereClientCredentialsName={0}");
		static const auto kGameClientLaunchParameterFleetId = TEXT("-glAnywhereClientFleetId={0}");
		static const auto kGameClientLaunchParameterCustomLocation = TEXT("-glAnywhereClientCustomLocation={0}");

		static const auto kGameServerWebSocketUrlFormat = TEXT("wss://{0}.api.amazongamelift.com");

		// Hyperlinks
		static const auto kViewInGameLiftConsoleHyperLinkText = NSLOCTEXT("SDeployAnywhereMenu", "ViewInGameLiftConsoleHyperLinkText", "View in Amazon GameLift Console");
		static const auto kViewInGameLiftConsoleHyperLinkUrlFormat = TEXT("https://{0}.console.aws.amazon.com/gamelift/fleets");

		static const auto kStatusTitle = NSLOCTEXT("SDeployAnywhereMenu", "StatusTitle", "Status");
		static const auto kCancelButtonText = NSLOCTEXT("SDeployAnywhereMenu", "CancelButtonText", "Cancel");

		// Misc
		static const auto kIPv4ValidationRegex = TEXT("^((25[0-5]|(2[0-4]|1[0-9]|[1-9]|)[0-9])(\\.(?!$)|$)){4}$");
	} // namespace DeployAnywhere

	namespace DeployManagedEC2
	{
		static const auto kS3Bucket = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "S3Bucket_ToolTip", "Resources used by this plugin are stored in this Amazon S3 bucket");

		// Select scenario
		static const auto kSelectScenarioTitle = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "SelectScenarioTitle", "Deployment scenario");
		static const auto kSelectScenarioDescription = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "SelectScenarioDescription", "Each scenario involves a different set of AWS resources and associated charges. Deploying the scenario can incur costs to your account unless you have AWS Free Tier usage available.");

		// Game parameters
		static const auto kBuildName = NSLOCTEXT("SDeploymentFields", "BuildName_Text", "Server build name");
		static const auto kBuildNameHint = NSLOCTEXT("SDeploymentFields", "BuildName_Hint", "Build name");
		static const auto kBuildNameInstructionText = NSLOCTEXT("SDeploymentFields", "BuildName_InstructionText", "The build name must have 1-12 characters.");

		static const auto kBuildOperatingSystemTitle = NSLOCTEXT("SDeploymentFields", "BuildOperatingSystem_Text", "Server build OS");

		static const auto kBuildFolderPathTitle = NSLOCTEXT("SDeploymentFields", "BuildFolderPath_Title", "Server build folder");
		static const auto kBuildFolderPathTooltip = NSLOCTEXT("SDeploymentFields", "BuildFolderPath_ToolTip", "Specify the folder containing the packaged game server.");
		static const auto kBuildFolderPathHint = NSLOCTEXT("SDeploymentFields", "BuildFolderPath_Hint", "Path to server build folder");

		static const auto kBuildFilePathTitle = NSLOCTEXT("SDeploymentFields", "BuildFilePath_Title", "Server build executable");
		static const auto kBuildFilePathTooltip = NSLOCTEXT("SDeploymentFields", "BuildFilePath_ToolTip", "Specify the executable file of your game server within server folder path.");
		static const auto kBuildFilePathHint = NSLOCTEXT("SDeploymentFields", "BuildFilePath_Hint", "Path to server build executable");
		static const auto kBuildFilePathFilter = TEXT("Game Server|*.exe;*.sh;|All Files|*");

		static const auto kExtraServerResourcesPathTitle = NSLOCTEXT("SDeploymentFields", "ExtraFilesPath_Title", "Additional server resources path");
		static const auto kExtraServerResourcesPathTooltip = NSLOCTEXT("SDeploymentFields", "ExtraFilesPath_ToolTip", "Specify a folder which contains additional files for Gamelift server delivery.");

		static const auto kOutConfigFilePathTitle = NSLOCTEXT("SDeploymentFields", "ConfigFilePath_Title", "Client configuration output path");
		static const auto kOutConfigFilePathTooltip = NSLOCTEXT("SDeploymentFields", "ConfigFilePath_ToolTip", "Specify a folder in the client build where the aws configuration should be stored. Your client will need this file to access the server in the cloud.\nSuggested path: \"<Client Build>/<Project Name>/Content/CloudFormation\".");
		static const auto kOutConfigFilePathHint = NSLOCTEXT("SDeploymentFields", "ConfigFilePath_Hint", "Path to client configuration output path");

		static const auto kWindowsServer2016Name = NSLOCTEXT("EFleetOperatingSystem", "WindowsServer2016Name", "Windows Server 2016");
		static const auto kWindowsServer2016Value = NSLOCTEXT("EFleetOperatingSystem", "WindowsServer2016Value", "WINDOWS_2016");
		static const auto kAmazonLinux2Name = NSLOCTEXT("EFleetOperatingSystem", "AmazonLinux2Name", "Amazon Linux 2 (AL2)");
		static const auto kAmazonLinux2Value = NSLOCTEXT("EFleetOperatingSystem", "AmazonLinux2Value", "AMAZON_LINUX_2");
		static const auto kAmazonLinux2023Name = NSLOCTEXT("EFleetOperatingSystem", "AmazonLinux2023Name", "Amazon Linux 2023 (AL2023)");
		static const auto kAmazonLinux2023Value = NSLOCTEXT("EFleetOperatingSystem", "AmazonLinux2023Value", "AMAZON_LINUX_2023");

		// Deploy scenario
		static const auto kDeploymentStatusInfoRichText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "DeploymentStatusInfoRichText", "<RichTextBlock.Bold>Deploying GameLift can take up to 30-40 minutes.</> Deploying and running various AWS resources in the CloudFormation template will incur costs to your account. See Amazon GameLift pricing for details on the costs for each resource in the CloudFormation template.");

		static const auto kGameLiftHowToDeployYourFirstGameLinkText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "GameLiftHowToDeployYourFirstGameLinkText", "How to deploy your first game");
		static const auto kGameLiftEndpointsLinkText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "GameLiftEndpointsLinkText", "Amazon GameLift endpoints and quotas");
		static const auto kGameLiftPricingPlanLinkText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "GameLiftPricingPlanLinkText", "Amazon GameLift pricing");

		static const auto kDeploymentStartedAwsScenarioNotification = TEXT("Deploying GameLift scenario...");
		static const auto kDeploymentStartedCustomScenarioNotification = TEXT("Deploying a custom GameLift scenario...");
		static const auto kDeploymentAbortedNotification = TEXT("Aborting GameLift deployment...");
		static const auto kDeploymentCompletedNotification = TEXT("GameLift deployment is completed.");
		static const auto kDeploymentFailedNotification = TEXT("GameLift deployment is failed.");

		static const auto kNeedDeployment = "Need Deployment";
		
		static const auto kNoDeployment = "Undeployed";
		static const auto kNoDeployment_Alternate = "No Deployment";
		static const auto kInProgressDeployment = "In Progress";
		static const auto kAbortInProgressDeployment = "Abort in Progress";
		static const auto kActiveDeployment = "Deployed";
		static const auto kActiveDeployment_Alternate = "Active";
		static const auto kFailedDeployment = "Failed";

		static const auto kDeploymentStoppedMessage = "Deployment has been cancelled";

		static const auto kConfirmStopDeploymentText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "ConfirmStopDeploymentText", "Do you really want to stop deployment?");
		static const auto kConfirmReploymentText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "ConfirmRedeploymentText", "Do you really want to redeploy stack?");

		static const auto kAwsResourceActionsText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "DeployCloudFormationTitle", "AWS resource actions");
		static const auto kDeployCloudFormationButtonText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "DeployCloudFormationButtonText", "Deploy scenario");
		static const auto kRedeployCloudFormationButtonText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "RedeployCloudFormationButtonText", "Redeploy scenario");
		static const auto kStopCloudFormationButtonText = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "StopCloudFormationButtonText", "Stop deployment");

		static const auto kDeploymentEnabledTooltip = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "kDeploymentEnabledTooltip", "Deployment can be triggered");
		static const auto kDeploymentDisabledNeedBootstrapTooltip = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "kDeploymentDisabledNeedBootstrapTooltip", "Account needs to be configured first");
		static const auto kDeploymentDisabledBuildNameEmptyTooltip = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "kDeploymentDisabledBuildNameEmptyTooltip", "Cannot deploy game name with empty build name");
		static const auto kDeploymentDisabledBuildNameTooLongTooltip = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "kDeploymentDisabledBuildNameTooLongTooltip", "Cannot deploy game name with more than 12 characters");
		static const auto kDeploymentDisabledServerBuildPathNotSetTooltip = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "kDeploymentDisabledServerBuildPathNotSetTooltip", "Cannot deploy with empty server build paths");
		static const auto kDeploymentDisabledAlreadyActiveTooltip = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "kDeploymentDisabledAlreadyActiveTooltip", "Deployment cannot be triggered once it is in progress state");

		static const auto kMaxGameNameLength = 12;

		static const auto kStopDeploymentEnabledTooltip = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "StopDeploymentEnabledTooltip", "Deployment can be stopped");
		static const auto kStopDeploymentDisabledTooltip = NSLOCTEXT("SGameLiftDeployManagedEC2Menu", "StopDeploymentDisabledTooltip", "Deployment can be stopped once it is in pending status");

		static const auto kViewInCloudFormationConsoleHyperLinkText = NSLOCTEXT("SDeploymentStatus", "ViewInCloudFormationConsoleHyperLinkText", "View in CloudFormation Console");
		static const auto kViewInCloudFormationHyperLinkUrlFormat = TEXT("https://{0}.console.aws.amazon.com/cloudformation/home");

		static const auto kDeploymentStatusText = NSLOCTEXT("SGameLiftClientMenu", "DeploymentStatus", "Deployment status");
		static const auto kScenarioText = NSLOCTEXT("SGameLiftClientMenu", "Scenario", "Deployment scenario");
		static const auto kAwsRegionText = NSLOCTEXT("SDeploymentStatus", "AwsRegion", "AWS Region");
		static const auto kBuildNameText = NSLOCTEXT("SDeploymentStatus", "BuildName", "Server build name");

		static const auto kLastUpdatedText = NSLOCTEXT("SDeploymentStatus", "LastUpdatedText", "Last updated");
		static const auto kErrorMessageText = NSLOCTEXT("SDeploymentStatus", "ErrorMessageText", "Error message");

		static const auto kCognitoClientIdText = NSLOCTEXT("SDeploymentStatus", "CognitoClientId", "Cognito client ID");
		static const auto kCognitoClientIdTooltip = NSLOCTEXT("SDeploymentStatus", "CognitoClientId_Tooltip", "Amazon Cognito is an AWS service to authenticate users for your game. You can\ncopy and paste this Client ID where you manage player credentials.");

		static const auto kApiGatewayEndpointText = NSLOCTEXT("SDeploymentStatus", "ApiGatewayEndpoint", "Gateway endpoint");
		static const auto kApiGatewayEndpointTooltip = NSLOCTEXT("SDeploymentStatus", "ApiGatewayEndpoint_Tooltip", "Amazon API is an AWS service to create and use APIs. You can copy\nand paste this endpoint wherever you need to integrate with AWS and GameLift.");

		// Client
		static const auto kRunDeploymentGameInfoText = NSLOCTEXT("SGameLiftClientMenu", "ClientInfoText", "To run a sample game you need to specify Client path that your previously built.");

		static const auto kDeployedGameClientRunningMessage = NSLOCTEXT("SGameLiftClientMenu", "ClientRunningMessage", "Deployed Game client has started locally");
		static const auto kDeployedGameClientFailureMessage = NSLOCTEXT("SGameLiftClientMenu", "ClientFailureMessage", "Unable to start a Deployed Game client locally");

		static const auto kNotDeployedMessage = NSLOCTEXT("SGameLiftClientMenu", "NotDeployedMessage", "To run a sample Game in Amazon Gamelift Testing Mode\nyou need to make deployment first.");

		static const auto kGameClientPathText = NSLOCTEXT("SGameLiftClientMenu", "SetGameClientPath", "Client build executable");
		static const auto kGameClientPathHint = NSLOCTEXT("SGameLiftClientMenu", "SetGameClientPathHint", "Path to client build executable");

		static const auto kLaunchGameClientText = NSLOCTEXT("SGameLiftClientMenu", "LaunchGameClient", "Launch game client");
		static const auto kLaunchGameClientButtonText = NSLOCTEXT("SGameLiftClientMenu", "LaunchGameClientButtonText", "Run client");

		static const auto kCanLaunchGameClientTooltipText = NSLOCTEXT("SGameLiftClientMenu", "kCanLaunchGameClientTooltipText", "Game client can be launched");
		static const auto kCannotLaunchGameClientNoPathTooltipText = NSLOCTEXT("SGameLiftClientMenu", "kCannotLaunchGameClientNoPathTooltipText", "Please specify a game path");
		static const auto kCannotLaunchGameClientNoDeploymentTooltipText = NSLOCTEXT("SGameLiftClientMenu", "kCannotLaunchGameClientNoDeploymentTooltipText", "Please create a deployment before launching game client");

		namespace Logs
		{
			static const auto kOutputPathChangedWarning = TEXT("Client Config File Output Path is not default");
			static const auto kDeploymentSucceed = TEXT("Deployment succeed");
			static const auto kDeploymentFailed = TEXT("Deployment failed");
		}
	} // namespace DeployManagedEC2

	static const auto kErrorUserMessageWithLog = NSLOCTEXT("FGameLiftPluginModule", "ErrorUserMessageWithLog", "For more information, see `Output Log`");
	static const auto kErrorUserMessageNoLog = NSLOCTEXT("FGameLiftPluginModule", "ErrorUserMessageNoLog", "Unknown failure, for more information, see `Output Log`. \nError code is:");
} // namespace Menu

namespace Tabs
{
	static const auto kDeployAnywhereTabTitle = NSLOCTEXT("FGameLiftDeployAnywhereTab", "FGameLiftDeployAnywhereTab_Title", "Deploy Anywhere");
	static const auto kDeployAnywhereTabTooltip = NSLOCTEXT("FGameLiftDeployAnywhereTab", "FGameLiftDeployAnywhereTab_Tooltip", "Deploy the game with Amazon GameLift Anywhere.");
	
	static const auto kDeployManagedEC2TabTitle = NSLOCTEXT("FGameLiftDeployManagedEC2Tab", "FGameLiftDeployManagedEC2Tab_Title", "Deploy EC2 Fleet");
	static const auto kDeployManagedEC2TabTooltip = NSLOCTEXT("FGameLiftDeployManagedEC2Tab", "FGameLiftDeployManagedEC2Tab_Tooltip", "Deploy the game with Amazon GameLift on a managed EC2 instance.");
} // namespace Tabs

namespace Defaults
{
	static const auto kDefaultS3Bucket = "";
} // namespace Defaults

namespace Style
{
	static const FName kGameLiftPluginStyleName = "GameLiftPluginStyle";

	constexpr auto KPrimaryWidthOverride = 220.0f;
	constexpr auto kSecondaryWidthOverride = 0.0f;  // Stretch to fill the whole column

	static const auto kLinkIconSize = 12;
	static const auto kStatusIconSize = 12;
	static const auto kTooltipIconSize = 12;
	static const auto kLoadingIconSize = 16;
	static const auto kBannerIconSize = 16;

	namespace Brush
	{ 
		static const auto kFolderOpenIconName = "FolderOpenIcon";
		static const auto kGameLiftTabIconName = "GameLiftTabIcon";
		static const auto kGameLiftToolbarIconName = "GameLiftToolbarIcon";
		static const auto kTooltipIconName = "TooltipIcon";
		static const auto kBorderImageName = "BorderImage";

		static const auto kExternalLinkIconName = "ExternalLinkIcon";
		static const auto kStatusSuccessIconName = "StatusSuccessIcon";
		static const auto kStatusWarningIconName = "StatusWarningIcon";
		static const auto kStatusErrorIconName = "StatusErrorIcon";
		static const auto kStatusInactiveIconName = "StatusInactiveIcon";

		static const auto kAccountIconName = "AccountIcon";
		static const auto kAccountMissingIconName = "AccountMissingIcon";

		static const auto kGameLiftLogoIconName = "GameLiftLogoIcon";
		static const auto kGameLiftLogoIconSize = FVector2D(67, 51);
	}

	namespace Font
	{
		const int SectionHeaderFontSize = 9;
		const int ParagraphFontSize = 10;
		const int FieldFontSize = 10;
		const int ButtonFontSize = 10;

		const int NoteFontSize = 9;
		const int LinkFontSize = 8;

		static const auto kTitleFontSize = 16;
		static const auto kSubtitleFontSize = 13;
	}

	namespace Text
	{
		static const auto kMessageLog = "MessageLog";

		static const auto kParagraph = "ParagraphTextStyle";
		static const auto kField = "FieldTextStyle";
		static const auto kFieldMedium = "FieldMediumTextStyle";
		static const auto kFieldBold = "FieldBoldTextStyle";
		static const auto kFieldItalic = "FieldItalicTextStyle";
		static const auto kNote = "NoteTextStyle";
		static const auto kNoteLight = "NoteLightTextStyle";
		static const auto kNoteItalic = "NoteItalicTextStyle";
		static const auto kSelectionDescription = "SelectionDescriptionTextStyle";

		static const auto kTitleStyleName = "TitleTextStyle";
		static const auto kSubtitleStyleName = "SubtitleTextStyle";

		static const auto kButtonNormal = "ButtonNormalTextStyle";
		static const auto kButtonLight = "ButtonLightTextStyle";
		
		static const auto kSectionHeaderFontStyleName = "SectionHeaderTextStyle";
	}

	namespace EditableText
	{
		static const auto kParagraph = "ParagraphEditableTextStyle";
		static const auto kField = "FieldEditableTextStyle";
		static const auto kFieldMedium = "FieldMediumEditableTextStyle";
		static const auto kFieldBold = "FieldBoldEditableTextStyle";
	}

	namespace EditableTextBox
	{
		static const auto kField = "FieldEditableTextBoxStyle";
	}

	namespace Button
	{
		static const auto kFlatButtonStyleName = "FlatButton";

		static const auto kNormalButtonStyleName = "NormalButton";
		static const auto kSuccessButtonStyleName = "SuccessButton";
		static const auto kErrorButtonStyleName = "ErrorButton";
		static const auto kCloseButtonStyleName = "CloseButton";

		static const auto kVisibilityButtonWidth = 70;
	}

	namespace Color
	{
		static const auto kSectionHeaderBackground = "SectionHeaderBackground";
		static const auto kPanelBackground = "PanelBackgroundColor";

		static const auto kCardBackground = "CardBackground";

		static const auto kTogglerBackground = "TogglerBackground";
		static const auto kTogglerBorder = "TogglerBorder";

		static const auto kSuccessForeground = "SuccessForegroundColor";
		static const auto kSuccessBackground = "SuccessBackgrounColor";
		static const auto kWarningForeground = "WarningForegroundColor";
		static const auto kWarningBackground = "WarningBackgroundColor";
		static const auto kErrorForeground = "ErrorForegroundColor";
		static const auto kErrorBackground = "ErrorBackgroundColor";

		static const auto kInactive = "InactiveColor";
		static const auto kSuccess = "SuccessColor";
		static const auto kWarning = "WarningColor";
		static const auto kError = "ErrorColor";
		static const auto kLoading = "LoadingColor";

		static const auto kTooltip = "TooltipColor";

		// Button colors
		static const auto kSuccessButtonNormal = "SuccessButtonNormalColor";
		static const auto kSuccessButtonHovered = "SuccessButtonHoveredColor";
		static const auto kSuccessButtonPressed = "SuccessButtonPressedColor";

		static const auto kErrorButtonNormal = "ErrorButtonNormalColor";
		static const auto kErrorButtonHovered = "ErrorButtonHoveredColor";
		static const auto kErrorButtonPressed = "ErrorButtonPressedColor";
	}

	static const auto kLinkStyleName = "LinkStyle";
} // namespace Style

namespace SPadding
{
	// Use these constants for padding widgets to avoid random numbers being used in the code base.

	static const auto Left = FMargin(5, 0, 0, 0);
	static const auto Right = FMargin(0, 0, 5, 0);
	static const auto Top = FMargin(0, 5, 0, 0);
	static const auto Bottom = FMargin(0, 0, 0, 5);

	static const auto Left2x = FMargin(10, 0, 0, 0);
	static const auto Right2x = FMargin(0, 0, 10, 0);
	static const auto Top2x = FMargin(0, 10, 0, 0);
	static const auto Bottom2x = FMargin(0, 0, 0, 10);

	static const auto Top_Bottom = FMargin(0, 5, 0, 5);
	static const auto Top2x_Bottom = FMargin(0, 10, 0, 5);
	static const auto Top_Bottom2x = FMargin(0, 5, 0, 10);
	static const auto Top2x_Bottom2x = FMargin(0, 10, 0, 10);

	static const auto Left_Right = FMargin(5, 0, 5, 0);
	static const auto Left2x_Right = FMargin(10, 0, 5, 0);
	static const auto Left_Right2x = FMargin(5, 0, 10, 0);
	static const auto Left2x_Right2x = FMargin(10, 0, 10, 0);

	static const auto All = FMargin(5);
	static const auto All2x = FMargin(10);

	static const auto  BannerContentAll = FMargin(8);

	static const auto Extra_For_Page_End = SPadding::Bottom2x * 10;
} // namespace SPadding

namespace Url
{
	// Additional Resources
	static const auto kGameLiftDocumentationUrl = TEXT("https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-intro.html");
	static const auto kGameTechForumUrl = TEXT("https://repost.aws/tags/TAF8-XUqojTsadH5jSz3IfGQ/amazon-gamelift");
	static const auto kTroubleshootAccountAccessIssueUrl = TEXT("https://docs.aws.amazon.com/IAM/latest/UserGuide/troubleshoot.html");
	static const auto kAboutGameLiftUrl = TEXT("https://aws.amazon.com/gamelift/");

	static const auto kAwsForGamesBlogUrl = TEXT("https://aws.amazon.com/blogs/gametech/");
	static const auto kAwsForGamesUrl = TEXT("https://aws.amazon.com/gametech/?nc2=h_ql_sol_ind_gt");
	static const auto kContributingGuidelinesUrl = TEXT("https://github.com/aws/amazon-gamelift-plugin-unreal/blob/main/CONTRIBUTING.md");
	
	// Context Menu
	static const auto kOpenGameLiftDocumentationUrl = kGameLiftDocumentationUrl;
	static const auto kOpenAwsGameTechForumUrl = kGameTechForumUrl;
	static const auto kReportIssuesUrl = TEXT("https://github.com/aws/amazon-gamelift-plugin-unreal/issues");
	static const auto kOpenServiceAPIReferenceUrl = TEXT("https://docs.aws.amazon.com/gamelift/latest/apireference/Welcome.html");
	static const auto kOpenServerSDKReferenceUrl = TEXT("https://docs.aws.amazon.com/gamelift/latest/developerguide/integration-server-sdk5-cpp.html");

	// Other
	static const auto kGameLiftHowToDeployYourFirstGameUrl = TEXT("https://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin-ec2-scenarios.html");
	static const auto kGameLiftEndpointsUrl = TEXT("https://docs.aws.amazon.com/general/latest/gr/gamelift.html");
	static const auto kGameLiftPricingPlanUrl = TEXT("https://aws.amazon.com/gamelift/pricing/");
	static const auto kAwsAccountCreateAwsAccountUrl = TEXT("https://repost.aws/knowledge-center/create-and-activate-aws-account");

	static const auto kHowToIntegrateYourGameForAnywhereUrl = TEXT("http://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin-anywhere-integrate.html");
	static const auto kHowToIntegrateYourGameForEC2Url = TEXT("http://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin-ec2-integrate.html");
} // namespace Url
