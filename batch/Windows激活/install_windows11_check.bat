::
:: 文 件 名: install_windows11_check.bat
:: 文件描述: （不一定能解决问题）管理员命令窗口，添加注册表项，绕过安装Windows11系统的TPM、安全启动、CPU、内存和硬盘空间检测
:: 作    者: HanKin
:: 创建日期: 2024.08.12
:: 修改日期：2024.08.12
:: 
:: Copyright (c) 2024 HanKin. All rights reserved.
::

@echo off  
setlocal

reg add "HKLM\SYSTEM\Setup\LabConfig" /v "BypassTPMCheck" s/t REG_DWORD /d "1" /f
reg add "HKLM\SYSTEM\Setup\LabConfig" /v "BypassSecureBootCheck" /t REG_DWORD /d "1" /f
reg add "HKLM\SYSTEM\Setup\LabConfig" /v "BypassRAMCheck" /t REG_DWORD /d "1" /f
reg add "HKLM\SYSTEM\Setup\LabConfig" /v "BypassStorageCheck" /t REG_DWORD /d "1" /f
reg add "HKLM\SYSTEM\Setup\LabConfig" /v "BypassCPUCheck" /t REG_DWORD /d "1" /f
reg add "HKLM\SYSTEM\Setup\MoSetup"   /v "AllowUpgradesWithUnsupportedTPMOrCPU" /t REG_DWORD /d "1" /f

endlocal
pause