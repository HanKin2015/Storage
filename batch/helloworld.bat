@echo off

Rem ���hello world
echo hello world

goto here

:: ��������ַ����洢��input������
set /p "input=>"
echo ���������%input%

start slave

:here
echo jump to here

:: ����
call:slave
pause