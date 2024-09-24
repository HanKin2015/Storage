#
# 文 件 名: delete_regedit_REG_MULTI_SZ.ps1
# 文件描述: 删除注册表多字符串中的一个值
# 备    注: 投入实际场景
# 作    者: HanKin
# 创建日期: 2024.09.20
# 修改日期：2024.09.20
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#
$KEY_PATH = "HKLM:\SYSTEM\CurrentControlSet\Control\Class\{6BDD1FC6-810F-11D0-BEC7-08002BE2092F}"
$VALUE_NAME = "LowerFilters"
$SEARCH_STRING = "lala"

$regData = Get-ItemProperty -Path $KEY_PATH -Name $VALUE_NAME -ErrorAction SilentlyContinue

if ($regData -and $regData.$VALUE_NAME) {
    $newValue = $regData.$VALUE_NAME | Where-Object { $_ -ne $SEARCH_STRING }
    Set-ItemProperty -Path $KEY_PATH -Name $VALUE_NAME -Value $newValue
    Write-Host "The registry value was updated successfully."
} else {
    Write-Host "Failed to read the registry value or the value does not exist."
}