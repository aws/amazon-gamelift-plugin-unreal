# Amazon GameLift Plugin for Unreal Engine

![GitHub](https://img.shields.io/github/license/aws/amazon-gamelift-plugin-unreal)
![GitHub latest release version (by date)](https://img.shields.io/github/v/release/aws/amazon-gamelift-plugin-unreal)
![GitHub downloads all releases](https://img.shields.io/github/downloads/aws/amazon-gamelift-plugin-unreal/total)
![GitHub downloads latest release (by date)](https://img.shields.io/github/downloads/aws/amazon-gamelift-plugin-unreal/latest/total)

Compatible with Unreal Engine 5 (versions 5.0, 5.1, 5.2 and 5.3).

## Install the plugin

Complete the following steps to install and enable the plugin for your multiplayer game project. For more details, see the [AWS GameLift documentation](https://docs.aws.amazon.com/gamelift/latest/developerguide/unreal-plugin.html).

1. Build the Amazon GameLift C++ Server SDK. See section below for details.

1. Install and enable the plugin.
    1. In your game project root folder, open the `Plugins` folder and copy the Amazon GameLift plugin files.
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

Before you can use the plugin inside an Unreal game, you need to build the Amazon GameLift C++ Server SDK.  

To build the Amazon GameLift C++ Server SDK:
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

For more detailed instructions on how to build the C++ Server SDK, please refer to the README.md file located in the C++ Server SDK directory.