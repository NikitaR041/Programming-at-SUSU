@echo off

REM Установить кодовую страницу UTF-8
chcp 65001 > nul

REM Открытие командного файла для редактирования с использованием "Блокнот"
notepad.exe %~f0

REM Задать цвет фона и цвет символа
color 0A

REM Вывести справку в файл help.txt
help > help.txt
echo Справка сохранена в help.txt

REM Пауза, чтобы увидеть результат выполнения команд
pause
