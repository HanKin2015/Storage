#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
#SingleInstance off

if not (A_IsAdmin) {
    Menu, tray, NoIcon
    MsgBox, 48, 提示, 请右键以管理员身份运行本程序！
    ExitApp
} else {
Gui, Add, Button, x22 y109 w100 h40 , 续命
Gui, Add, Button, x152 y109 w100 h40 , 还原
Gui, Add, Button, x22 y169 w100 h40 , 关于
Gui, Add, Button, x152 y169 w100 h40 , 退出
Gui, Add, Text, x32 y19 w230 h20 +Left, 使用说明：
Gui, Add, Text, x32 y39 w230 h20 , 点击续命按钮试试？
Gui, Add, Text, x32 y59 w230 h20 , 续命一次，长时间可用！
Gui, Add, Text, x32 y79 w230 h20 , 失效后，打开此程序，再次续命即可。
; Generated using SmartGUI Creator 4.0
Menu, tray, NoStandard
Menu, tray, add, 续命, Button续命
Menu, tray, add, 还原, Button还原
Menu, tray, add, 关于, Button关于
Menu, tray, add, 退出, Button退出
Gui, Show, x535 y235 h222 w276, 续命工具
Return
}


GuiClose:

Button退出:
ExitApp



Button续命:
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
