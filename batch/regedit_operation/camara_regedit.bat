@echo off  
setlocal  
  
:: ����Ҫ�޸ĵ�ע������·����ֵ��  
set "registryPath=HKLM\SYSTEM\CurrentControlSet\Control\Class\{6BDD1FC6-810F-11D0-BEC7-08002BE2092F}"  
set "keyName=LowerFilters"  
  
:: ����ɾ��LowerFiltersֵ����������ڣ�  
reg delete "%registryPath%" /v %keyName% /f >nul 2>&1  
  
:: �����һ��������˳�����  
if %errorlevel% equ 0 (  
    echo Successfully deleted LowerFilters for %registryPath% (now considered "empty")
    reg add "%registryPath%" /v %keyName% /t REG_MULTI_SZ /d "" /f >nul  
) else (  
    echo Failed to delete LowerFilters for %registryPath% (it may not exist)  
)  
  
endlocal