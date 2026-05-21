@echo off
rem Resolves ADAS_INTERFACES_DIR for sibling clone or 1v-superproject submodule layout.
set "ADAS_INTERFACES_DIR="

if exist "%~dp0..\..\interfaces\cmake\AdasInterfacesConfig.cmake" (
    set "ADAS_INTERFACES_DIR=%~dp0..\..\interfaces\cmake"
    goto :found
)

if exist "%~dp0..\interfaces\cmake\AdasInterfacesConfig.cmake" (
    set "ADAS_INTERFACES_DIR=%~dp0..\interfaces\cmake"
    goto :found
)

echo ERROR: AdasInterfaces not found.
echo   Tried: %~dp0..\..\interfaces\cmake  (1v-superproject modules layout)
echo   Tried: %~dp0..\interfaces\cmake       (sibling interfaces clone)
echo Clone interfaces next to perception-core or use the superproject modules/ tree.
exit /b 1

:found
echo Using AdasInterfaces_DIR=%ADAS_INTERFACES_DIR%
exit /b 0
