;
; 文 件 名: study_nsis.nsi
; 文件描述: 学习
; 作    者: HanKin
; 创建日期: 2024.07.23
; 修改日期：2024.07.23
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;

; 引入头文件，文件不存在可能拷贝到当前目录
;!include "Registry.nsh"
!include "x64.nsh" ; 如果需要在64位系统上运行，请包含此文件

; 宏定义
!define PRODUCT_NAME "TestApp"
!define PRODUCT_VERSION "1.0.0.0"
!define PRODUCT_COMPANY "Test Company"
!define FILE_VERSION "1.2.3.4"

; exe文件属性
VIAddVersionKey FileDescription "${PRODUCT_NAME} Installer" ; 文件说明
                                                            ; 类型
VIProductVersion "${PRODUCT_VERSION}"                       ; 文件版本
VIAddVersionKey ProductName "${PRODUCT_NAME} Installer"     ; 产品名称
VIAddVersionKey ProductVersion "${PRODUCT_VERSION}"         ; 产品版本
VIAddVersionKey LegalCopyright "Copyright (C) 2015-2024 ${PRODUCT_COMPANY}" ; 版权
VIAddVersionKey FileVersion "${FILE_VERSION}"               ; 无用
VIAddVersionKey CompanyName "${PRODUCT_COMPANY}"            ; 无用

;General

;Properly display all languages (Installer will not work on Windows 95, 98 or ME!)

;Name and file
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"       ; 窗口标题名称
OutFile "TestInstaller v${PRODUCT_VERSION}.exe" ; 输出的exe文件名称

;Default installation folder
InstallDir "$PROGRAMFILES\TestCompany\TestApp"

;Get installation folder from registry if available
;InstallDirRegKey HKCU "Software\Modern UI Test" ""

;Request Admin privileges for Windows Vista
RequestExecutionLevel admin
  
;--------------------------------


!define PRODUCT_INST_ROOT_KEY "HKLM"
!define PRODUCT_INST_KEY "SYSTEM\CurrentControlSet\Control\Class\{36FC9E60-C465-11CF-8056-444553540000}"
Function WriteRegedit
    DetailPrint "开始注册表操作，https://blog.csdn.net/lvmengzou/article/details/105644308"
    
    ; 不存在的键会自动创建REG_EXPAND_SZ/REG_DWORD/REG_SZ
    ; win11会对usb过滤设备的class类注册表进行检查（比win10更为严格，校验条件更多），识别到REG_EXPAND_SZ类型的键后会识别为usb过滤驱动class配置异常，导致键鼠设备异常
    WriteRegExpandStr ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}" "LowerFilters" "hj_test"
    WriteRegStr       ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}" "Name" "hj"
	WriteRegDWORD     ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}" "Age" 30
    
    ; 删除键，不存在的键不报错
    DeleteRegValue    ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}" "Age"
    DeleteRegValue    ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}" "Sex"
    
    ; 删除注册表项，如果指定了/ ifempty，则只有在没有子项的情况下才会删除注册表项（否则，将删除整个注册表树）
    DeleteRegKey /ifempty ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}"
    
    ; NSIS本身不直接支持多字符串（REG_MULTI_SZ）类型值的操作
    ; 设置要写入的多字符串值
    StrCpy $0 "service1 service2"
    ; 写入注册表，但是也有一个问题，这样也是覆盖啊，不能追加
    WriteRegMultiStr /REGEDIT5 ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}" "Hobby" 66,00,6f,00,6f,00,00,00,62,00,61,00,72,00,00,00,00,00
    WriteRegMultiStr /REGEDIT5 ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}" "Other" 54,00,63,00,70,00,00,00,70,00,00,00,41,00,00,00,00,00
    
FunctionEnd

Var nRet
Section "!Test" SecTest
    ; 服务存在返回0，不存在返回1060
    ;SimpleSC::ExistsService "BFE"
    Pop $nRet ;Pop $nRet ; returns an errorcode if the service doesn′t exists (<>0)/service exists (0)

    MessageBox MB_OK|MB_ICONEXCLAMATION "nRet = $nRet" /SD IDOK
SectionEnd

Section
    DetailPrint "开始安装"  ; 打印内容
    Call WriteRegedit       ; 调用函数
SectionEnd