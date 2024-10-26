:: This script can be used to build on Windows.
:: You need to have CMake installed.

@echo off
setlocal enabledelayedexpansion

:clean
echo Removing build directory...
rmdir /s /q build
if %errorlevel% neq 0 (
    echo Failed to remove build directory.
    exit /b 1
) else (
    echo Build directory removed.
)

if "%~1" == "fclean" (
    exit /b 0
)

if "%~1" == "re" (
    call :clean
)

if exist "build" (
    echo Build directory already created.
) else (
    echo No build directory found, creating new one.
    mkdir build
    if %errorlevel% neq 0 (
        echo Failed to create build directory.
        exit /b 1
    )
    echo Build directory created.
)

echo Going to build directory.
cd build
if %errorlevel% neq 0 (
    echo Failed to change to build directory.
    exit /b 1
)

echo Launching CMake...
cmake ..
if %errorlevel% neq 0 (
    echo Failed to run CMake.
    exit /b 1
)
echo CMake finished.

echo Building targets...
cmake --build .
if %errorlevel% neq 0 (
    echo Failed to build targets.
    exit /b 1
)
echo Targets built.
exit /b 0
