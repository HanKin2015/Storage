::
:: 文 件 名: mem_cpu_io.bat
:: 文件描述: 吃掉系统内存cpuio
:: 作    者: HanKin
:: 创建日期: 2022.02.09
:: 修改日期：2022.02.09
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

@echo off

path = %path%;.;

eatcpu.exe 80
scEatMem.exe 90