::
:: �� �� ��: remove_handle.bat
:: �ļ�����: ��Ҫ����ɾ���ļ������ļ��б�ռ�õľ��
:: ��    ע: https://superuser.com/questions/335138/how-to-close-all-file-handles-under-a-given-folder-programatically/787179#787179
::           https://blog.csdn.net/weixin_33964094/article/details/91425643
::           https://learn.microsoft.com/zh-cn/sysinternals/downloads/handle
:: ��    ��: HanKin
:: ��������: 2023.02.22
:: �޸����ڣ�2023.02.22
:: 
:: Copyright (c) 2023 HanKin. All rights reserved.
::

@echo off

for /f "skip=5 tokens=3,6,8 delims=: " %%i in ('handle64 %1') do echo Releasing %%k & handle64 -c %%j -y -p %%i