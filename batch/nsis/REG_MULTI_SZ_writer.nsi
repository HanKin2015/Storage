;
; 文 件 名: REG_MULTI_SZ_writer.nsi
; 文件描述: 网上找的方案，但是运行写入失败，https://www.wenjiangs.com/doc/eqsr1e08#google_vignette
; 作    者: HanKin
; 创建日期: 2024.07.23
; 修改日期：2024.07.23
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;

OutFile "REG_MULTI_SZ_writer.exe"
Name "REG_MULTI_SZ"
ShowInstDetails show

!define HKEY_CLASSES_ROOT        0x80000000
!define HKEY_CURRENT_USER        0x80000001
!define HKEY_LOCAL_MACHINE      0x80000002
!define HKEY_USERS              0x80000003
!define HKEY_PERFORMANCE_DATA    0x80000004
!define HKEY_PERFORMANCE_TEXT    0x80000050
!define HKEY_PERFORMANCE_NLSTEXT 0x80000060
!define HKEY_CURRENT_CONFIG      0x80000005
!define HKEY_DYN_DATA            0x80000006

!define KEY_QUERY_VALUE          0x0001
!define KEY_SET_VALUE            0x0002
!define KEY_create_SUB_KEY      0x0004
!define KEY_ENUMERATE_SUB_KEYS  0x0008
!define KEY_NOTIFY              0x0010
!define KEY_create_LINK          0x0020

!define REG_NONE                0
!define REG_SZ                  1
!define REG_EXPAND_SZ            2
!define REG_BINARY              3
!define REG_DWORD                4
!define REG_DWORD_LITTLE_ENDIAN  4
!define REG_DWORD_BIG_ENDIAN    5
!define REG_LINK                6
!define REG_MULTI_SZ            7

!define RegcreateKey            "Advapi32::RegcreateKeyA(i, t, *i) i"
!define RegSetValueEx           "Advapi32::RegSetValueExA(i, t, i, i, i, i) i"
!define RegCloseKey             "Advapi32::RegCloseKeyA(i) i"

####### Edit this!
!define ROOT_KEY                "${HKEY_LOCAL_MACHINE}"
!define SUB_KEY                 "SYSTEM\CurrentControlSet\Control\Class\{36FC9E60-C465-11CF-8056-444553540000}"
!define VALUE                   "RegMultiSzTest"
!define DATA_1                  "First string"
!define DATA_2                  "Second string"
####### Stop editing

Section "Write"
  SetPluginUnload alwaysoff
  ; create a buffer for the multi_sz value
  System::Call "*(&t${NSIS_MAX_STRLEN}) i.r1"
  ; Open/create the registry key
  System::Call "${RegcreateKey}(${ROOT_KEY}, '${SUB_KEY}', .r0) .r9"
  ; Failed?
  IntCmp $9 0 write
    MessageBox MB_OK|MB_ICONSTOP "Can't create registry key! ($9)"
    Goto noClose

  write:
    ; Fill in the buffer with our strings
    StrCpy $2 $1                            ; Initial position

    StrLen $9 '${DATA_1}'                  ; Length of first string
    IntOp $9 $9 + 1                        ; Plus null
    System::Call "*$2(&t$9 '${DATA_1}')"    ; Place the string
    IntOp $2 $2 + $9                        ; Advance to the next position

    StrLen $9 '${DATA_2}'                  ; Length of second string
    IntOp $9 $9 + 1                        ; Plus null
    System::Call "*$2(&t$9 '${DATA_2}')"    ; Place the string
    IntOp $2 $2 + $9                        ; Advance to the next position

    System::Call "*$2(&t1 '')"              ; Place the terminating null
    IntOp $2 $2 + 1                        ; Advance to the next position

    ; create/write the value
    IntOp $2 $2 - $1                        ; Total length
    System::Call "${RegSetValueEx}(r0, '${VALUE}', 0, ${REG_MULTI_SZ}, r1, r2) .r9"
    ; Failed?
    IntCmp $9 0 done
      MessageBox MB_OK|MB_ICONSTOP "Can't set key value! ($9)"
      Goto done

  done:
    ; Close the registry key
    System::Call "${RegCloseKey}(r0)"

noClose:
  ; Clear the buffer
  SetPluginUnload manual
  System::Free $1
SectionEnd