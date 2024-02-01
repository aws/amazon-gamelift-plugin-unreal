& "$PSScriptRoot\.clean-exports.ps1"
if ($LASTEXITCODE -eq 0) { & "$PSScriptRoot\.clean-download-files.ps1" } # Comment this out for faster builds

exit $LASTEXITCODE