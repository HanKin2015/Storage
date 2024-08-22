;
; 文 件 名: initiation.nsi
; 文件描述: 启蒙(检查服务是否存在)
; 作    者: HanKin
; 创建日期: 2024.06.04
; 修改日期：2024.06.04
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;

!define PRODUCT_NAME "TestApp"
!define PRODUCT_VERSION "1.0.0.0"
!define PRODUCT_COMPANY "Test Company"

VIProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey FileDescription "${PRODUCT_NAME} Installer"
VIAddVersionKey FileVersion "${PRODUCT_VERSION}"
VIAddVersionKey ProductName "${PRODUCT_NAME} Installer" 
VIAddVersionKey ProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey CompanyName "${PRODUCT_COMPANY}"
VIAddVersionKey LegalCopyright "Copyright (C) 2015-2020 ${PRODUCT_COMPANY}"

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


Function .onInit
FunctionEnd

Var nRet
Section "!Test" SecTest
    ;测试服务是否存在
	SimpleSC::ExistsService "jk"
	Pop $nRet ;Pop $nRet ; returns an errorcode if the service doesn′t exists (<>0)/service exists (0)
	
	MessageBox MB_OK|MB_ICONEXCLAMATION "nRet = $nRet" /SD IDOK
SectionEnd