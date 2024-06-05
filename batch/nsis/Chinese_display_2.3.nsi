;
; 文 件 名: Chinese_display_2.3.nsi
; 文件描述: 使用NSIS2.3版本打印输出中文，注意需要ANSI编码
; 作    者: HanKin
; 创建日期: 2024.06.04
; 修改日期：2024.06.04
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;

Outfile "Chinese_display_2.3.exe"

; 整个安装程序为中文版
!include "MUI2.nsh"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

Section
    MessageBox MB_OK "嗨翻世界"
    DetailPrint "窗前明月光，疑是地上霜"
SectionEnd