@echo off

:: 1.ע�ⲻ��ʹ��˫����
:: 2.����ʹ������
:: 3.delims��˼�ǽ��������ݶ�ȡ��a��
for /f "delims=" %%a in (C:\Users\User\Downloads\readme) do set str=%%~a
echo %str%
