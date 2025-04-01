# Amazon GameLift Servers Plugin for Unreal Engine


![GitHub](https://img.shields.io/github/license/aws/amazon-gamelift-plugin-unreal)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/aws/amazon-gamelift-plugin-unreal)
![GitHub all releases](https://img.shields.io/github/downloads/aws/amazon-gamelift-plugin-unreal/total)
![GitHub release (latest by date)](https://img.shields.io/github/downloads/aws/amazon-gamelift-plugin-unreal/latest/total)

Amazon GameLift Servers plugin for Windows is compatible with Unreal Engine 5 (versions 5.0, 5.1, 5.2, 5.3, 5.4, and 5.5).  Use the plugin to develop and package game servers for Windows or Linux, and game clients for any Unreal-supported platform.

[Overview](#overview)

[Install the plugin](#install-the-plugin)

[Troubleshoot installation](#troubleshoot-installation)

[Next steps: Get started with the plugin](#next-steps-get-started-with-the-plugin)

[Additional resources](#additional-resources)

[Instructions for contributors](#instructions-for-contributors)

## Overview

[Amazon GameLift Servers](https://aws.amazon.com/gamelift/servers/) is a fully managed service that gives game developers the ability to manage and scale dedicated game servers for session-based multiplayer games. The **Amazon GameLift Servers plugin for Unreal Engine** streamlines the process of setting up an Unreal game project for hosting on Amazon GameLift Servers.

With the plugin added to your Unreal game project, you can work with Amazon GameLift Servers from inside the Unreal Editor. Use the plugin to complete these steps:

* Integrate your game server code with the server SDK for Amazon GameLift Servers (included with the plugin), so that the game server can communicate with the service and respond to prompts to start and run game sessions.
* Deploy your integrated game server to an Amazon GameLift Servers fleet. Use the plugin’s guided workflows to configure and deploy a Windows or Linux game server using any of these deployment options. [Learn more about each option.](https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-intro-flavors.html#gamelift-intro-flavors-hosting)
    * **Anywhere fleet.** Deploy an Anywhere fleet to run game servers on hosting resources that you control. Anywhere fleets are commonly used to test on a local device, or to act as test environments for iterative development. You can also use Anywhere fleets to set up game hosting on-premises hardware, other resources, or as part of a hybrid solution.
    * **Managed EC2 fleet.** Deploy a managed EC2 fleet to run game servers on AWS Cloud resources that are managed by Amazon GameLift Servers. With this option you get resources and management tools (such as automatic scaling) that are optimized for multiplayer game hosting.
    * **Managed container fleet (for Linux servers).** Deploy a managed container fleet to run game servers on AWS Cloud resources in a containerized environment. Container fleets are managed by Amazon GameLift Servers and provide EC2 resources and management tools (such as automatic scaling) that are optimized for multiplayer game hosting.
* Build a backend service with the AWS SDK for Amazon GameLift Servers (included with the plugin) and add functionality to your game client to start a game session and connect to it. When you deploy to a managed fleet, the plugin also deploys a simple backend service for your game. You can use the default backend service or customize it as needed.
* Perform tests using plugin functionality to start a game client and join a running game session.
* Continue to use the plugin’s SDKs and tools when you want to customize your game hosting beyond the plugin’s guided workflows.

When deploying a game server to a fleet for hosting, Amazon GameLift Servers uses an AWS CloudFormation template to create a resource stack for your solution. You can view and manage your resource stacks in the AWS Management Console for AWS CloudFormation.

## Install the plugin

Follow these steps to set up the Amazon GameLift Servers plugin and add it to your Unreal Engine editor.

1. [Install prerequisites](#step-1-install-prerequisites)
2. [Download the plugin](#step-2-get-the-plugin)
3. [Build the C++ server SDK](#step-3-build-the-c-server-sdk-for-unreal)
4. [Add the plugin to an Unreal game project](#step-4-add-the-plugin-to-your-unreal-game-project)

### Step 1: Install prerequisites

You’ll need the following tools to install and run the plugin with your Unreal projects.

* [CMake](https://cmake.org/download/) version 3.1 or later. (required for plugin installation only)
* An AWS account to use with Amazon GameLift Servers. To use the plugin guided workflows, you need a user profile with your AWS account and access credentials. See [Set up an AWS account](https://docs.aws.amazon.com/gamelift/latest/developerguide/setting-up-aws-login.html) for help with these steps:
    * Sign up for an AWS account.
    * Create a user with permissions to use Amazon GameLift Servers.
    * Set up programmatic access with long-term IAM credentials.
* A source-built version of the Unreal Engine editor. You need a source-built editor to package a multiplayer game server build. See these Unreal Engine documentation topics:
    * [Accessing Unreal Engine source code on GitHub](https://www.unrealengine.com/ue-on-github) (requires GitHub and Epic Games accounts).
    * [Building Unreal Engine from Source](https://docs.unrealengine.com/5.3/en-US/building-unreal-engine-from-source/)
* A multiplayer game project with C++ game code. (Blueprint-only projects aren’t compatible with the plugin.) If you don’t have a project in progress, use one of the Unreal Engine sample games such as the [Third Person Template](https://dev.epicgames.com/documentation/en-us/unreal-engine/third-person-template-in-unreal-engine).
* [Microsoft Visual Studio](https://visualstudio.microsoft.com/vs/) 2019 or newer.
* [Unreal Engine cross-compiling toolchain](https://dev.epicgames.com/documentation/en-us/unreal-engine/linux-development-requirements-for-unreal-engine#cross-compiletoolchain). This tool is required only if you’re building a Linux game server.

### Step 2: Get the plugin

1. Download the plugin from the repository’s [**Releases**](https://github.com/aws/amazon-gamelift-plugin-unreal/releases) page. Download either the plugin (to use as is) or the plugin source files (if you want to customize it).
2. Unzip the plugin download. It contains two zip files:

    * The plugin for Unreal Engine (`amazon-gamelift-plugin-unreal-release-<version>.zip`)
    * The C++ server SDK for Amazon GameLift Servers ( `GameLift-Cpp-ServerSDK.zip`)

1. Unzip the plugin files and verify that all files were extracted. The destination folder will have the following structure:
   `amazon-gamelift-plugin-unreal-release-{version}\amazon-gamelift-plugin-unreal-{version}-sdk-{version}\amazon-gamelift-plugin-unreal\GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\{Linux \ Win64}`

### Step 3: Build the C++ server SDK for Unreal

The server SDK contains functionality that your deployed game server needs to communicate with the Amazon GameLift Servers service. In this step, you need to build C++ server SDK libraries for Unreal and to match your game server’s runtime environment.

* If you’re creating a Windows game server, build the server SDK for Windows only.
* If you’re creating a Linux game server with the Unreal Engine cross-compiling toolchain, build the server SDK for both Windows and Linux.

For additional information on CMake options, see the readme in the C++ server SDK files.

#### For Windows servers

1. Unzip the `GameLift-Cpp-ServerSDK.zip` file from the plugin download (see Step 2). Verify that all files were extracted.
2. Open a terminal or command prompt and navigate to the folder where you extracted the server SDK zip file.
3. Run the following commands. In the `cmake` command, specify your version of Visual Studio (see [cmake-generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators) for a list of valid strings).

```
mkdir out
cd out
cmake -G "Visual Studio 17 2022" -DBUILD_FOR_UNREAL=1 ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Release 
```

This step produces the following binary files. These files are required by the plugin.

    prefix\bin\aws-cpp-sdk-gamelift-server.dll
    prefix\lib\aws-cpp-sdk-gamelift-server.lib

1. Locate your plugin folder (where you extracted the plugin files in Step 2), and copy these files to this file path:
   `...\GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\Win64\`

When complete, your  you should have two filepaths similar to this example

    GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.dll
    GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.lib

#### For Linux servers

For a quick and easy automated build for Amazon Linux 2023, see [Building the Amazon GameLift Server SDK for Unreal Engine 5 on Amazon Linux.](https://github.com/aws/amazon-gamelift-toolkit/tree/main/building-gamelift-server-sdk-for-unreal-engine-and-amazon-linux) If you’re developing a Linux server on a Windows environment, this process provides complete descriptions on how to set up the plugin with the Unreal Engine cross-compiling toolchain.

### Step 4: Add the plugin to your Unreal game project

1. Locate the plugin folder for Unreal (created in Step 2) and open the subfolder
   `...\GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\{Linux \ Win64}`

   Verify that the folder includes the `aws-cpp-sdk-gamelift-server` libraries (as described in Step 3).
2. Locate your Unreal game project root folder. Look for a subfolder called `Plugins`. If it doesn’t exist, create it.
3. Copy the entire contents of `\GameLiftPlugin\` into the `Plugins` folder.
4. Open the `.uproject` file for your game project. Go to the `Plugins` section and add the following code:

```
"Plugins": [
{
    "Name": "GameLiftPlugin",
    "Enabled": true
},
{
    "Name": "WebBrowserWidget",
    "Enabled": true
}
```

1. In a file browser, select the game project `.uproject` file and choose the option **Switch Unreal Engine Version**. Set the game project to use the source-built Unreal Editor (as mentioned in Step 1).
2. (Windows) In the game project root folder, look for a solution ( `*.sln`) file. If none exists, select the `.uproject` file and choose the option to generate project files. Open the solution file and build or rebuild the project.
3. Open the game project in your Unreal Editor. If you already have the editor open, you might need to restart it before it recognizes the new plugin.
4. Verify that the plugin is installed. Check the main editor toolbar for the new Amazon GameLift menu button. Look in the Content Browser for the Amazon GameLift Servers plugin assets. (Make sure that **View Options** has the **Show Plugin Content** option selected.)

## Troubleshoot installation

#### Issue: When extracting the plugin files or server SDK files from the downloaded zip file, I get a `path too long` error.

Resolution: Some of the plugin files have very long paths and filenames. To resolve this issue, retry extracting the files and choose a destination folder that’s closer to the root directory. Alternatively, you might be able to shorten the destination folder name.

#### Issue: When rebuilding your game project’s solution file after adding the plugin (Windows), I get a  `No such file or directory` error for files in the `aws/gamelift/server/model/` path.

Resolution: This issue is likely caused by very long file paths to the server SDK header files. Sometimes zip tools silently skip files if the file path lenth exceeds a limit. To resolve this issue, retry extracting the files and choose a destination folder that’s closer to the root directory. Alternatively, you might be able to shorten the destination folder name.

#### Issue: I need to remove a successfully installed plugin or recover from a failed installation.

Resolution: To remove plugin components from your Unreal Editor, undo the tasks in [Step 4: Add the plugin to your Unreal game project](https://quip-amazon.com/asQ7Avytfm5d/Github-readme-for-Unreal-plugin#temp:C:eYe8deeb97a93aa4cce97c6e016d).

## Next steps: Get started with the plugin

See these Amazon GameLift Servers documentation topics for help with plugin features.

* [Set up an AWS account and user profile](https://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin-profiles.html)
* [Integrate the server SDK into your game server code and package your game build](https://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin-anywhere.html#unreal-plugin-anywhere-integrate)
* [Deploy your game with an Anywhere fleet](https://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin-anywhere.html)
* [Deploy your game with a managed EC2 fleet](https://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin-ec2.html)
* [Deploy your game with a managed container fleet](https://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin-container.html)

## Additional resources

* [About Amazon GameLift Servers](http://aws.amazon.com/gamelift/servers)
* [AWS Game Tech forum](https://repost.aws/topics/TAo6ggvxz6QQizjo9YIMD35A/game-tech/c/amazon-gamelift)
* [AWS for Games blog](https://aws.amazon.com/blogs/gametech/)
* [Amazon GameLift toolkit](https://github.com/aws/amazon-gamelift-toolkit)
* [Contributing guidelines](https://github.com/aws/amazon-gamelift-plugin-unreal/blob/main/CONTRIBUTING.md)

## Instructions for contributors

If you’re interested in contributing to the Amazon GameLift plugin, clone the source code from the GitHub repository and follow these instructions.

1. Download the following items from the Amazon GameLift Servers [Getting Started](https://aws.amazon.com/gamelift/getting-started/) page.
    1. C++ Server SDK Plugin for Unreal
    2. C++ Server SDK
2. Copy the source code for the C++ Server SDK Plugin for Unreal into the following folder:
   `amazon-gamelift-plugin-unreal-release-<version>/amazon-gamelift-plugin-unreal/GameLiftPlugin/Source/GameLiftServer/`.
3. The `REPLACEME.md` inside the directory details what the file structure should look like.
4. Delete the `GameLiftServerSDK.uplugin` from the same directory.
5. Open the file `amazon-gamelift-plugin-unreal/GameLiftPlugin/Source/GameLiftServer/Source/GameLiftServerSDK/Private/GameLiftServerSDK.cpp`. and make the following change:
    1. Change line 30 and 31 from

```
FString BaseDir = IPluginManager::Get().FindPlugin("GameLiftServerSDK")->GetBaseDir();
const FString SDKDir = FPaths::Combine(*BaseDir, TEXT("ThirdParty"), TEXT("GameLiftServerSDK"));
```

to

```
FString BaseDir = IPluginManager::Get().FindPlugin("GameLiftPlugin")->GetBaseDir();
const FString SDKDir = FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("GameLiftServer"), TEXT("ThirdParty"), TEXT("GameLiftServerSDK"));
```
