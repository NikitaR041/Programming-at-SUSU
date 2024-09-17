@echo off
setlocal

REM Проверка наличия параметра (папки)
if "%1"=="" (
    echo Ошибка: Не указана папка.
    echo Использование: script.bat [Папка]
    exit /b
)

set "folder=%1"
echo Содержимое папки: %folder%

REM Предложение выбора через команду choice
echo Выберите критерий сортировки:
echo D - по дням создания
echo M - по месяцам создания
echo Y - по годам создания
choice /c DMY /m "Выберите критерий сортировки (D - Дни, M - Месяцы, Y - Годы): "

REM Обработка выбора
if errorlevel 3 goto sort_years
if errorlevel 2 goto sort_months
if errorlevel 1 goto sort_days

:sort_days
echo Сортировка по дням создания:
dir "%folder%" /O:D
goto end

:sort_months
echo Сортировка по месяцам создания:
dir "%folder%" /O:D
goto end

:sort_years
echo Сортировка по годам создания:
dir "%folder%" /O:D
goto end

:end
