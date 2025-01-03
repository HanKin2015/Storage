;
; 文 件 名: 替换二进制文件脚本.nsi
; 文件描述: 将二进制文件打包成exe文件一键替换
; 作    者: HanKin
; 创建日期: 2024.12.10
; 修改日期：2024.12.10
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;
# 定义安装程序的基本信息
Name "libusbredir2文件替换测试"
OutFile "libusbredir2文件替换测试.exe"

!include "LogicLib.nsh"
!include "MUI2.nsh"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

# 设置安装程序的默认安装目录
InstallDir "C:\program files (x86)\AppClient"

# 请求管理员权限
RequestExecutionLevel admin

# 定义页面
#Page directory
Page instfiles

# 定义安装部分
Section "Install"

  # 判断系统是 32 位还是 64 位
  Call IsWow64
  Pop $0
  ${If} $0 == "1"
    # 64 位系统
    StrCpy $INSTDIR "C:\program files (x86)\AppClient"
  ${Else}
    # 32 位系统
    StrCpy $INSTDIR "C:\program files\AppClient"
  ${EndIf}

  # 设置安装目录
  SetOutPath "$INSTDIR"

  # 备份原文件（如果存在）
  IfFileExists "$INSTDIR\libusbredir2.dll" 0 +3
    Rename "$INSTDIR\libusbredir2.dll" "$INSTDIR\libusbredir2.dll.bak"
    DetailPrint "备份libusbredir2.dll原文件到: $INSTDIR\libusbredir2.dll.bak"

  # 将 libusbredir2.dll 文件复制到目标目录
  File "libusbredir2.dll"
  DetailPrint "将修改的libusbredir2.dll文件替换到: $INSTDIR\libusbredir2.dll"

  # 生成卸载程序
  WriteUninstaller "$INSTDIR\libusbredir2文件还原.exe"
  DetailPrint "卸载程序已生成: $INSTDIR\libusbredir2文件还原.exe"
SectionEnd

# 定义卸载部分
Section "Uninstall"

  # 删除替换的文件
  Delete "$INSTDIR\libusbredir2.dll"
  DetailPrint "删除替换的libusbredir2.dll文件: $INSTDIR\libusbredir2.dll"

  # 恢复备份文件（如果存在）
  IfFileExists "$INSTDIR\libusbredir2.dll.bak" 0 +3
    Rename "$INSTDIR\libusbredir2.dll.bak" "$INSTDIR\libusbredir2.dll"
    DetailPrint "将备份的libusbredir2.dll文件还原: $INSTDIR\libusbredir2.dll"

  # 删除卸载程序
  Delete "$INSTDIR\libusbredir2文件还原.exe"
  DetailPrint "卸载程序已删除: $INSTDIR\libusbredir2文件还原.exe"
SectionEnd

# 判断系统是否为 64 位的函数
Function IsWow64
  Push $0
  System::Call "kernel32::GetCurrentProcess() i .s"
  System::Call "kernel32::IsWow64Process(i s, *i .r0)"
  Exch $0
FunctionEnd