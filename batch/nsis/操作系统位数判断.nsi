;
; 文 件 名: 操作系统位数判断.nsi
; 文件描述: 判断操作系统位数
; 作    者: HanKin
; 创建日期: 2024.12.10
; 修改日期：2024.12.10
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;
# 定义安装程序的基本信息
Name "系统位数判断示例"
OutFile "系统位数判断示例.exe"

# 包含 Modern UI 2
!include "MUI2.nsh"

# 设置语言
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

# 请求管理员权限
RequestExecutionLevel admin

# 定义页面
Page instfiles

# 定义安装部分
Section "Install"

  # 判断系统是 32 位还是 64 位
  Call IsWow64
  Pop $0
  ${If} $0 == "1"
    # 64 位系统
    DetailPrint "当前系统是 64 位系统。"
    StrCpy $INSTDIR "C:\Program Files (x86)\Example"
  ${Else}
    # 32 位系统
    DetailPrint "当前系统是 32 位系统。"
    StrCpy $INSTDIR "C:\Program Files\Example"
  ${EndIf}

SectionEnd

# 判断系统是否为 64 位的函数
Function IsWow64
  Push $0
  System::Call "kernel32::GetCurrentProcess() i .s"
  System::Call "kernel32::IsWow64Process(i s, *i .r0)"
  Exch $0
FunctionEnd
