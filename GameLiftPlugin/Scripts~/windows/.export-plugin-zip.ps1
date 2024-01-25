param(
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $LightWeightUnrealServerSdkVersion,
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $PluginVersion
)

$ROOT_DIR=Resolve-Path "$PSScriptRoot\..\..\.."
$SOURCE_DIR="$ROOT_DIR\GameLiftPlugin\Source"
$BUILD_DIR="$ROOT_DIR\GameLiftPlugin\build"
$SERVER_SDK_DIR="GameLift-Cpp-ServerSDK-UnrealPlugin-$LightWeightUnrealServerSdkVersion";
$SERVER_SDK_FILENAME="$SERVER_SDK_DIR.zip";
$DESTINATION_PATH="$SOURCE_DIR\GameliftServer"
$TEMP_PATH="C:\Temp\AmazonGameLiftPluginUnreal"
$TEMP_ZIP_PATH="$TEMP_PATH\$SERVER_SDK_FILENAME"
$TEMP_PLUGIN_PATH="$TEMP_PATH\amazon-gamelift-plugin-unreal"
$TEMP_EXTRACTED_PATH="$TEMP_PATH\GameLiftServer"
$ITEMS_TO_COPY_PATH="$TEMP_EXTRACTED_PATH\GameLiftServerSDK\*"
$SERVER_SDK_S3_LINK_PREFIX="https://gamelift-server-sdk-release.s3.us-west-2.amazonaws.com/unreal"
$SERVER_SDK_S3_DOWNLOAD_LINK="$SERVER_SDK_S3_LINK_PREFIX/$SERVER_SDK_FILENAME"
$PACKAGED_ZIP_PATH="$BUILD_DIR\amazon-gamelift-plugin-unreal-$PluginVersion-sdk-$LightWeightUnrealServerSdkVersion.zip"
$LICENSE_FILE_PATH="$TEMP_EXTRACTED_PATH\GameLiftServerSDK\LICENSE_AMAZON_GAMELIFT_SDK.TXT"

New-Item -Force -Type Directory -Path $BUILD_DIR -ErrorAction Stop
if (Test-Path -Path $TEMP_PLUGIN_PATH)
{
	Write-Host "Amazon Gamelift Unreal plugin has already been copied to $TEMP_PLUGIN_PATH, skipping copy" -ForegroundColor DarkYellow
}
else
{
	New-Item -Force -Type Directory -Path $TEMP_PLUGIN_PATH -ErrorAction Stop
	Copy-Item -Path "$ROOT_DIR\*" -Destination $TEMP_PLUGIN_PATH -Recurse -Include *.md,GameLiftPlugin -ErrorAction Stop
}
Compress-Archive -Force -Path $TEMP_PLUGIN_PATH -DestinationPath $PACKAGED_ZIP_PATH -ErrorAction Stop
Write-Host "Amazon Gamelift Unreal plugin has been re-packaged without license file at $PACKAGED_ZIP_PATH" -ForegroundColor Yellow
exit 0