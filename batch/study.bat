::
:: ѧϰbatch�ű�
:: ѧϰ��վ��https://baike.baidu.com/item/%E6%89%B9%E5%A4%84%E7%90%86/1448600?fromtitle=Batch&fromid=1079355&fr=aladdin
:: Rem��::����ע�ͣ��Ƽ�::�����ۼ�ࣻ�ű��Ƽ�ʹ��ANCI���룬������ܳ�����������
::
:: ���ߣ�hankin
:: ���ڣ�2021.06.04
::
:: Copyright (c) 2020 hejian. All rights reserved.
::

:: �رջ���
@echo off

:: 1��echo����򿪻��Ի�ر�������Թ��ܣ�����ʾ��Ϣ��
echo hello world

:: 2��rem���ע�͹��ܣ�����::����
Rem ���

:: 3��pause�����ͣ����
Rem ��ʾPress any key to continue. . .(���밴���������. . .)

:: 4��call�����һ����������������һ����������򣬲��Ҳ���ֹ�����������
call:slave.bat

:: 5��start��������ⲿ�������е�DOS����������г��򶼿�����start���������á�
start slave.bat

::6 ��goto�����ת�������ָ����ת��ָ���ı�ǩ���ӱ�ǩ��ĵ�һ�����ʼ����ִ�����������
goto here
:here
echo jump to here

:: 7��set�����ʾ�����û�ɾ��������
set aa=abcd
echo %aa%
set aa=
echo %aa%

:: 8��assoc�������ļ���չ��
assoc .txp=����


:: ��������ַ����洢��input������
set /p "input=>"
echo ���������%input%

pause