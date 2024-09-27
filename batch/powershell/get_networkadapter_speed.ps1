#
# 文 件 名: get_networkadapter_speed.ps1
# 文件描述: 获取网络适配器的速度
# 备    注: Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy Unrestricted
            powershell -File get_networkadapter_speed.ps1
            echo $LASTEXITCODE
# 作    者: HanKin
# 创建日期: 2024.09.25
# 修改日期：2024.09.25
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

$speed = Get-WmiObject -Class Win32_NetworkAdapter | 
    Where-Object { $_.Speed -and $_.MACAddress -and $_.Name -notmatch 'wireless|wi-fi|bluetooth|802.11' } | 
    Select-Object -ExpandProperty Speed

# 将速度从比特每秒转换为兆比特每秒
$speedMbps = [math]::Round($speed / 1MB)

# 输出速度
Write-Output "Network speed: $speedMbps Mbps"

# 设置退出代码（return network speed as exit code）
exit $speedMbps