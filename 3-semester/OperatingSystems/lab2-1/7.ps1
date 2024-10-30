$WSUSServer = 'SERVER_NAME' #WSUS-сервер
$PortNumber = 8530 #http порт wsus
[void][reflection.assembly]::LoadWithPartialName("Microsoft.UpdateServices.Administration")
$wsus = [Microsoft.UpdateServices.Administration.AdminProxy]::getUpdateServer($WSUSServer,$False,$PortNumber)
$UpdateScope = New-Object Microsoft.UpdateServices.Administration.UpdateScope
#$UpdateScope.ApprovedStates = 'NotApproved' #указываем критерии апдейтов: не одобренные
#$UpdateScope.IncludedInstallationStates = 'NotInstalled' #указываем критерии апдейтов: не проинсталированные
$UpdateScope.IncludedInstallationStates = 'Installed' #указываем критерии апдейтов: проинсталированные
$UpdateScope #просматриваем сформированные критерии апдейтов
$wsus.GetUpdateCount($updatescope) #получаем и выводим количество апдейтов
$wsus.GetUpdateStatus($updatescope,$False) #получаем и выводим краткую информацию об обновлениях
$wsus.GetUpdates($updatescope).Title #выводим имена апдейтов

$computers = $wsus.GetComputerTargets() #все компьютеры со wsus
ForEach ($computer in $computers){ #для каждого компьютера
 $Computername = $computer.fulldomainname #получаем его имя 
 $updates = $computer.GetUpdateInstallationInfoPerUpdate($updateScope) #получаем апдейты по указаным критериям
 $UpdateCount = $updates.Count #количество апдейтов для текущего компьютера
 write-host $Computername $UpdateCount #выводим имя компьютера и количество апдейтов
 $i = 0
 ForEach ($update in $updates) { #для каждого апдейта выводим подробную информацию 
 $i++
 $update_info = $update.GetUpdate() #запрашиваем инфо об апдейте
 $UpdateTitle = $update_info.Title #имя апдейта
 $IsApproved = $update_info.IsApproved #является ли он одобренным 
 write-host $Computername $i "of" $UpdateCount $IsApproved $UpdateTitle 
 }
}
