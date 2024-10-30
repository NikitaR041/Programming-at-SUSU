Function Get-Image {
    begin { [System.Reflection.Assembly]::LoadWithPartialName("System.Drawing") | Out-Null }
    process {
        $fi = [System.IO.FileInfo]$_
        if ($fi.Exists) {
            $img = [System.Drawing.Image]::FromFile($_)
            $img.Clone()
            return $img
            $img.Dispose()
        } else {
            Write-Host "File not found: $_" -Fore Yellow
        }
    }
    end {}
}

$path = "D:\photo"

# Получаем все изображения в указанной папке
Get-ChildItem -Path $path -Recurse -Include *.jpg | ForEach-Object {
    # Получаем изображение
    $image = $_.FullName | Get-Image

    if ($image) {
        $Width = $image.Width
        $Height = $image.Height
        $pixels = $Width * $Height
        $hd_ready = 1280 * 720
        
        # Вывод на экран
        $string = $_.FullName + ' Width:' + $Width + ' Height:' + $Height + " Pixels:" + $pixels
        
        # Если качество ниже HD Ready, удаляем файл
        if ($pixels -le $hd_ready) {
            Remove-Item $_.FullName
            Write-Host "Deleted: $string"
        } else {
            # Если качество выше HD Ready, переименовываем в .png
            $newFileName = [System.IO.Path]::ChangeExtension($_.FullName, ".png")
            $image.Save($newFileName, [System.Drawing.Imaging.ImageFormat]::Png)
            Write-Host "Converted: $newFileName"
        }

        $image.Dispose()
    }
}
