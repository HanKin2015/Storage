@echo off

:: 1.ע�ⲻ��ʹ��˫����
:: 2.����ʹ������
:: 3.delims��˼�ǽ��������ݶ�ȡ��a��
for /f "delims=" %%a in (D:\Github\Storage\batch\get_lastline\info) do set str=%%~a
echo %str%
