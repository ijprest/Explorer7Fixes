@echo off
setlocal ENABLEEXTENSIONS
set DLL=Release\Explorer7Fixes.dll
if "%PROCESSOR_ARCHITECTURE%"=="AMD64" set DLL=x64\Release\Explorer7Fixes.dll

for /f "delims=" %%Q IN ('ver') DO if "%%Q"=="Microsoft Windows [Version 6.1.7600]" goto :install

echo.This is the wrong version of Windows; only the following is supported:
echo.    Microsoft Windows [Version 6.1.7600]"
pause
goto :EOF

:install
echo.This will uninstall/deregister: %DLL%
echo.Once uninstalled, only new instances of explorer.exe are affected;
echo.you may need to log off/on in order to see any changes.
echo.
pause
regsvr32 /u "%~dp0%DLL%"
