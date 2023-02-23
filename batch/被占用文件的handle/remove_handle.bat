::
:: 文 件 名: remove_handle.bat
:: 文件描述: 主要用于删除文件或者文件夹被占用的句柄
:: 备    注: https://superuser.com/questions/335138/how-to-close-all-file-handles-under-a-given-folder-programatically/787179#787179
::           https://blog.csdn.net/weixin_33964094/article/details/91425643
::           https://learn.microsoft.com/zh-cn/sysinternals/downloads/handle
:: 作    者: HanKin
:: 创建日期: 2023.02.22
:: 修改日期：2023.02.22
:: 
:: Copyright (c) 2023 HanKin. All rights reserved.
::

@echo off

for /f "skip=5 tokens=3,6,8 delims=: " %%i in ('handle64 %1') do echo Releasing %%k & handle64 -c %%j -y -p %%i