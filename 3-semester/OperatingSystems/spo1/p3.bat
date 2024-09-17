@echo off
setlocal

REM Проверка наличия файла error.txt
if not exist "D:\spo1\error.txt" (
    echo Ошибка: Файл error.txt не найден.
    exit /b
)

REM Чтение файла error.txt и завершение указанных процессов
for /f "tokens=*" %%A in (D:\spo1\error.txt) do (
    echo Проверка процесса %%A...
    tasklist | findstr /i "%%A" >nul
    if %errorlevel%==0 (
        echo Завершаем процесс %%A...
        taskkill /IM %%A /F
    ) else (
        echo Процесс %%A не запущен.
    )
)

echo Все запрещенные процессы были обработаны.
endlocal
