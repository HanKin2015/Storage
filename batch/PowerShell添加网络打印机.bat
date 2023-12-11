::
:: 文 件 名: PowerShell添加网络打印机.bat
:: 文件描述: PowerShell添加网络打印机
:: 备    注: 适用于已经添加过打印机的场景，即已经安装打印机驱动，且打印机端口也已经存在。
::           计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Print\Printers\Microsoft Print to PDF
::           Name/Port/Printer Driver/Share Name等参数
:: 作    者: HanKin
:: 创建日期: 2023.12.11
:: 修改日期：2023.12.11
:: 
:: Copyright (c) 2023 HanKin. All rights reserved.
::

# 定义网络打印机的信息
$printerName = "HP 1606"  # 打印机的名称
$printerPort = "12.122.126.27"  # 打印机的端口，可以是 IP 地址或者端口名称
$shareName = "HP1606_12.122.126.27"  # 共享打印机的名称

# 安装打印机
Add-Printer -Name $printerName -PortName $printerPort -DriverName "HP 1606 Driver"

# 设置打印机共享
Set-Printer -Name $printerName -Shared $true -ShareName $shareName

# 输出安装结果
Write-Host "已安装打印机：$printerName，端口：$printerPort，共享名称：$shareName"