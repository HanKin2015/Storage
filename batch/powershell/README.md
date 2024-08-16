## 1、Write-Error语句
Write-Error 是 PowerShell 的一个命令，用于向错误输出流写入一条错误信息。这与 Write-Host 或 Write-Output 不同，因为 Write-Error 写入的是错误，而不仅仅是一些普通信息。

注意以下几点：
- Write-Error 输出的内容会显示为红色（取决于你的 PowerShell 颜色配置）。
- 当你使用 Write-Error 写入错误时，它不会停止脚本的执行。如果你希望在发生错误时停止脚本，你需要使用 throw 语句。
- 你可以使用 -ErrorAction 参数来控制如何处理错误。例如，你可以设置 -ErrorAction Stop 来使脚本在遇到错误时停止执行。

## 2、双击ps1脚本会使用记事本打开编辑
要么在powershell创建执行.\template.ps1，另外就是鼠标右键使用PowerShell运行。

注意：win7系统也存在PowerShell窗口。

## 3、因为在此系统上禁止运行脚本
允许运行本地脚本：Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy Unrestricted
禁止运行本地脚本：Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy Restricted
执行脚本允许：PowerShell -ExecutionPolicy Bypass -File "C:\Users\test\Desktop\3.ps1"
