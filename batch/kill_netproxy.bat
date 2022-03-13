@echo off
cls
:start
taskkill /f /im netproxy.exe
ping -n 3 127.0.0.1>nul
goto start