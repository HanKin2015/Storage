::
:: 文 件 名: 禁用和启用USB设备.bat
:: 文件描述: 通过devcon.exe工具禁用和启用USB设备
:: 作    者: HanKin
:: 注    意: 不清楚是devcon的原因还是其他原因，命令只能匹配前几个字符
:: 创建日期: 2022.08.04
:: 修改日期：2022.08.04
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

@echo off

echo disable USB\ROOT_HUB20*
devcon.exe disable "USB\ROOT_HUB20*"

echo enable USB\ROOT_HUB20*
devcon.exe enable "USB\ROOT_HUB20*"

pause