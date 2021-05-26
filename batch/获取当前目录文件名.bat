@echo off
pushd %1 & for %%i in (.) do set curr=%%~ni
echo %curr%
echo [General] >>1.ini
echo LastUsedProfile=%~dp0 >>1.ini
dir *.*/b >> 2.ini
pause