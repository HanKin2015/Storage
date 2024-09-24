# 1、bat脚本无法删除注册表多字符串中一条
规避方案使用ps1脚本
见：D:\Github\Storage\batch\powershell\delete_regedit_one_string_value.ps1

# 2、因为在此系统上禁止运行脚本
允许运行本地脚本：Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy Unrestricted
禁止运行本地脚本：Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy Restricted
执行脚本允许：PowerShell -ExecutionPolicy Bypass -File "C:\Users\test\Desktop\3.ps1"

因此部署的时候还得使用bat脚本执行ps1脚本才行。（原因是本地的安全软件给关闭了，正常来说是开启的）