::
:: 文 件 名: 获取当前目录文件名.bat
:: 文件描述: 获取当前目录文件名
:: 作    者: HanKin
:: 创建日期: 2022.07.18
:: 修改日期：2022.07.18
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

@echo off
pushd %1 & for %%i in (.) do set curr=%%~ni
echo %curr%
echo [General] >>1.ini
echo LastUsedProfile=%~dp0 >>1.ini
dir *.*/b >> 2.ini
pause