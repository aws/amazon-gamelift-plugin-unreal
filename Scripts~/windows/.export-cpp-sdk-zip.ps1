param(
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $ServerSdkVersion
)

$ROOT_DIR=Resolve-Path "$PSScriptRoot\..\.."
$BUILD_DIR="$ROOT_DIR\GameLiftPlugin\build"
$TEMP_PATH="C:\Temp\AmazonGameLiftPluginUnreal"
$TEMP_EXTRACTED_PATH="$TEMP_PATH\GameLiftCppServerSDK"
$CPP_SERVER_SDK_S3_LINK_PREFIX="https://gamelift-server-sdk-release.s3.us-west-2.amazonaws.com/cpp"
$CPP_SERVER_SDK_DIR="GameLift-Cpp-ServerSDK-$ServerSdkVersion";
$CPP_SERVER_SDK_FILENAME="$CPP_SERVER_SDK_DIR.zip";
$CPP_SERVER_SDK_S3_DOWNLOAD_LINK="$CPP_SERVER_SDK_S3_LINK_PREFIX/$CPP_SERVER_SDK_FILENAME"
$CPP_SERVER_SDK_DESTINATION_PATH="$BUILD_DIR\GameLift-Cpp-ServerSDK-$ServerSdkVersion.zip"
$CPP_SERVER_SDK_TEMP_ZIP_PATH="$TEMP_PATH\$CPP_SERVER_SDK_FILENAME"

if (Test-Path -Path $CPP_SERVER_SDK_DESTINATION_PATH)
{
	Write-Host "Amazon GameLift C++ Server SDK has already been downloaded and packaged, skipping download and extraction." -ForegroundColor DarkYellow
	exit 0
}
Write-Host "Preparing Amazon GameLift C++ Server SDK download and extraction..."
if (-Not (Test-Path -Path $CPP_SERVER_SDK_TEMP_ZIP_PATH) )
{
	Write-Host "Downloading Amazon GameLift C++ SDK $ServerSdkVersion..."
	# Download link should be public and require no credentials
	iwr $CPP_SERVER_SDK_S3_DOWNLOAD_LINK -OutFile $CPP_SERVER_SDK_TEMP_ZIP_PATH
}
else
{
	Write-Host "Amazon GameLift C++ Server SDK is already downloaded and stored at $CPP_SERVER_SDK_TEMP_ZIP_PATH, skipping download."
}
Write-Host "Removing license file..."
Expand-Archive -Force -LiteralPath $CPP_SERVER_SDK_TEMP_ZIP_PATH -DestinationPath $TEMP_EXTRACTED_PATH -ErrorAction Stop
Remove-Item -Force -LiteralPath "$TEMP_EXTRACTED_PATH\LICENSE_AMAZON_GAMELIFT_SDK.TXT" -ErrorAction Stop
Write-Host "Re-packaging Amazon GameLift C++ Server SDK zip into project directory..."
Compress-Archive -Force -Path "$TEMP_EXTRACTED_PATH\*" -DestinationPath $CPP_SERVER_SDK_DESTINATION_PATH -ErrorAction Stop
Write-Host "Amazon GameLift C++ Server SDK has been re-packaged without license file at '$CPP_SERVER_SDK_DESTINATION_PATH'" -ForegroundColor Yellow

exit 0