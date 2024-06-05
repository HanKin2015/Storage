;
; 文 件 名: Unicode_3.10.nsi
; 文件描述: Unicode语句在3.0版本及以上支持，但目前不知道它作用
; 作    者: HanKin
; 创建日期: 2024.06.04
; 修改日期：2024.06.04
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;
Outfile "Unicode_3.10.exe"

!include "WinVer.nsh"
Unicode true

; 请求管理员权限
RequestExecutionLevel admin
 
; 安装程序入口点
Section
  DetailPrint 你好，世界！
SectionEnd
