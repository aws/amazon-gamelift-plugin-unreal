# GameLiftServerSDK Unreal Plugin
## Documention
You can find the official Amazon GameLift documentation [here](https://aws.amazon.com/documentation/gamelift/).

## Building Unreal from Source
The standard version of Unreal Engine download through the Epic launcher only allows for Unreal client application builds. In order to build an Unreal server application, you need to download and build the Unreal Engine from the Epic Games Git repo.
1. Follow the instructions [here](https://www.unrealengine.com/en-US/ue-on-github) to link your GitHub account to your Epic Games account 
1. Run the following command to clone your desired branch
    ```
    git clone -b <branch> --single-branch https://github.com/EpicGames/UnrealEngine.git
    ```
    For example, to clone the 5.1.0-release branch  
    ```
    git clone -b 5.1.0-release --single-branch https://github.com/EpicGames/UnrealEngine.git
    ```
1. Run `setup.bat` from the repo root folder
1. Run `generateFiles.bat` from the repo root folder
1. Open up the UE5.sln file in Visual Studio and build the UE5 project with Development Editor Win64 target.  
    * Be aware that building this solution can take over an hour

## Creating a new Amazon GameLift example project for Unreal
1. Run the Development Editor for UE5 project from the UE5.sln with VisualStudio.
1. Once loaded, select a New Third Person Project with the following:
    * C++
    * With starter content
    * Desktop  
    * For our examples we will name our project `GameLiftUnrealApp`
1. If using Visual Studio, this will open another instance of Visual Studio. You can close this and the Visual Studio instance you were using with the Unreal Engine Source.
1. Navigate to the location of your new third person example. Find the Source folder and file named `<Your application name>.Target.cs`
    * For our example this will be `GameLiftUnrealApp.Target.cs`
1. Copy this file and name it `<Your application name>Server.Target.cs`
    * In our case `GameLiftUnrealAppServer.Target.cs`
1. Open this newly copied file and the following changes
    * Change the `class` and `constructor` to match the filename
    * Change the `Type` from `TargetType.Game` to `TargetType.Server`
    * The final file will look like the following for our example app. There might be some differences, however that's fine as long as the above changes were made. 
    ```csharp
    public class GameLiftUnrealAppServerTarget : TargetRules
    {  
        public GameLiftUnrealAppServerTarget(TargetInfo Target) : base(Target)
        {
            Type = TargetType.Server;
            DefaultBuildSettings = BuildSettingsVersion.V2;
            IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
            ExtraModuleNames.Add("GameLiftUnrealApp");
        }
    }
    ```
1. Keep the location of your new third person example app in mind, you will need it later in this document.

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
1. Copy the file over to this location in the Unreal plugin folder 
    ```
    ../../GameLift-Unreal-plugin-<version>/GameLiftServerSDK/ThirdParty/GameLiftServerSDK/Linux/x86_64-unknown-linux-gnu/
    ```  
    Once complete you should have a filepath similar to this example
    ```
    ../../GameLift-Unreal-plugin-5.0.2/GameLiftServerSDK/ThirdParty/GameLiftServerSDK/Linux/x86_64-unknown-linux-gnu/aws-cpp-sdk-gamelift-server.so 
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
1. Copy the files over to this location in the Unreal plugin folder 
    ```
    ..\..\GameLift-Unreal-plugin-<version>\GameLiftServerSDK\ThirdParty\GameLiftServerSDK\Win64\
    ```  
    Once complete you should have two filepaths similar to this example  
    ```
    ..\..\GameLift-Unreal-plugin-5.0.2\GameLiftServerSDK\ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.dll  
    ..\..\GameLift-Unreal-plugin-5.0.2\GameLiftServerSDK\ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.lib 
    ```

At this point, we are ready to add the plugin to an Unreal game project and start using it.

For more detailed instructions on how to build the C++ SDK, please refer to the README.md file located in the C++ SDK directory.

### Import the plugin into the example project
There are multiple ways to import an Unreal plugin. The method shown below doesn't require use of the Unreal Editor.

1. First, we'll want to add the GameLiftServerSDK plugin to the game's `.uproject` file.  
    * *From the example above, remember our app is called `GameLiftUnrealApp`, so the file will be `GameLiftUnrealApp.uproject`*  
1. Add the following entry to the list of plugins
    ```sh
    "Plugins": [
        {
            "Name": "GameLiftServerSDK",
            "Enabled": true
        }
    ]
    ```
1. Next, we'll want to make sure the game's ModuleRules take a dependency on the plugin. By opening the `.Build.cs` file and adding the GameLiftServerSDK dependency.
    * This file is found in the in under `<Your application name>/Source/<Your application name>/`
    * For our example, the filepath is `../GameLiftUnrealApp/Source/GameLiftUnrealApp/GameLiftUnrealApp.Build.cs`  
1. Add `"GameLiftServerSDK"` to the end of the list of `PublicDependencyModuleNames`
    ```csharp
    public class GameLiftUnrealApp : ModuleRules  
    {
      public GameLiftUnrealApp(TargetInfo Target)
      {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameLiftServerSDK" });
        bEnableExceptions = true;
      }
    }
    ```
1. The plugin should now be working for your application. Next you will need to initialize Amazon GameLift. See the next section for example code to do this.

### Example code
The code sample below showcases how to initialize a game server with Amazon GameLift. See the Amazon GameLift server integration guide for more details.
As we can see, the Amazon GameLift-specific code is dependent on the WITH_GAMELIFT preprocessor flag. This flag is true only when both of these conditions are met:
1. The plugins found the Amazon GameLift server SDK binaries.
1. Target.Type == TargetRules.TargetType.Server  

This means only Unreal Server builds will invoke Amazon GameLift's backend API. It also enables developers to write code that will execute properly for all the different Unreal Targets the game may produce.

1. Open the `.sln` file for your application, for our example this will be `GameLiftUnrealApp.sln` found in the root folder.
1. Once opened, find the file called `<Your application name>GameMode.h`, in our case `GameLiftUnrealAppGameMode.h`
1. Change the file to match our example below  
*Note the class name starts with an `A`*
    ```cpp
    #pragma once
    
    #include "CoreMinimal.h"
    #include "GameFramework/GameModeBase.h"
    #include "GameLiftServerSDK.h"
    #include "GameLiftUnrealAppGameMode.generated.h"
    
    DECLARE_LOG_CATEGORY_EXTERN(GameServerLog, Log, All);
    
    UCLASS(minimalapi)
    class AGameLiftUnrealAppGameMode : public AGameModeBase
    {
        GENERATED_BODY()
    
    public:
        AGameLiftUnrealAppGameMode();
    
    protected:
        virtual void BeginPlay() override;
    
    private:
        // Process Parameters needs to remain in scope for the lifetime of the app
        FProcessParameters m_params;
    
        void InitGameLift();
    };
    ```
1. Next open the related source file, `<Your application name>GameMode.cpp` file, in our case `GameLiftUnrealAppGameMode.cpp`, and change to match the following example
    ```cpp
    #include "GameLiftUnrealAppGameMode.h"
    #include "GameLiftUnrealAppCharacter.h"
    
    #include "UObject/ConstructorHelpers.h"
    
    DEFINE_LOG_CATEGORY(GameServerLog);
    
    AGameLiftUnrealAppGameMode::AGameLiftUnrealAppGameMode()
    {
        // set default pawn class to our Blueprinted character
        static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
        if (PlayerPawnBPClass.Class != NULL)
        {
            DefaultPawnClass = PlayerPawnBPClass.Class;
        }
    }
    
    void AGameLiftUnrealAppGameMode::BeginPlay()
    {
    #if WITH_GAMELIFT
        InitGameLift();
    #endif
    }
    
    void AGameLiftUnrealAppGameMode::InitGameLift()
    {
        UE_LOG(GameServerLog, Log, TEXT("Initializing the GameLift Server"));
    
        //Getting the module first.
        FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
    
        //Define the server parameters
        FServerParameters serverParameters;
    
        //AuthToken returned from the "aws gamelift get-compute-auth-token" API. Note this will expire and require a new call to the API after 15 minutes.
        if (FParse::Value(FCommandLine::Get(), TEXT("-authtoken="), serverParameters.m_authToken))
        {
            UE_LOG(GameServerLog, Log, TEXT("AUTH_TOKEN: %s"), *serverParameters.m_authToken)
        }
    
        //The Host/compute-name of the GameLift Anywhere instance.
        if (FParse::Value(FCommandLine::Get(), TEXT("-hostid="), serverParameters.m_hostId))
        {
            UE_LOG(GameServerLog, Log, TEXT("HOST_ID: %s"), *serverParameters.m_hostId)
        }
    
        //The EC2 or Anywhere Fleet ID.
        if (FParse::Value(FCommandLine::Get(), TEXT("-fleetid="), serverParameters.m_fleetId))
        {
            UE_LOG(GameServerLog, Log, TEXT("FLEET_ID: %s"), *serverParameters.m_fleetId)
        }
    
        //The WebSocket URL (GameLiftServiceSdkEndpoint).
        if (FParse::Value(FCommandLine::Get(), TEXT("-websocketurl="), serverParameters.m_webSocketUrl))
        {
            UE_LOG(GameServerLog, Log, TEXT("WEBSOCKET_URL: %s"), *serverParameters.m_webSocketUrl)
        }
    
        //The PID of the running process
        serverParameters.m_processId = FString::Printf(TEXT("%d"), GetCurrentProcessId());
        UE_LOG(GameServerLog, Log, TEXT("PID: %s"), *serverParameters.m_processId);
    
        //InitSDK will establish a local connection with GameLift's agent to enable further communication.
        gameLiftSdkModule->InitSDK(serverParameters);
    
        //When a game session is created, GameLift sends an activation request to the game server and passes along the game session object containing game properties and other settings.
        //Here is where a game server should take action based on the game session object.
        //Once the game server is ready to receive incoming player connections, it should invoke GameLiftServerAPI.ActivateGameSession()
        auto onGameSession = [=](Aws::GameLift::Server::Model::GameSession gameSession)
        {
            FString gameSessionId = FString(gameSession.GetGameSessionId());
            UE_LOG(GameServerLog, Log, TEXT("GameSession Initializing: %s"), *gameSessionId);
            gameLiftSdkModule->ActivateGameSession();
        };
    
        m_params.OnStartGameSession.BindLambda(onGameSession);
    
        //OnProcessTerminate callback. GameLift will invoke this callback before shutting down an instance hosting this game server.
        //It gives this game server a chance to save its state, communicate with services, etc., before being shut down.
        //In this case, we simply tell GameLift we are indeed going to shutdown.
        auto onProcessTerminate = [=]() 
        {
            UE_LOG(GameServerLog, Log, TEXT("Game Server Process is terminating"));
            gameLiftSdkModule->ProcessEnding();
        };
    
        m_params.OnTerminate.BindLambda(onProcessTerminate);
    
        //This is the HealthCheck callback.
        //GameLift will invoke this callback every 60 seconds or so.
        //Here, a game server might want to check the health of dependencies and such.
        //Simply return true if healthy, false otherwise.
        //The game server has 60 seconds to respond with its health status. GameLift will default to 'false' if the game server doesn't respond in time.
        //In this case, we're always healthy!
        auto onHealthCheck = []() 
        {
            UE_LOG(GameServerLog, Log, TEXT("Performing Health Check"));
            return true;
        };
    
        m_params.OnHealthCheck.BindLambda(onHealthCheck);
    
        //This game server tells GameLift that it will listen on port 7777 for incoming player connections.
        m_params.port = 7777;
    
        //Here, the game server tells GameLift what set of files to upload when the game session ends.
        //GameLift will upload everything specified here for the developers to fetch later.
        TArray<FString> logfiles;
        logfiles.Add(TEXT("GameLift426Test/Saved/Logs/GameLift426Test.log"));
        m_params.logParameters = logfiles;
    
        //Calling ProcessReady tells GameLift this game server is ready to receive incoming game sessions!
        UE_LOG(GameServerLog, Log, TEXT("Calling Process Ready"));
        gameLiftSdkModule->ProcessReady(m_params);
    }
    ```
1. Now you need to build your app for both of the following target types: `Development Editor` and `Development Server`  
  *Avoid doing a rebuild of the solution, instead build just the project under the "Games" folder that matches the name of your app. Otherwise Visual Studio will rebuild the UE5 project which might take up to an hour.*
1. Once both builds are complete, you can close Visual Studio, then open your app by double clicking the `.uproject` file
1. After the app loads, to package the server build of the app. Click on `Platforms > Windows > <Your application name>Server` to select the correct target (for our example: `Platforms > Windows > GameLiftUnrealAppServer`)
1. Now click on `Platforms > Windows > Package Project`, this will start the process of building the server application. Once complete you should have an executable, for the case of our example it will be named `GameLiftUnrealAppServer.exe`
  
### Running a cooked Unreal server on Amazon GameLift
When cooking an Unreal server build, the engine will produce two executables. One will be located in the root of the folder and will act as a wrapper for the actual server executable. Is it recommended that the actual server executable be passed in as the launch path when creating a fleet.
For example, I might have a GameLiftFPS.exe file at the root and another at \GameLiftFPS\Binaries\Win64\GameLiftFPSServer.exe. So, when creating a fleet, it is recommended to use C:\GameLiftFPS\Binaries\Win64\GameLiftFPSServer.exe as the launch path of the runtime configuration.

Make sure to open the necessary UDP ports on the Amazon GameLift Fleet so that the Server can communicate to the client. By default Unreal Engine uses port 7777. Follow this link for more information: https://docs.aws.amazon.com/gamelift/latest/apireference/API_UpdateFleetPortSettings.html

Include an install.bat file to setup preqrequiests on the fleet. Example install.bat file:

````
VC_redist.x64.exe /q
UE5PrereqSetup_x64.exe /q
````

### Do not forget your dependencies
When uploading your application to Amazon GameLift, **make sure you also include any dependencies** such as the OpenSSL DLLs that you built the Amazon GameLift SDK with:
```
libssl-3-x64.dll
libcrypto-3-x64.dll
```

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
