;
; 文 件 名: IsWin10_senior_macro.nsi
; 文件描述: 在 NSIS 中，Is 宏是 NSIS 的高级宏，用于进行条件判断。它是内置的，无法直接自定义。
; 备    注: 在"WinVer.nsh"文件中
; 作    者: HanKin
; 创建日期: 2024.06.04
; 修改日期：2024.06.04
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;

Outfile "IsWin10.exe"

!include "MUI2.nsh"
!include "WinVer.nsh"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

!define IsWindows10 "!insertmacro IsWindows10"
!include LogicLib.nsh

!macro IsWindows10
    ${If} ${IsWin10}
        StrCpy $0 "is Windows 10"
    ${Else}
        StrCpy $0 "is not Windows 10"
    ${EndIf}
!macroend

Section
    ${IsWindows10}

    DetailPrint "version: $0"
    
    MessageBox MB_OK "嗨翻世界"
SectionEnd