Loop

{

InputBox, cmd,快速启动,请输入命令：`n`n`n注：查看命令请留空；退出程序请按Esc。

if (cmd="我的电脑" or cmd="wddn")

Run ::{20d04fe0-3aea-1069-a2d8-08002b30309d}

if (cmd="记事本" or cmd="jsb")

Run C:\Windows\system32\notepad.exe

if (cmd="计算器" or cmd="jsq")

Run C:\Windows\system32\calc.exe

if (cmd="百度" or cmd="bd")

Run http://www.baidu.com

if Instr(cmd,"www.") or Instr(cmd,".com") or Instr(cmd,".cn") or Instr(cmd,".net")

Run %cmd%

；根据个人需要添加

if cmd=

Run Notepad.exe %A_ScriptName%

}

Esc::ExitApp