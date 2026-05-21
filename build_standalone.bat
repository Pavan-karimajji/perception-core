@echo off
setlocal EnableExtensions
cd /d "%~dp0"

call "%~dp0scripts\resolve_interfaces_dir.bat"
if errorlevel 1 exit /b 1

set "BUILD_DIR=%~dp0build-standalone"
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

echo Configuring perception-core (TARGET_TYPE=standalone)...
cmake .. -DTARGET_TYPE=standalone -DAdasInterfaces_DIR="%ADAS_INTERFACES_DIR%"
if errorlevel 1 exit /b 1

echo Building...
cmake --build . --config Release
if errorlevel 1 exit /b 1

echo.
echo Standalone build OK: %BUILD_DIR%
echo Executable: %BUILD_DIR%\src\platform\standalone\Release\perception_standalone.exe
endlocal
exit /b 0
