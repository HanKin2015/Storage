#
# 文 件 名: delete_regedit_one_string_value.ps1
# 文件描述: 删除注册表多字符串中的一个值
# 备    注: 实测可以
# 作    者: HanKin
# 创建日期: 2024.08.12
# 修改日期：2024.08.12
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

# 设置注册表路径和要删除的字符串
$registryPath = "HKLM:\SYSTEM\CurrentControlSet\Control\Class\{6BDD1FC6-810F-11D0-BEC7-08002BE2092F}"
$keyName = "LowerFilters"
$stringToRemove = "commonusb2"

# 读取当前的LowerFilters值
$lowerFilters = (Get-ItemProperty -Path $registryPath -Name $keyName).$keyName

# 检查LowerFilters值是否存在并且包含要删除的字符串
if ($lowerFilters -and $lowerFilters -contains $stringToRemove) {
    # 创建一个新的数组，不包含要删除的字符串
    $newData = $lowerFilters | Where-Object { $_ -ne $stringToRemove }

    # 写回新的LowerFilters值
    Set-ItemProperty -Path $registryPath -Name $keyName -Value $newData
    Write-Host "Successfully removed $stringToRemove from LowerFilters."
} else {
    Write-Host "LowerFilters value does not exist or the string to remove is not present."
}
