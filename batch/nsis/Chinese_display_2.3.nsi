;
; �� �� ��: Chinese_display_2.3.nsi
; �ļ�����: ʹ��NSIS2.3�汾��ӡ������ģ�ע����ҪANSI����
; ��    ��: HanKin
; ��������: 2024.06.04
; �޸����ڣ�2024.06.04
; 
; Copyright (c) 2024 HanKin. All rights reserved.
;

Outfile "Chinese_display_2.3.exe"

; ������װ����Ϊ���İ�
!include "MUI2.nsh"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

Section
    MessageBox MB_OK "�˷�����"
    DetailPrint "��ǰ���¹⣬���ǵ���˪"
SectionEnd