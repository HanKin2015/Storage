::
:: �� �� ��: errorlevel.bat
:: �ļ�����: %errorlevel% ��һ�������ϵͳ���������洢�����ִ�е�������˳�״̬
:: ��    ע: �������ɹ�ִ�У�%errorlevel% ͨ���ᱻ����Ϊ 0���������ִ��ʧ�ܣ�%errorlevel% ͨ���ᱻ����Ϊ����ֵ
:: ��    ��: HanKin
:: ��������: 2024.08.28
:: �޸����ڣ�2024.08.28
:: 
:: Copyright (c) 2024 HanKin. All rights reserved.
::

@echo off
:: ִ��һ������
dir non_existent_file.txt

:: ��ӡ������˳�״̬
echo %errorlevel%
pause