::
:: 文 件 名: errorlevel.bat
:: 文件描述: %errorlevel% 是一个特殊的系统变量，它存储了最近执行的命令的退出状态
:: 备    注: 如果命令成功执行，%errorlevel% 通常会被设置为 0。如果命令执行失败，%errorlevel% 通常会被设置为非零值
:: 作    者: HanKin
:: 创建日期: 2024.08.28
:: 修改日期：2024.08.28
:: 
:: Copyright (c) 2024 HanKin. All rights reserved.
::

@echo off
:: 执行一个命令
dir non_existent_file.txt

:: 打印命令的退出状态
echo %errorlevel%
pause