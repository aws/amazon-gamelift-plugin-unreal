# Amazon GameLift Plugin for Unreal Engine

![GitHub](https://img.shields.io/github/license/aws/amazon-gamelift-plugin-unreal)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/aws/amazon-gamelift-plugin-unreal)
![GitHub all releases](https://img.shields.io/github/downloads/aws/amazon-gamelift-plugin-unreal/total)
![GitHub release (latest by date)](https://img.shields.io/github/downloads/aws/amazon-gamelift-plugin-unreal/latest/total)

Compatible with Unreal Engine 5 (versions 5.0, 5.1, 5.2 and 5.3).

# Overview

Amazon GameLift is a fully managed service that allows game developers to manage and scale dedicated game servers for session-based multiplayer games. The Amazon GameLift plugin for Unreal Engine provides tools that makes setting up your Unreal project, compatible with UE 5.0, 5.1, 5.2 and 5.3, for hosting on Amazon GameLift quicker and easier. Once installed, you will be able to search the plugin from within the Unreal Engine editor and start using it to integrate Amazon GameLift functionality into your client and server code. The plugin contains functionality to automatically bootstrap your game runtime environment to the AWS Cloud, fully test your game server integration with Amazon GameLift locally, and deploy your game servers on Amazon GameLift.

You can use the following built-in templates to deploy your game for some of the common scenarios.
* Single-region fleet: Deploy your game server to one fleet in a single AWS Region. Use this scenario to experiment with your install scripts and runtime deployment, as well as your integration.
* FlexMatch fleet: Deploy your game server for hosting with a FlexMatch matchmaking solution. [Amazon GameLift's FlexMatch](https://docs.aws.amazon.com/gamelift/latest/flexmatchguide/match-intro.html) is a highly scalable and customizable matchmaking service for multiplayer games. Use this scenario to set up basic matchmaking components (including a rule set) that you can customize.

Each scenario uses an AWS CloudFormation template to  deploy your game, creating a stack with the necessary resources. You can view and manage your resource stacks in the AWS Management Console for CloudFormation.

- [Prerequisites](#prerequisites)
- [Install the plugin](#install-the-plugin)
- [Amazon GameLift resources](#amazon-gamelift-resources)

## Prerequisites

* Amazon GameLift plugin for Unreal download package. Download a zip file from [the GitHub Releases page](https://github.com/aws/amazon-gamelift-plugin-unreal/releases). Or clone the plugin from the [Github repo](https://github.com/aws/amazon-gamelift-plugin-unreal).
* If you cloned the repo you will also need to download the following items from [Amazon GameLift's Getting Started](https://aws.amazon.com/gamelift/getting-started/). Otherwise, if you downloaded the zip file from [the GitHub Releases page](https://github.com/aws/amazon-gamelift-plugin-unreal/releases), you can skip this step.
    * C++ Server SDK Plugin for Unreal
    * C++ Server SDK
* If you cloned the repo instead of downloading the zip from [the GitHub Releases page](https://github.com/aws/amazon-gamelift-plugin-unreal/releases), copy the source code for C++ Server SDK Plugin for Unreal into the folder `amazon-gamelift-plugin-unreal-release-<version>/amazon-gamelift-plugin-unreal/GameLiftPlugin/Source/GameLiftServer/`. The `REPLACEME.md` inside the directory details what the file structure should look like. Delete the `GameLiftServerSDK.uplugin` from the same directory. Then make the following code change to `amazon-gamelift-plugin-unreal/GameLiftPlugin/Source/GameLiftServer/Source/GameLiftServerSDK/Private/GameLiftServerSDK.cpp`. Change line 30 and 31 from
```
FString BaseDir = IPluginManager::Get().FindPlugin("GameLiftServerSDK")->GetBaseDir();
const FString SDKDir = FPaths::Combine(*BaseDir, TEXT("ThirdParty"), TEXT("GameLiftServerSDK"));
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;to
```
FString BaseDir = IPluginManager::Get().FindPlugin("GameLiftPlugin")->GetBaseDir();
const FString SDKDir = FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("GameLiftServer"), TEXT("ThirdParty"), TEXT("GameLiftServerSDK"));
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;If you downloaded the zip file from [the GitHub Releases page](https://github.com/aws/amazon-gamelift-plugin-unreal/releases), you can skip this step.
* Microsoft Visual Studio 2019 or newer.
* A source-built version of the Unreal Engine editor. Required to develop server build components for a multiplayer game. See the Unreal Engine documentation:
    * [Accessing Unreal Engine source code on GitHub](https://www.unrealengine.com/ue-on-github). Requires  GitHub and Epic Games accounts.
    * [Building Unreal Engine from Source](https://docs.unrealengine.com/5.3/en-US/building-unreal-engine-from-source/)
* (Optional) A C++ multiplayer game project with game code. Projects that use Blueprints only are not compatible with this plugin, at this time.
* An AWS account with access permissions to use AWS GameLift. See [Set up programmatic access](https://docs.aws.amazon.com/gamelift/latest/developerguide/setting-up-aws-login.html) with long-term credentials.

## Install the plugin

Complete the following steps to install and enable the plugin for your multiplayer game project. For more details, see the [AWS GameLift documentation](https://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin.html).

1. Build the Amazon GameLift C++ Server SDK. See section below for details.

1. Install and enable the plugin.
    1. In your game project root folder, create a folder called "Plugins" and copy the "GameLiftPlugin" folder located inside the downloaded Amazon GameLift plugin into this new folder.
    1. In the `.uproject` file, add the following to the `Plugins` section:

        ```
        {
            "Name": "GameLiftPlugin",
            "Enabled": true
        },
        {
            "Name": "WebBrowserWidget",
            "Enabled": true
        }
        ```
1. Set your project to use the source-built UE editor. Do this step if your game project was created with a non-source-built version of UE. In your game project folder, select the `.uproject` file and choose the option **Switch Unreal Engine Version**.

1. Rebuild the project solution. After completing the previous steps to update your project files, rebuild the solution.

## Build the Amazon GameLift C++ Server SDK

Before you can use the plugin inside an Unreal game, you need to build the Amazon GameLift server C++ SDK.

To build the Amazon GameLift server SDK:
1. Open a terminal/command prompt.
1. Navigate to the `GameLift-Cpp-ServerSDK-<version>` folder that was included with the Amazon GameLift SDK Release download.
1. Follow the below instructions for your platform.

### Linux

1. Run the following commands
    ```sh
    mkdir out
    cd out
    cmake -DBUILD_FOR_UNREAL=1 ..
    make
    ```
1. Once complete, the following file should have been built
    ```
    prefix/lib/aws-cpp-sdk-gamelift-server.so
    ```
1. Copy the file over to the following location in the Unreal plugin folder:
    ```
    GameLiftPlugin/Source/GameLiftServer/ThirdParty/GameLiftServerSDK/Linux/x86_64-unknown-linux-gnu/
    ```  
   Once complete you should have a filepath similar to this example
    ```
    GameLiftPlugin/Source/GameLiftServer/ThirdParty/GameLiftServerSDK/Linux/x86_64-unknown-linux-gnu/aws-cpp-sdk-gamelift-server.so 
    ```

### Windows

1. Run the following commands
    ```sh
    mkdir out
    cd out
    cmake -G "Visual Studio 17 2022" -DBUILD_FOR_UNREAL=1 ..
    msbuild ALL_BUILD.vcxproj /p:Configuration=Release
    ```
1. The above step produces the following binary files required by the plugin.
    ```
    prefix\bin\aws-cpp-sdk-gamelift-server.dll  
    prefix\lib\aws-cpp-sdk-gamelift-server.lib
    ```
1. Copy the files over to this location in the Unreal plugin folder:
    ```
    GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\Win64\
    ```  
   Once complete you should have two filepaths similar to this example
    ```
    GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.dll  
    GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.lib 
    ```

For more detailed instructions on how to build the C++ SDK,, please refer to the README.md file located in the C++ SDK directory.

## Amazon GameLift Resources

* [About Amazon GameLift](https://aws.amazon.com/gamelift/)
* [Amazon GameLift documentation](https://docs.aws.amazon.com/gamelift/)
* [AWS Game Tech forum](https://repost.aws/topics/TAo6ggvxz6QQizjo9YIMD35A/game-tech/c/amazon-gamelift)
* [AWS for Games blog](https://aws.amazon.com/blogs/gametech/)
* [Contributing guidelines](CONTRIBUTING.md)
