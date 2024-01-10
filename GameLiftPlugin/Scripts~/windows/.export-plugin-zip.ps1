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
$SOURCE_DIR="$ROOT_DIR\GameLiftPlugin\Source"
$BUILD_DIR="$ROOT_DIR\GameLiftPlugin\build"
$SERVER_SDK_DIR="GameLift-Cpp-ServerSDK-UnrealPlugin-$ServerSdkVersion";
$SERVER_SDK_FILENAME="$SERVER_SDK_DIR.zip";
$DESTINATION_PATH="$SOURCE_DIR\GameliftServer"
$TEMP_PATH="C:\Temp\AmazonGameLiftPluginUnreal"
$TEMP_ZIP_PATH="$TEMP_PATH\$SERVER_SDK_FILENAME"
$TEMP_PLUGIN_PATH="$TEMP_PATH\amazon-gamelift-plugin-unreal"
$TEMP_EXTRACTED_PATH="$TEMP_PATH\GameLiftServer"
$ITEMS_TO_COPY_PATH="$TEMP_EXTRACTED_PATH\GameLiftServerSDK\*"
$SERVER_SDK_S3_LINK_PREFIX="https://gamelift-server-sdk-release.s3.us-west-2.amazonaws.com/unreal"
$SERVER_SDK_S3_DOWNLOAD_LINK="$SERVER_SDK_S3_LINK_PREFIX/$SERVER_SDK_FILENAME"
$PACKAGED_ZIP_PATH="$BUILD_DIR\amazon-gamelift-plugin-unreal-$PluginVersion-sdk-$ServerSdkVersion.zip"
$LISCENSE_FILE_PATH="$TEMP_EXTRACTED_PATH\GameLiftServerSDK\LICENSE_AMAZON_GAMELIFT_SDK.TXT"

if (Test-Path -Path $PACKAGED_ZIP_PATH)
{
	Write-Host "Amazon GameLift Server SDK zip has already been prepared, skipping download and extraction." -ForegroundColor DarkYellow
	exit 0
}

Write-Host "Preparing Amazon GameLift Server SDK download and extraction..."
if (-Not (Test-Path -Path $TEMP_ZIP_PATH) )
{
	New-Item -Force -Type Directory -Path $TEMP_PATH -ErrorAction Stop
	Write-Host "Downloading Amazon GameLift Server SDK $ServerSdkVersion..."
	# Download link should be public and require no credentials
	iwr $SERVER_SDK_S3_DOWNLOAD_LINK -OutFile $TEMP_ZIP_PATH
}
else
{
	Write-Host "Amazon GameLift Server SDK is already downloaded and stored at $TEMP_ZIP_PATH, skipping download."
}
if (Test-Path -Path $DESTINATION_PATH)
{
	Write-Host "Amazon GameLift Server SDK zip has already been unpacked at $DESTINATION_PATH, skipping unpack" -ForegroundColor DarkYellow
}
else
{
	Write-Host "Extracting into project directory..."
	Expand-Archive -Force -LiteralPath $TEMP_ZIP_PATH -DestinationPath $TEMP_EXTRACTED_PATH -ErrorAction Stop
	Remove-Item -Force -LiteralPath $LISCENSE_FILE_PATH -ErrorAction Stop
	New-Item -Force -Type Directory -Path $DESTINATION_PATH -ErrorAction Stop
	Copy-Item -Path $ITEMS_TO_COPY_PATH -Destination $DESTINATION_PATH -Recurse
}
Write-Host "Re-packaging Server SDK zip into project directory..."
New-Item -Force -Type Directory -Path $BUILD_DIR -ErrorAction Stop
if (Test-Path -Path $TEMP_PLUGIN_PATH)
{
	Write-Host "Amazon GameLift Server SDK zip has already been copied to $TEMP_PLUGIN_PATH, skipping copy" -ForegroundColor DarkYellow
}
else
{
	New-Item -Force -Type Directory -Path $TEMP_PLUGIN_PATH -ErrorAction Stop
	Copy-Item -Path "$ROOT_DIR\*" -Destination $TEMP_PLUGIN_PATH -Recurse -Include *.md,GameLiftPlugin -ErrorAction Stop
}
Compress-Archive -Force -Path $TEMP_PLUGIN_PATH -DestinationPath $PACKAGED_ZIP_PATH -ErrorAction Stop
Write-Host "Amazon GameLift Server SDK has been re-packaged without license file at $PACKAGED_ZIP_PATH" -ForegroundColor Yellow
exit 0