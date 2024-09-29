@echo off
setlocal

REM Проверка наличия параметров
if "%1"=="" (
    echo Ошибка: Не указана первая папка.
    echo Использование: script.bat [Папка 1] [Папка 2]
    exit /b
)

if "%2"=="" (
    echo Ошибка: Не указана вторая папка.
    echo Использование: script.bat [Папка 1] [Папка 2]
    exit /b
)

set "folder1=%1"
set "folder2=%2"

REM Проверка существования папок
if not exist "%folder1%" (
    echo Ошибка: Папка "%folder1%" не существует.
    exit /b
)

if not exist "%folder2%" (
    echo Ошибка: Папка "%folder2%" не существует.
    exit /b
)

echo Сравнение папок "%folder1%" и "%folder2%"...

REM Сравнение по именам и размерам
echo.
echo Сравнение файлов по именам и размерам:
for /f "delims=" %%F in ('dir /b "%folder1%"') do (
    if not exist "%folder2%\%%F" (
        echo Файл %%F присутствует в "%folder1%", но отсутствует в "%folder2%"
    ) else (
        for %%A in ("%folder1%\%%F") do set "size1=%%~zA"
        for %%B in ("%folder2%\%%F") do set "size2=%%~zB"
        if not "%size1%"=="%size2%" (
            echo Размер файла %%F отличается: %size1% байт в "%folder1%", %size2% байт в "%folder2%"
        )
    )
)

for /f "delims=" %%F in ('dir /b "%folder2%"') do (
    if not exist "%folder1%\%%F" (
        echo Файл %%F присутствует в "%folder2%", но отсутствует в "%folder1%"
    )
)

REM Сравнение по атрибутам
echo.
echo Сравнение файлов по атрибутам:
for /f "delims=" %%F in ('dir /b "%folder1%"') do (
    if exist "%folder2%\%%F" (
        for %%A in ("%folder1%\%%F") do set "attrib1=%%~aA"
        for %%B in ("%folder2%\%%F") do set "attrib2=%%~aB"
        if not "%attrib1%"=="%attrib2%" (
            echo Атрибуты файла %%F отличаются: %attrib1% в "%folder1%", %attrib2% в "%folder2%"
        )
    )
)

echo Сравнение завершено.
endlocal
