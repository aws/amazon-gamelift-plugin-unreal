$ROOT_DIR=Resolve-Path "$PSScriptRoot\..\.."
$TEMP_PATH="C:\Temp\AmazonGameLiftPluginUnreal"
$LIGHTWEIGHT_SERVERSDK_PATH="$ROOT_DIR\GameLiftPlugin\Source\GameLiftServer"
$REPLACEME_FILE_NAME="REPLACEME.md"

if (Test-Path -Path $LIGHTWEIGHT_SERVERSDK_PATH)
{
	Write-Host "Cleaning up $LIGHTWEIGHT_SERVERSDK_PATH..."
	Remove-Item "$LIGHTWEIGHT_SERVERSDK_PATH\*" -Exclude $REPLACEME_FILE_NAME -Recurse -Force
}

if (Test-Path -Path $TEMP_PATH)
{
	Write-Host "Removing temporary folder to clear out downloaded artifacts..."
	Remove-Item -Recurse -Force $TEMP_PATH -ErrorAction Stop
}
else
{
	Write-Host "$TEMP_PATH is already cleaned up. Continuing..."
}

Write-Host "Downloads clean up completed!" -ForegroundColor Yellow

exit 0