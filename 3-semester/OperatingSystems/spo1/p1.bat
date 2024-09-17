@echo off
chcp 65001>nul
setlocal enabledelayedexpansion

REM Проверка наличия параметров
if "%1"=="" (
    echo Ошибка: Не указана папка.
    echo Используйте /h для получения справки.
    exit /b
)

REM Обработка ключа /a для информации о разработчике
if "%1"=="/a" (
    echo Разработчик: Никита Романов
    exit /b
)

REM Обработка ключа /h для справки
if "%1"=="/h" (
    echo Назначение: Подсчет размера папки и всех её подпапок.
    echo Использование: script.bat [Папка] или script.bat /a или script.bat /h
    echo Ключи:
    echo   /a  - информация о разработчике
    echo   /h  - вывод справки
    exit /b
)

REM Подсчет размера папки
set "folder=%1"
echo Подсчитываем размер папки: %folder%

REM Используем команду for для подсчета размера папки
for /f "usebackq tokens=3" %%A in (`dir /s "%folder%" ^| find "байт"`) do set size=%%A

REM Вывод размера
echo Размер папки %folder% вместе с содержимым подпапок: %size% байт
