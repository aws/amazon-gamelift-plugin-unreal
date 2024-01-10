# GameLiftServerSDK Unreal Plugin
## Documention
You can find the official Amazon GameLift documentation [here](https://aws.amazon.com/documentation/gamelift/).


## Using the plugin
### Building the C++ SDK
Before we can use the plugin inside an Unreal game, we need to compile the Amazon GameLift server C++ SDK.  

To build the Amazon GameLift server SDK:
1. Open a terminal/command prompt.
2. Navigate to the `GameLift-Cpp-ServerSDK-<version>` folder that was included with the Amazon GameLift SDK Release download.
1. Follow the below instructions for your platform.  

#### Linux

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
1. Copy the file over to this location in the Unreal plugin folder. Note if you choose to clone the plugin from repo, you need to download the C++ Server SDK Plugin for Unreal from [Amazon GameLift's Getting Started](https://aws.amazon.com/gamelift/getting-started/), then copy the unzipped GameLiftServerSDK folder under `GameLiftPlugin/Source/` and rename the folder `GameLiftServerSDK` to `GameLiftServer`. 
    ```
    GameLiftPlugin/Source/GameLiftServer/ThirdParty/GameLiftServerSDK/Linux/x86_64-unknown-linux-gnu/
    ```  
    Once complete you should have a filepath similar to this example
    ```
    GameLiftPlugin/Source/GameLiftServer/ThirdParty/GameLiftServerSDK/Linux/x86_64-unknown-linux-gnu/aws-cpp-sdk-gamelift-server.so 
    ```

#### Windows

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
1. Copy the files over to this location in the Unreal plugin folder. Note if you choose to clone the plugin from repo, you need to download the C++ Server SDK Plugin for Unreal from [Amazon GameLift's Getting Started](https://aws.amazon.com/gamelift/getting-started/), then copy the unzipped GameLiftServerSDK folder under `GameLiftPlugin/Source/` and rename the folder`GameLiftServerSDK` to `GameLiftServer`. 
    ```
    GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\Win64\
    ```  
    Once complete you should have two filepaths similar to this example  
    ```
    GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.dll  
    GameLiftPlugin\Source\GameLiftServer\ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.lib 
    ```

At this point, we are ready to add the plugin to an Unreal game project and start using it.

For more detailed instructions on how to build the C++ SDK, please refer to the README.md file located in the C++ SDK directory. For an overview of the GameLift Unreal plugin and how to install, please refer to the README.md in the amazon-gamelift-unreal-\<version>-sdk-\<version>.zip folder.


### Compatability Notes
Supported UE4 and UE5 Versions

------
4.22  
4.23  
4.24  
4.25  
4.26  
4.27   
5.1.0  
5.1.1   
