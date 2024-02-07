param(
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $LightWeightUnrealServerSdkVersion
)

$ROOT_DIR=Resolve-Path "$PSScriptRoot\..\.."
$SOURCE_DIR="$ROOT_DIR\GameLiftPlugin\Source"
$SERVER_SDK_DIR="GameLift-Cpp-ServerSDK-UnrealPlugin-$LightWeightUnrealServerSdkVersion";
$SERVER_SDK_FILENAME="$SERVER_SDK_DIR.zip";
$DESTINATION_PATH="$SOURCE_DIR\GameLiftServer"
$TEMP_PATH="C:\Temp\AmazonGameLiftPluginUnreal"
$TEMP_ZIP_PATH="$TEMP_PATH\$SERVER_SDK_FILENAME"
$TEMP_EXTRACTED_PATH="$TEMP_PATH\GameLiftServer"
$ITEMS_TO_COPY_PATH="$TEMP_EXTRACTED_PATH\GameLiftServerSDK\*"
$SERVER_SDK_S3_LINK_PREFIX="https://gamelift-server-sdk-release.s3.us-west-2.amazonaws.com/unreal"
$SERVER_SDK_S3_DOWNLOAD_LINK="$SERVER_SDK_S3_LINK_PREFIX/$SERVER_SDK_FILENAME"
$LICENSE_FILE_PATH="$TEMP_EXTRACTED_PATH\GameLiftServerSDK\LICENSE_AMAZON_GAMELIFT_SDK.TXT"


Write-Host "Preparing Lightweight Server SDK for Unreal download and extraction..."
if (-Not (Test-Path -Path $TEMP_ZIP_PATH) )
{
	New-Item -Force -Type Directory -Path $TEMP_PATH -ErrorAction Stop
	Write-Host "Downloading Lightweight Server SDK for Unreal $LightWeightUnrealServerSdkVersion..."
	# Download link should be public and require no credentials
	iwr $SERVER_SDK_S3_DOWNLOAD_LINK -OutFile $TEMP_ZIP_PATH
}
else
{
	Write-Host "Lightweight Server SDK for Unreal zip is already downloaded and stored at $TEMP_ZIP_PATH, skipping download."
}
if (Test-Path -Path $TEMP_EXTRACTED_PATH)
{
	Write-Host "Lightweight Server SDK for Unreal zip has already been unpacked at $DESTINATION_PATH, skipping unpack" -ForegroundColor DarkYellow
}
else
{
	Expand-Archive -Force -LiteralPath $TEMP_ZIP_PATH -DestinationPath $TEMP_EXTRACTED_PATH -ErrorAction Stop
	Remove-Item -Force -LiteralPath $LICENSE_FILE_PATH -ErrorAction Stop
}
Write-Host "Importing Lightweight Server SDK for Unreal source into $DESTINATION_PATH"
New-Item -Force -Type Directory -Path $DESTINATION_PATH -ErrorAction Stop
Write-Host "Removing any existing items in $DESTINATION_PATH so that extra files do not get pacakged into the Lightweight Server SDK for Unreal directory"
Remove-Item "$DESTINATION_PATH\*" -Recurse -Force
Copy-Item -Path $ITEMS_TO_COPY_PATH -Destination $DESTINATION_PATH -Recurse -Force

exit 0