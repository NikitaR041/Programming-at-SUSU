@echo off
setlocal

REM Проверка наличия параметра
if "%1"=="" (
    echo Ошибка: Не указана папка.
    echo Использование: script.bat [Имя папки]
    exit /b
)

set "target_folder=%1"

REM Проверка существования папки
if not exist "%target_folder%" (
    echo Ошибка: Папка "%target_folder%" не существует.
    exit /b
)

echo Список подпапок в папке "%target_folder%", отсортированный по количеству файлов:

REM Создание временного файла для хранения количества файлов
set "temp_file=%temp%\subfolder_counts.txt"
if exist "%temp_file%" del "%temp_file%"

REM Перебор всех подпапок и подсчет количества файлов
for /d %%D in ("%target_folder%\*") do (
    set "subfolder=%%D"
    for /f "delims=" %%C in ('dir /s /a /b "%%D" ^| find /c /v ""') do (
        echo %%C %%D >> "%temp_file%"
    )
)

REM Сортировка по количеству файлов и вывод результата
sort "%temp_file%"
del "%temp_file%"

echo Сортировка завершена.
endlocal
