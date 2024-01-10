param(
	[Parameter(Mandatory)]
	[Alias("ServerSdk", "SdkVersion", "Sdk")]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $ServerSdkVersion,
	[Parameter(Mandatory)]
	[ValidatePattern("\d+\.\d+\.\d+")]
	[string] $PluginVersion
)

& "$PSScriptRoot\.export-plugin-zip.ps1" $ServerSdkVersion $PluginVersion
if ($LASTEXITCODE -eq 0) { & "$PSScriptRoot\.export-cpp-sdk-zip.ps1" $ServerSdkVersion }
if ($LASTEXITCODE -eq 0) { & "$PSScriptRoot\.export-release.ps1" $ServerSdkVersion $PluginVersion }
exit $LASTEXITCODE