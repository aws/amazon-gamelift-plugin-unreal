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
$RELEASE_NOTES_PATH="$DESTINATION_PATH\Release-notes"
$TEMP_PATH="C:\Temp\AmazonGameLiftPluginUnreal"
$TEMP_ZIP_PATH="$TEMP_PATH\$SERVER_SDK_FILENAME"
$TEMP_PLUGIN_PATH="$TEMP_PATH\amazon-gamelift-plugin-unreal"
$TEMP_EXTRACTED_PATH="$TEMP_PATH\GameLiftServer"
$ITEMS_TO_COPY_PATH="$TEMP_EXTRACTED_PATH\GameLiftServerSDK\*"
$SERVER_SDK_S3_LINK_PREFIX="https://gamelift-server-sdk-release.s3.us-west-2.amazonaws.com/unreal"
$SERVER_SDK_S3_DOWNLOAD_LINK="$SERVER_SDK_S3_LINK_PREFIX/$SERVER_SDK_FILENAME"
$PACKAGED_ZIP_PATH="$BUILD_DIR\amazon-gamelift-plugin-unreal-$PluginVersion-sdk-$LightWeightUnrealServerSdkVersion.zip"
$LICENSE_FILE_PATH="$TEMP_EXTRACTED_PATH\GameLiftServerSDK\LICENSE_AMAZON_GAMELIFT_SDK.TXT"

if (Test-Path -Path $PACKAGED_ZIP_PATH)
{
	Write-Host "Amazon GameLift Unreal Plugin zip has already been prepared, skipping packaging." -ForegroundColor DarkYellow
	exit 0
}

Write-Host "Preparing Lightweight Unreal Server SDK for Unreal download and extraction..."
if (-Not (Test-Path -Path $TEMP_ZIP_PATH) )
{
	New-Item -Force -Type Directory -Path $TEMP_PATH -ErrorAction Stop
	Write-Host "Downloading C++ Server SDK Plugin for Unreal $LightWeightUnrealServerSdkVersion..."
	# Download link should be public and require no credentials
	iwr $SERVER_SDK_S3_DOWNLOAD_LINK -OutFile $TEMP_ZIP_PATH
}
else
{
	Write-Host "Lightweight Unreal Server SDK for Unreal zip is already downloaded and stored at $TEMP_ZIP_PATH, skipping download."
}
if (Test-Path -Path $RELEASE_NOTES_PATH)
{
	Write-Host "Lightweight Unreal Server SDK for Unreal zip has already been unpacked at $DESTINATION_PATH, skipping unpack" -ForegroundColor DarkYellow
}
else
{
	Write-Host "Extracting into project directory..."
	Expand-Archive -Force -LiteralPath $TEMP_ZIP_PATH -DestinationPath $TEMP_EXTRACTED_PATH -ErrorAction Stop
	Remove-Item -Force -LiteralPath $LICENSE_FILE_PATH -ErrorAction Stop
	New-Item -Force -Type Directory -Path $DESTINATION_PATH -ErrorAction Stop
	Copy-Item -Path $ITEMS_TO_COPY_PATH -Destination $DESTINATION_PATH -Recurse
}
exit 0