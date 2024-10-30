$source = "$([Environment]::GetFolderPath('MyPictures'))\Снимки экрана"
$outputFile = "D:\CountFiles.csv"

# Убедимся, что файл не существует, перед началом записи
if (Test-Path $outputFile) {
    Remove-Item $outputFile
}

# Записываем заголовки в файл
"Folder,Files,Size (MB)" | Out-File $outputFile

Get-ChildItem $source -recurse -force | Where-Object { $_.PSIsContainer } | ForEach-Object {
    $count = Get-ChildItem $_.FullName -Recurse | Where-Object { $_.Length -gt 0 } | Measure-Object -Property Length -Sum
    $folderSizeMB = '{0:F}' -f (($count.Sum / 1MB))

    Write-Host "Folder: $($_.FullName)"
    Write-Host "Files: $($count.Count)"
    Write-Host "Size: $folderSizeMB MB"

    '"' + $_.FullName + '","' + $count.Count + '","' + $folderSizeMB + '"' | Out-File $outputFile -Append
}

Write-Host "Data has been written to $outputFile"
