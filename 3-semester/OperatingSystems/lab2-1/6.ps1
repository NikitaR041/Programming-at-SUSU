$StartTimeHour = (Get-Date).Hour
$Day_of_week = [int]((Get-Date).DayofWeek)

if ((($Day_of_week -eq 2) -or ($Day_of_week -eq 4) -or ($Day_of_week -eq 6)) -and ($StartTimeHour -eq 11)) {
    $StartTime = Get-Date -Format "yyyy.MM.dd HH:mm:ss"
    $Free_Space_Start = Get-WMIObject Win32_LogicalDisk -Filter "DeviceID='D:'" | ForEach-Object {[math]::truncate($_.freespace / 1GB)}
    $log_file = "D:\Backups\log.txt"
    $date = "{0:yyyy-MM-dd}" -f (Get-Date)
    $path = "D:\Backups\$date\"

    if (-not(Test-Path $path)) {
        Write-Host "Creating folder: $path"
        New-Item -ItemType directory -Path $path | Out-Null
    }

    # Backup Medoc
    $time = "{0:yyyy-MM-dd HH:mm:ss}" -f (Get-Date)
    $string = "$time Start Copy \\172.16.13.1\Backups\Medoc"
    "##################################################" | Out-File -Append $log_file -Encoding UTF8
    $string | Out-File -Append $log_file -Encoding UTF8
    & robocopy \\172.16.13.1\Backups\Medoc D:\Backups\Medoc /e /log:"D:\Backups\robocopy_log.txt"

    # Backup Other
    $time = "{0:yyyy-MM-dd HH:mm:ss}" -f (Get-Date)
    $string = "$time Start Copy \\172.16.13.1\Backups\Other"
    $string | Out-File -Append $log_file -Encoding UTF8
    & robocopy \\172.16.13.1\Backups\Other D:\Backups\Other /e /log:"D:\Backups\robocopy_log.txt"

    # Backup Windows from Server 1
    $path = "$path\WindowsImageBackup"
    $time = "{0:yyyy-MM-dd HH:mm:ss}" -f (Get-Date)
    $string = "$time Start Copy \\172.16.13.1\Backups\WindowsImageBackup"
    $string | Out-File -Append $log_file -Encoding UTF8
    & robocopy \\172.16.13.1\Backups\WindowsImageBackup $path /e /log:"D:\Backups\robocopy_log.txt"

    # Backup Windows from Server 2
    $time = "{0:yyyy-MM-dd HH:mm:ss}" -f (Get-Date)
    $string = "$time Start Copy \\172.16.13.2\Backups\WindowsImageBackup"
    $string | Out-File -Append $log_file -Encoding UTF8
    & robocopy \\172.16.13.2\Backups\WindowsImageBackup $path /e /log:"D:\Backups\robocopy_log.txt"

    # Log completion
    $time = "{0:yyyy-MM-dd HH:mm:ss}" -f (Get-Date)
    $string = "$time Finish Backup"
    $string | Out-File -Append $log_file -Encoding UTF8
    "##################################################" | Out-File -Append $log_file -Encoding UTF8

    # Prepare email data
    $EndTime = Get-Date -Format "yyyy.MM.dd HH:mm:ss"
    $Free_Space_End = Get-WMIObject Win32_LogicalDisk -Filter "DeviceID='D:'" | ForEach-Object {[math]::truncate($_.freespace / 1GB)}
    $backup_Size = $Free_Space_Start - $Free_Space_End
    $Work_time = (New-TimeSpan –Start $StartTime –End $EndTime)
    $Work_time_seconds = $Work_time.TotalSeconds
    $NetworkSpeed = '{0:N1}' -f ((($backup_Size * 1024 * 1024 * 1024) / $Work_time_seconds) * 8 / 1MB)

    $Mail_String = "Free space before backup: $Free_Space_Start GB | `r`n"
    $Mail_String += "Free space after backup: $Free_Space_End GB | `r`n"
    $Mail_String += "Backup size: $backup_Size GB | `r`n"
    $Mail_String += "Backup start time: $StartTime | `r`n"
    $Mail_String += "Backup end time: $EndTime | `r`n"
    $Mail_String += "Execution time: $Work_time | `r`n"
    $Mail_String += "Average copy speed: $NetworkSpeed Mbps `r`n"

    Write-Host $Mail_String 

    # Email settings
    $From = "admin-notify@domain.com"
    $To = "admin@domain.com"
    $SMTPServer = "smtp.server.com"
    $SMTPPort = "25"
    $Username = "admin-notify@domain.com"
    $Password = "password"
    $subject = "Copy Backups to ReserveServer" 
    $body = $Mail_String 

    # Create and send email
    $message = New-Object System.Net.Mail.MailMessage $From, $To
    $message.Subject = $subject
    $message.IsBodyHTML = $true
    $message.Body = $body

    # Sending the email
    Write-Host "Sending email"
    $smtp = New-Object System.Net.Mail.SmtpClient($SMTPServer, $SMTPPort)
    $smtp.EnableSSL = $true
    $smtp.Credentials = New-Object System.Net.NetworkCredential($Username, $Password)
    $smtp.Send($message)
    Write-Host "Email sent"
    & shutdown -s -t 300 # Shut down computer after 5 minutes
}
