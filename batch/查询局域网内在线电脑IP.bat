COLOR 0A
CLS
@ECHO Off
Title ��ѯ�����������ߵ���IP
:send
@ECHO off&setlocal enabledelayedexpansion 

ECHO ���ڻ�ȡ������IP��ַ�����Ե�... 
for /f "tokens=2 skip=2 delims=:" %%i in ('nbtstat -n') do ( 
set "IP=%%i" 
ECHO !IP!
set IP=!IP:~2,-7!
ECHO ����IPΪ��!IP!
goto :next 
)

:next 
for /f "delims=. tokens=1,2,3,4" %%i in ("%IP%") do set range=%%i.%%j.%%k 
ECHO.&ECHO ���ڻ�ȡ�������ڵ��������߼�����������Ե�... 
ECHO �����Ρ�%range%.*���ڵļ�����У�
for /f "delims=" %%i in ('net view') do ( 
set "var=%%i" 
::��ѯ���߼��������
if "!var:~0,2!"=="\\" ( 
set "var=!var:~2!" 
ECHO !var! 
ping -n 1 !var!>nul 
)) 
ECHO.
ECHO ���ڻ�ȡ�������ڵ��������߼����IP�����Ե�... 
for /f "skip=3 tokens=1,* delims= " %%i in ('arp -a') do ECHO IP�� %%i ����ʹ��

ECHO.
ECHO ��ѯ��ϣ���������˳�...
pause>nul