@echo off  
setlocal  
  
:: 设置要修改的注册表项的路径和值名  
set "registryPath=HKLM\SYSTEM\CurrentControlSet\Control\Class\{6BDD1FC6-810F-11D0-BEC7-08002BE2092F}"  
set "keyName=LowerFilters"  
  
:: 尝试删除LowerFilters值（如果它存在）  
reg delete "%registryPath%" /v %keyName% /f >nul 2>&1  
  
:: 检查上一个命令的退出代码  
if %errorlevel% equ 0 (  
    echo Successfully deleted LowerFilters for %registryPath% (now considered "empty")
    reg add "%registryPath%" /v %keyName% /t REG_MULTI_SZ /d "" /f >nul  
) else (  
    echo Failed to delete LowerFilters for %registryPath% (it may not exist)  
)  
  
endlocal