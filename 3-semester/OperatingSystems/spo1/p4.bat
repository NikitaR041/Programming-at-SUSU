@echo off
setlocal

REM Проверка наличия параметров
if "%1"=="" (
    echo Ошибка: Не указана эталонная папка.
    echo Использование: script.bat [Эталонная папка] [Целевая папка]
    exit /b
)

if "%2"=="" (
    echo Ошибка: Не указана целевая папка.
    echo Использование: script.bat [Эталонная папка] [Целевая папка]
    exit /b
)

set "source=%1"
set "target=%2"

REM Проверка существования папок
if not exist "%source%" (
    echo Ошибка: Эталонная папка "%source%" не существует.
    exit /b
)

if not exist "%target%" (
    echo Ошибка: Целевая папка "%target%" не существует.
    exit /b
)

echo Синхронизация папки "%target%" с эталонной папкой "%source%"...

REM Копируем недостающие файлы из эталонной папки в целевую
for /f "delims=" %%F in ('dir /b "%source%"') do (
    if not exist "%target%\%%F" (
        echo Копирование файла %%F из эталонной папки...
        copy "%source%\%%F" "%target%\"
    )
)

REM Удаляем файлы из целевой папки, которых нет в эталонной
for /f "delims=" %%F in ('dir /b "%target%"') do (
    if not exist "%source%\%%F" (
        echo Удаление файла %%F из целевой папки...
        del "%target%\%%F"
    )
)

echo Синхронизация завершена.
endlocal
