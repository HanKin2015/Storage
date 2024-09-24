@echo off

for /f "tokens=3"  %%i in ('reg query "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{36fc9e60-c465-11cf-8056-444553540000}" /v LowerFilters') do (
 set pgPath=%%i
)
set pgPath=%pgPath:sangfor_commonusb\0=%

set pgPath=%pgPath:sangfor_commonusb=%

echo 导出注册表项至 %temp%/bak_36fc9e60.reg
reg export "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{36fc9e60-c465-11cf-8056-444553540000}" %temp%/bak_36fc9e60.reg
echo 清除sangfor_commonusb
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{36fc9e60-c465-11cf-8056-444553540000}" /v LowerFilters /t reg_multi_sz /d %pgPath% /f
pause