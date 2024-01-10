param(
	[Parameter(Mandatory)]
	[Alias("ServerSdk", "SdkVersion", "Sdk")]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $ServerSdkVersion,
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $PluginVersion
)

$ROOT_DIR=Resolve-Path "$PSScriptRoot\..\..\.."
$BUILD_DIR="$ROOT_DIR\GameLiftPlugin\build"
$STAGING_PATH="$BUILD_DIR\staging-release"
$README_PATH=Resolve-Path "$PSScriptRoot\..\PACKAGE_FOR_RELEASE.md"
$PLUGIN_PATH="$BUILD_DIR\amazon-gamelift-plugin-unreal-$PluginVersion-sdk-$ServerSdkVersion.zip"
$CPP_SERVER_SDK_PATH="$BUILD_DIR\GameLift-Cpp-ServerSDK-$ServerSdkVersion.zip"
$DESTINATION_PATH="$BUILD_DIR\amazon-gamelift-plugin-unreal-release-$PluginVersion.zip"

Write-Host "Staging files for release..."
New-Item -Force -Type Directory -Path $STAGING_PATH -ErrorAction Stop
Move-Item -Force -LiteralPath $CPP_SERVER_SDK_PATH, $PLUGIN_PATH -Destination $STAGING_PATH -ErrorAction Stop
Copy-Item -Force -LiteralPath $README_PATH -Destination "$STAGING_PATH\README.md" -ErrorAction Stop
Write-Host "Packaging zip file for release..."
Compress-Archive -Force -Path "$STAGING_PATH\*" -DestinationPath $DESTINATION_PATH -ErrorAction Stop
Write-Host "Packaging successful! Release artifact located at '$DESTINATION_PATH'" -ForegroundColor Green
exit 0