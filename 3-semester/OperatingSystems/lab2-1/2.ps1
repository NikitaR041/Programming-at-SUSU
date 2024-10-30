Function Get-Image {
   begin { [void][System.Reflection.Assembly]::LoadWithPartialName("System.Drawing") | Out-Null }
   process {
      $fi = [System.IO.FileInfo]$_
      if ($fi.Exists) {
         $img = [System.Drawing.Image]::FromFile($_)
         $clonedImg = $img.Clone()
         $img.Dispose()
         return $clonedImg
      } else {
         Write-Host "File not found: $_" -ForegroundColor Yellow
      }
   }
}

# Скачиваем файл
$webclient = New-Object System.Net.WebClient
$url = "http://cs418720.userapi.com/v418720852/20d0/DiSlb-_mVBg.jpg"
$file = "D:\SUSU-Programming\3-semester\OperatingSystems\lab2-1\ImageSize.jpg"
$webclient.DownloadFile($url, $file)

# Получаем ширину и высоту изображения
$image = $file | Get-Image
$Width = $image.Width
$Height = $image.Height

# Вывод на экран
Write-Output "Width: $Width, Height: $Height"
