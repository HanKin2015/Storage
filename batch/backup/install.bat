set PATH=%PATH%;%windir%\system32;

cd /d "%~dp0"

taskkill  /F /IM ProcessWatcher.exe  2>nul

call reg.bat

cd /d "%~dp0"
regsvr32 /s /u .\UICtrl.dll
regsvr32 /s .\UICtrl.dll

AgentService.exe -uninstall
BootAgentService.exe -uninstall
BootAgentService.exe -install
net start BootAgentService

if exist install_regcmci1258.bat call install_regcmci1258.bat

