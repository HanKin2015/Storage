::
:: 文 件 名: all_cpu_use.bat
:: 文件描述: 本机CPU使用率
:: 作    者: HanKin
:: 创建日期: 2022.02.09
:: 修改日期：2022.02.09
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

@echo off

for /f "tokens=2 delims==" %%a in ('wmic path Win32_PerfFormattedData_PerfOS_Processor get PercentProcessorTime /value^|

findstr "PercentProcessorTime"') do (set ucpu=%%a)

echo 本机CPU使用率：%uCPU%%%

pause