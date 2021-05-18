#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

^j::
Send, Hello World
Return
/*
第一行: ^j:: 是热键. ^ 代表 Ctrl, j 是字母 J. 任何在 :: 左边的字符表示您需要按下的热键.
第二行: Send, My First Script 表示如何发送按键. Send 是命令, 任何在逗号(,) 之后的内容将会被键入.
第三行: Return. Return 将会成为你最好的朋友. 从字面上看, 它将停止代码继续往下. 当你的脚本包含越来越多的东西时, 使用 Return 会避免很多问题.
*/


::ftw::Free the whales
Return
/*
需要按回车键
*/

esc::
   MsgBox Escape!!!!
Return

::btw::
   MsgBox You typed "btw".
Return
/*
需要按回车键
*/

^k::
MsgBox 即将打开记事本
Run, Notepad.exe
Return

