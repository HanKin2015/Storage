::
:: 文 件 名: 获取当前目录下所有文件名.bat
:: 文件描述: 获取当前目录下所有文件及文件夹的名字
:: 作    者: HanKin
:: 创建日期: 2021.05.19
:: 修改日期：2022.01.19
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

@echo off

pushd %1 & for %%i in (.) do set curr=%%~ni

:: 当前文件夹名
echo %curr%

:: 存储当前文件夹路径
echo [General] >> 1.ini
echo LastUsedProfile=%~dp0 >>1.ini

:: 存储文件及文件夹名字
dir *.*/b >> 2.ini

pause