@echo off
setlocal EnableExtensions
cd /d "%~dp0"

conan --version >nul 2>&1
if errorlevel 1 (
  echo ERROR: Conan is not installed or not in PATH.
  echo Install Conan 2 and re-run this script.
  exit /b 1
)

call "%~dp0scripts\resolve_interfaces_dir.bat"
if errorlevel 1 exit /b 1

set "BUILD_DIR=%~dp0build-test"
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

echo Installing Conan dependencies (protobuf from cache/remote)...
conan install .. --output-folder . --build=missing -s build_type=Release
if errorlevel 1 exit /b 1

echo Configuring perception-core tests (TARGET_TYPE=sil, BUILD_TESTING=ON)...
cmake --fresh .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DTARGET_TYPE=sil -DBUILD_TESTING=ON -DAdasInterfaces_DIR="%ADAS_INTERFACES_DIR%"
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
