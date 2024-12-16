# Определяем рабочий стол текущего пользователя
$Desktop = [Environment]::GetFolderPath("Desktop")

Write-Host "Текущая директория: $(Get-Location)" -ForegroundColor Yellow
$ExePath = Join-Path (Get-Location) "cinema\cinema.exe"

if (-not (Test-Path -Path $ExePath)) {
    Write-Host "Не найдено .exe файлов в текущей директории." -ForegroundColor Red
    exit 1
} else {
    Write-Host "Найден файл: $($ExeFile.FullName)" -ForegroundColor Green
}

# Создаём ярлык
$ShortcutPath = Join-Path $Desktop "cinema.lnk"
$WScriptShell = New-Object -ComObject WScript.Shell
$Shortcut = $WScriptShell.CreateShortcut($ShortcutPath)
$Shortcut.TargetPath = $ExePath
$Shortcut.WorkingDirectory = (Get-Item $ExePath).DirectoryName
$Shortcut.IconLocation = $ExePath
$Shortcut.Save()

Write-Host "Ярлык успешно создан: $ShortcutPath" -ForegroundColor Green
