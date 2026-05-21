@echo off
setlocal EnableExtensions
cd /d "%~dp0"

call "%~dp0scripts\resolve_interfaces_dir.bat"
if errorlevel 1 exit /b 1

set "BUILD_DIR=%~dp0build-sil"
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

echo Configuring perception-core (TARGET_TYPE=sil)...
cmake .. -DTARGET_TYPE=sil -DAdasInterfaces_DIR="%ADAS_INTERFACES_DIR%"
if errorlevel 1 exit /b 1

echo Building...
cmake --build . --config Release
if errorlevel 1 exit /b 1

echo.
echo SIL build OK: %BUILD_DIR%
endlocal
exit /b 0
