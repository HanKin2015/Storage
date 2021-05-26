/*
办公助手.ahk

- 一键打开常用文件夹，如ftp的文件夹
- 一键安装所需要的软件
- 列出常忘记的操作
- 备忘录
- 希望软件跟hostspadfast一样，希望界面美观
- 一键整理桌面功能
- 一键开启功能
- 检测电脑环境情况，是否有g++、python、java环境

author: hankin
date  : 2021.05.17

Copyright (c) 2021 HanKin. All rights reserved.
*/

; 脚本配置
#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
#SingleInstance off

; 需要管理员权限
if not (A_IsAdmin) {
    Menu, tray, NoIcon
    MsgBox, 48, 提示, 请右键以管理员身份运行本程序！
    ExitApp
} else {
Gui, Add, Text, x32 y19 w230 h20 +Left, 使用说明：
Gui, Add, Text, x32 y39 w230 h20 , 点击续命按钮试试？
Gui, Add, Text, x32 y59 w230 h20 , 续命一次，长时间可用！
Gui, Add, Text, x32 y79 w230 h20 , 失效后，打开此程序，再次续命即可。
Gui, Add, Button, x22 y109 w100 h40 , 天若OCR
Gui, Add, Button, x152 y109 w100 h40 , 一键打开文件夹
Gui, Add, Button, x22 y169 w100 h40 , 关于
Gui, Add, Button, x152 y169 w100 h40 , 退出

; Generated using SmartGUI Creator 4.0
Menu, tray, NoStandard
Menu, tray, add, 天若OCR, Button天若OCR
Menu, tray, add, 一键打开文件夹, Button一键打开文件夹
Menu, tray, add, 关于, Button关于
Menu, tray, add, 退出, Button退出
Gui, Show, x535 y235 h222 w276, 续命工具
Return
}

; Gui关闭和点击退出按钮都会完全退出程序ExitApp, 否则就会留下托盘

GuiClose:
Button退出:
ExitApp



Button天若OCR:
Gui +OwnDialogs
FileCopy, %A_WinDir%\System32\drivers\etc\hosts, %A_WinDir%\System32\drivers\etc\hosts.bak
UrlDownloadToFile, https://raw.githubusercontent.com/racaljk/hosts/master/hosts, %A_WinDir%\System32\drivers\etc\hosts
if ErrorLevel
{
    FileDelete, %A_WinDir%\System32\drivers\etc\hosts.bak
    MsgBox, , 续命失败, % "续命失败！请检查你的网络连接！"
}
else
{
    Run, ipconfig /flushdns, , Hide
    MsgBox, , 续命成功, % "续命成功！现在你可以关闭此程序，使用 Google 了！:-P"
    run https://www.google.com.hk/
}
return



Button还原:
Gui +OwnDialogs
FileCopy, %A_WinDir%\System32\drivers\etc\hosts.bak, %A_WinDir%\System32\drivers\etc\hosts, 1
Run, ipconfig /flushdns, , Hide
FileDelete, %A_WinDir%\System32\drivers\etc\hosts.bak
MsgBox, , 还原成功, % "还原成功！现在你不能再访问 Google 了。‾\_(ツ)_/‾"
return


Button关于:
Gui +OwnDialogs
MsgBox, , 关于, % "感谢 @racaljk 的开源项目为此程序提供续命源。`n本程序采用 GPLv3 开源协议。`n`nCreated by @Lyraa from NUAA"
return
