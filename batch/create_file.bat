::
:: 文 件 名: create_file.bat
:: 文件描述: 一次创建20个10MB大小的文件
:: 作    者: HanKin
:: 创建日期: 2022.11.23
:: 修改日期：2022.11.23
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

@echo off

set a=1
:loop
fsutil file createnew file%a%.txt 10485760
echo file%a% done
set /a a+=1
if %a% lss 21 goto :loop

pause
