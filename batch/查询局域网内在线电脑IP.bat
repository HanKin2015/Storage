COLOR 0A
CLS
@ECHO Off
Title 查询局域网内在线电脑IP
:send
@ECHO off&setlocal enabledelayedexpansion 

ECHO 正在获取本机的IP地址，请稍等... 
for /f "tokens=2 skip=2 delims=:" %%i in ('nbtstat -n') do ( 
set "IP=%%i" 
ECHO !IP!
set IP=!IP:~2,-7!
ECHO 本机IP为：!IP!
goto :next 
)

:next 
for /f "delims=. tokens=1,2,3,4" %%i in ("%IP%") do set range=%%i.%%j.%%k 
ECHO.&ECHO 正在获取本网段内的其它在线计算机名，请稍等... 
ECHO 本网段【%range%.*】内的计算机有：
for /f "delims=" %%i in ('net view') do ( 
set "var=%%i" 
::查询在线计算机名称
if "!var:~0,2!"=="\\" ( 
set "var=!var:~2!" 
ECHO !var! 
ping -n 1 !var!>nul 
)) 
ECHO.
ECHO 正在获取本网段内的其它在线计算机IP，请稍等... 
for /f "skip=3 tokens=1,* delims= " %%i in ('arp -a') do ECHO IP： %%i 正在使用

ECHO.
ECHO 查询完毕，按任意键退出...
pause>nul