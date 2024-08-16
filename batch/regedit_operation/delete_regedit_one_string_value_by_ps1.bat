::
:: 文 件 名: delete_regedit_one_string_value_by_ps1.bat
:: 文件描述: 删除注册表多字符串中的一个值
:: 备    注: 其中的字符串是通过空字符（\0）分隔的，不能直接使用批处理的 for 循环来分隔这些字符串
:: 作    者: HanKin
:: 创建日期: 2024.08.12
:: 修改日期：2024.08.12
:: 
:: Copyright (c) 2024 HanKin. All rights reserved.
::

@echo off
setlocal

:: 处理脚本的特殊变量，它代表了脚本所在的目录的完整路径
cd /D "%~dp0"
echo Running script from: %cd%

PowerShell -ExecutionPolicy Bypass -File ".\delete_regedit_one_string_value.ps1"

endlocal
pause
