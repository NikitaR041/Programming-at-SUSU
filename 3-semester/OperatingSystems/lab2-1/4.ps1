# Случайный афоризм из файла
# Автор скрипта: https://elims.org.ua

# Читаем содержимое файла в массив построчно и берем случайную строку
$file = Get-Content "D:\aphorism.txt"
$aphorism = Get-Random -InputObject $file # Берем случайный афоризм из массива афоризмов

# Берем случайный тег
$tags = @("#aphorism", "#quote", "#wisdom")
$tag = Get-Random -InputObject $tags

# Объединяем афоризм и тег
$aphorism = $aphorism + " " + $tag

# Выводим результат
Write-Host $aphorism
