@echo off
"%~dp0\ListDevices.exe" > "%TEMP%\ListDevices.txt"
start "" "%TEMP%\ListDevices.txt"