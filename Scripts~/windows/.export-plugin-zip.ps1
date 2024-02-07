param(
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $LightWeightUnrealServerSdkVersion,
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $PluginVersion
)

$ROOT_DIR=Resolve-Path "$PSScriptRoot\..\.."
$BUILD_DIR="$ROOT_DIR\GameLiftPlugin\build"
$TEMP_PATH="C:\Temp\AmazonGameLiftPluginUnreal"
$TEMP_PLUGIN_PATH="$TEMP_PATH\amazon-gamelift-plugin-unreal"
$PACKAGED_ZIP_PATH="$BUILD_DIR\amazon-gamelift-plugin-unreal-$PluginVersion-sdk-$LightWeightUnrealServerSdkVersion.zip"

if (Test-Path -Path $TEMP_PLUGIN_PATH)
{
	Write-Host "Amazon GameLift plugin for Unreal Engine has already been copied to $TEMP_PLUGIN_PATH, skipping copy" -ForegroundColor DarkYellow
}
else
{
	New-Item -Force -Type Directory -Path $TEMP_PLUGIN_PATH -ErrorAction Stop
	Copy-Item -Path "$ROOT_DIR\*" -Destination $TEMP_PLUGIN_PATH -Recurse -Include *.md,GameLiftPlugin -ErrorAction Stop
}
New-Item -Force -Type Directory -Path $BUILD_DIR -ErrorAction Stop
Compress-Archive -Force -Path $TEMP_PLUGIN_PATH -DestinationPath $PACKAGED_ZIP_PATH -ErrorAction Stop
Write-Host "Amazon GameLift plugin for Unreal Engine source has been packaged at $PACKAGED_ZIP_PATH" -ForegroundColor Yellow
exit 0