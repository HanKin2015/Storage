::
:: �� �� ��: all_cpu_use.bat
:: �ļ�����: ����CPUʹ����
:: ��    ��: HanKin
:: ��������: 2022.02.09
:: �޸����ڣ�2022.02.09
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

@echo off

for /f "tokens=2 delims==" %%a in ('wmic path Win32_PerfFormattedData_PerfOS_Processor get PercentProcessorTime /value^|

findstr "PercentProcessorTime"') do (set ucpu=%%a)

echo ����CPUʹ���ʣ�%uCPU%%%

pause