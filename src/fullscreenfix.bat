@echo off
if "%1"=="" (
    echo Usage: %0 ^<html_file^>
    exit /b 1
)
powershell -Command "(Get-Content '%1.html') -replace 'Module\.requestFullscreen\(!1,!1\)', 'document.getElementById(\"canvas\").requestFullscreen()' | Set-Content '%1.html'"
echo Replacement done in %1.html