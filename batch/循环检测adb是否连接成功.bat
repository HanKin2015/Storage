@echo off
setlocal EnableDelayedExpansion

:: ================= CONFIGURATION =================
set "TARGET_IP=192.168.1.12"
set "TARGET_PORT=5555"
set "MAX_RETRIES=0"
set "DELAY_SECONDS=3"
:: ================================================

set "FULL_ADDRESS=%TARGET_IP%:%TARGET_PORT%"
set "count=0"

echo ==========================================
echo   ADB Auto Connect Script
echo   Target: %FULL_ADDRESS%
echo   Interval: %DELAY_SECONDS% seconds
echo   Max Retries: %MAX_RETRIES% (0=infinite)
echo ==========================================
echo.

:LOOP
set /a count+=1

if %MAX_RETRIES% GTR 0 (
    if %count% GTR %MAX_RETRIES% (
        echo [ERROR] Max retries reached (%MAX_RETRIES%). Stopping.
        goto :END_FAIL
    )
)

echo [%date% %time%] Attempt #%count% connecting to %FULL_ADDRESS% ...

:: Try to connect
adb connect %FULL_ADDRESS% >nul 2>&1

:: Give it a moment to stabilize
timeout /t 1 /nobreak >nul 2>&1

:: Get the full device list and look for our IP with 'device' status
:: We use findstr to look for the pattern: "IP:PORT       device"
:: Note: There might be multiple spaces/tabs between IP and status
adb devices | findstr /R "^%TARGET_IP%:%TARGET_PORT%[	 ]*[dD][eE][vV][iI][cC][eE]" >nul 2>&1

if %errorlevel% EQU 0 (
    echo.
    echo ==========================================
    echo   [SUCCESS] Truly connected to %FULL_ADDRESS%!
    echo   Status: device (ready for commands)
    echo ==========================================
    echo.
    adb devices
    goto :END_SUCCESS
) else (
    :: Check if it's offline or unauthorized
    adb devices | findstr "%TARGET_IP%" >nul 2>&1
    if %errorlevel% EQU 0 (
        :: Found the IP, but status is NOT 'device'
        for /f "tokens=1,2" %%A in ('adb devices ^| findstr "%TARGET_IP%"') do (
            set "STATUS=%%B"
        )
        echo [WARNING] Found %FULL_ADDRESS% but status is '!STATUS!' (not ready yet).
        echo          Waiting for authorization or retrying...
    ) else (
        echo [FAILED] Cannot reach %FULL_ADDRESS% at all.
    )
)

:: Delay before next attempt
if %DELAY_SECONDS% GTR 0 (
    ping -n %DELAY_SECONDS% 127.0.0.1 >nul 2>&1
)

goto :LOOP

:END_SUCCESS
echo Script finished successfully. Device is ready.
exit /b 0

:END_FAIL
echo Script finished. Device is NOT ready.
exit /b 1