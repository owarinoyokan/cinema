@echo off
echo Текущий путь: %~dp0
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0CreateShortcut.ps1"
pause