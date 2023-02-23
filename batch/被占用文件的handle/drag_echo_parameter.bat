::
:: 文 件 名: drag_echo_parameter.bat
:: 文件描述: 拖曳文件然后输出参数
:: 作    者: HanKin
:: 创建日期: 2023.02.22
:: 修改日期：2023.02.22
:: 
:: Copyright (c) 2023 HanKin. All rights reserved.
::

:: 不输出执行的详细命令行
@echo off

::for /f "tokens=1,2,3 delims=: " %%i in ('handle64 %1') do echo %%i %%j & echo %%k
for /f "skip=5 tokens=6,7,8 delims=: " %%i in ('handle64 %1') do echo %%i %%j %%k

:: 请按任意键继续
pause