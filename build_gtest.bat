@echo off
setlocal EnableExtensions
cd /d "%~dp0"

call "%~dp0scripts\resolve_interfaces_dir.bat"
if errorlevel 1 exit /b 1

set "BUILD_DIR=%~dp0build-test"
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

echo Configuring perception-core tests (TARGET_TYPE=sil, BUILD_TESTING=ON)...
cmake .. -DTARGET_TYPE=sil -DBUILD_TESTING=ON -DAdasInterfaces_DIR="%ADAS_INTERFACES_DIR%"
if errorlevel 1 exit /b 1

echo Building...
cmake --build . --config Release
if errorlevel 1 exit /b 1

echo Running Tests...
ctest -C Release --output-on-failure
if errorlevel 1 exit /b 1

echo.
echo GTest build and execution OK!
endlocal
exit /b 0
