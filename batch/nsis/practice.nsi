;
; 文 件 名: practice.nsi
; 文件描述: 练习实战
; 作    者: HanKin
; 创建日期: 2024.06.04
; 修改日期：2024.06.04
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;

!define /REDEF UNICODE
!define PRODUCT_NAME "TestApp"
!define PRODUCT_VERSION "2.46.0.0"
!define PRODUCT_COMPANY "Test Company"

!include "MUI2.nsh"
!include "LogicLib.nsh"
!include "FileFunc.nsh"
!define StrStr "!insertmacro StrStr"

!macro StrStr ResultVar String SubString
  Push `${String}`
  Push `${SubString}`
  Call StrStr
  Pop `${ResultVar}`
!macroend

;字符串查找函数
Function StrStr
/*After this point:
  ------------------------------------------
  $R0 = SubString (input)
  $R1 = String (input)
  $R2 = SubStringLen (temp)
  $R3 = StrLen (temp)
  $R4 = StartCharPos (temp)
  $R5 = TempStr (temp)*/

  ;Get input from user
  Exch $R0
  Exch
  Exch $R1
  Push $R2
  Push $R3
  Push $R4
  Push $R5

  ;Get "String" and "SubString" length
  StrLen $R2 $R0
  StrLen $R3 $R1
  ;Start "StartCharPos" counter
  StrCpy $R4 0

  ;Loop until "SubString" is found or "String" reaches its end
  ${Do}
    ;Remove everything before and after the searched part ("TempStr")
    StrCpy $R5 $R1 $R2 $R4

    ;Compare "TempStr" with "SubString"
    ${IfThen} $R5 == $R0 ${|} ${ExitDo} ${|}
    ;If not "SubString", this could be "String"'s end
    ${IfThen} $R4 >= $R3 ${|} ${ExitDo} ${|}
    ;If not, continue the loop
    IntOp $R4 $R4 + 1
  ${Loop}

/*After this point:
  ------------------------------------------
  $R0 = ResultVar (output)*/

  ;Remove part before "SubString" on "String" (if there has one)
  StrCpy $R0 $R1 `` $R4

  ;Return output to user
  Pop $R5
  Pop $R4
  Pop $R3
  Pop $R2
  Pop $R1
  Exch $R0
FunctionEnd

!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

; Unicode编码在NSI 3.0版本才支持的，NSIS用户手册说明
;Unicode True

VIProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey FileDescription "${PRODUCT_NAME} Installer"
VIAddVersionKey FileVersion "${PRODUCT_VERSION}"
VIAddVersionKey ProductName "${PRODUCT_NAME} Installer" 
VIAddVersionKey ProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey CompanyName "${PRODUCT_COMPANY}"
VIAddVersionKey LegalCopyright "Copyright (C) 1994-2024 ${PRODUCT_COMPANY}"


;General

;Properly display all languages (Installer will not work on Windows 95, 98 or ME!)

;Name and file
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "TestInstaller v${PRODUCT_VERSION}.exe"

;Default installation folder
InstallDir "$PROGRAMFILES\TestCompany\TestApp"

;Get installation folder from registry if available
;InstallDirRegKey HKCU "Software\Modern UI Test" ""

;Request Admin privileges for Windows Vista
RequestExecutionLevel admin
  
;--------------------------------


var DeviceDesc
var nRet
var nValue
Function INSTALL_USBHUB
	StrCpy $DeviceDesc "PCI\ven_10ff&dev_81ff"
	call InstallorUpdateDriver
    DetailPrint ""
    DetailPrint "-------------"
    call GetResult
    DetailPrint "-------------"
    DetailPrint ""
FunctionEnd

Function INSTALL_USBHUBB
	StrCpy $DeviceDesc "PCI\ven_10ff&dev_821ff"
	call InstallorUpdateDriver
    DetailPrint ""
    DetailPrint "-------------"
    call GetResult
    DetailPrint "-------------"
    DetailPrint ""
FunctionEnd

Function GetResult
    DetailPrint "Exec GetResult DeviceDesc=$DeviceDesc"
	nsExec::Exec  '"devcon.exe" find "$DeviceDesc"'
	Pop $nRet 	;nsExec::ExecToStack 执行结果
	Pop $nValue ;返回结果
	DetailPrint "$nRet, devcon.exe find $nValue"
    DetailPrint ""
    
    DetailPrint "ExecWait GetResult DeviceDesc=$DeviceDesc"
	ExecWait  '"devcon.exe" find "$DeviceDesc"'
	Pop $nRet 	;nsExec::ExecToStack 执行结果
	Pop $nValue ;返回结果
	DetailPrint "$nRet, devcon.exe find $nValue"
    DetailPrint ""
    
    DetailPrint "ExecToStack GetResult DeviceDesc=$DeviceDesc"
	nsExec::ExecToStack  "devcon.exe find $DeviceDesc"
	Pop $nRet 	;nsExec::ExecToStack 执行结果
	Pop $nValue ;返回结果
	DetailPrint "$nRet, devcon.exe find $nValue"
    DetailPrint ""
    
    DetailPrint "ExecShell GetResult DeviceDesc=$DeviceDesc"
	ExecShell open  "devcon.exe find $DeviceDesc"
	Pop $nRet 	;nsExec::ExecToStack 执行结果
	Pop $nValue ;返回结果
	DetailPrint "$nRet, devcon.exe find $nValue"
    DetailPrint ""
FunctionEnd

Function InstallorUpdateDriver
    DetailPrint "DeviceDesc=$DeviceDesc"
	nsExec::ExecToStack  '"devcon.exe" find	"$DeviceDesc"'
	Pop $nRet 	;nsExec::ExecToStack 执行结果
	Pop $nValue ;返回结果
	DetailPrint "$nRet, devcon.exe find $nValue"
	${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
	DetailPrint "$2/$1/$0 $4:$5:$6  $nValue !$\r$\n"
	
	; 需要比较字符串，是否包含"No matching devices found"
	${StrStr} $nRet $nValue "No Matching devices found"
    
    ; 包含就输出该语句，不包含就输出空
	DetailPrint "StrStr result $nRet"
FunctionEnd

Section
    ; 在这里可以执行其他操作

    ; 调用函数
    Call INSTALL_USBHUB
    
    DetailPrint ""
    
    Call INSTALL_USBHUBB

    ; 继续执行其他操作
SectionEnd 

