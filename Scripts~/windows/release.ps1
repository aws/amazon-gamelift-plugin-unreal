param(
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $ServerSdkVersion,
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $LightWeightUnrealServerSdkVersion
)

$GAMELIFT_PLUGIN_DIR=Resolve-Path "$PSScriptRoot\..\..\GameLiftPlugin"
Write-Host "Getting version number from 'GameLiftPlugin.uplugin'"
$PLUGIN_VERSION=Select-String -LiteralPath $GAMELIFT_PLUGIN_DIR\GameLiftPlugin.uplugin -Pattern '"VersionName": ".*",' | % { $_.Matches.Value } | % { $_.substring(16, $_.length-18) }
Write-Host "Identified plugin version as $PLUGIN_VERSION" -ForegroundColor DarkYellow
& "$PSScriptRoot\clean.ps1"
if ($LASTEXITCODE -eq 0) { & "$PSScriptRoot\.import-lightweight-sdk.ps1" $LightWeightUnrealServerSdkVersion }
if ($LASTEXITCODE -eq 0) { & "$PSScriptRoot\.export-plugin-zip.ps1" $LightWeightUnrealServerSdkVersion $PLUGIN_VERSION }
if ($LASTEXITCODE -eq 0) { & "$PSScriptRoot\.export-cpp-sdk-zip.ps1" $ServerSdkVersion }
if ($LASTEXITCODE -eq 0) { & "$PSScriptRoot\.export-release.ps1" $ServerSdkVersion $PLUGIN_VERSION $LightWeightUnrealServerSdkVersion }

exit $LASTEXITCODE