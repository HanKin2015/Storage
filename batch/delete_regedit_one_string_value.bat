::
:: 文 件 名: delete_regedit_one_string_value.bat
:: 文件描述: 删除注册表多字符串中的一个值（失败）
:: 备    注: 其中的字符串是通过空字符（\0）分隔的，我们不能直接使用批处理的 for 循环来分隔这些字符串，因为 for 循环默认是按照空格、制表符、换行符等来分隔字符串的
:: 作    者: HanKin
:: 创建日期: 2024.08.12
:: 修改日期：2024.08.12
:: 
:: Copyright (c) 2024 HanKin. All rights reserved.
::

@echo off
setlocal enabledelayedexpansion

:: 设置注册表路径和要删除的字符串
set "registryPath=HKLM\SYSTEM\CurrentControlSet\Control\Class\{6BDD1FC6-810F-11D0-BEC7-08002BE2092F}"
set "keyName=LowerFilters"
set "stringToRemove=commonusb2"

:: 读取当前的LowerFilters值
for /f "tokens=*" %%a in ('reg query "%registryPath%" /v %keyName% 2^>nul') do (
    set "regData=%%a"
)
echo %regData%

:: 检查LowerFilters值是否存在
if defined regData (
    :: 创建一个新的字符串，不包含要删除的字符串
    set "newData="
    for /f "tokens=2*" %%a in ('reg query "%registryPath%" /v %keyName%') do (
        set "data=%%b"
        for %%i in (!data!) do (
            if "%%i" neq "%stringToRemove%" (
                set "newData=!newData!%%i "
            )
        )
    )

    :: 删除尾部空格
    set "newData=!newData:~0,-1!"

    :: 写回新的LowerFilters值
    reg add "%registryPath%" /v %keyName% /t REG_MULTI_SZ /d "!newData!" /f
) else (
    echo LowerFilters value does not exist.
)

echo %data%
echo %newData%

endlocal
pause
