@echo off
:loop
echo [%time%] 正在执行定时任务...

:: --- 在这里写你要执行的命令 ---
dir C:\ > C:\temp\log.txt
echo 任务已完成，日志已保存。
:: ---------------------------

echo 等待60秒后再次执行...
:: timeout /t 60 表示等待60秒，/nobreak 表示忽略按键中断
set /a wait_seconds=30*60 
timeout /t %wait_seconds% /nobreak

msg * /time:5 闹钟  
msg * /time:0 闹钟  

::goto loop

@echo off
msg * 闹钟
timeout /t 3

cscript //nologo 闹钟.vbs

cscript //nologo //e:jscript "%~f0" & exit /b
// VBScript代码开始
WScript.Echo "这是您的消息内容"
// VBScript代码结束

powershell -command "Add-Type -AssemblyName System.Windows.Forms; [System.Windows.Forms.MessageBox]::Show('这是您的消息内容', '标题')"

Dim waitTime
' 检查是否传入了参数，防止没传参数导致报错
If WScript.Arguments.Count > 0 Then
    ' 获取第一个参数 (索引为0)，并将其转换为数字
    waitTime = CInt(WScript.Arguments.Item(0))
Else
    'MsgBox "错误：未提供时间参数！", vbCritical, "用法错误"
    waitTime = 5
End If

' 执行休眠 (单位：毫秒)
WScript.Sleep waitTime * 1000

' 弹出消息框
MsgBox "闹钟响了！" & vbCrLf & "你相信光吗？", vbInformation, "定时提醒"