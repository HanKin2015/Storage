@echo off

Rem 输出hello world
echo hello world

goto here

:: 将输入的字符串存储到input变量中
set /p "input=>"
echo 您输入的是%input%

start slave

:here
echo jump to here

:: 调用
call:slave
pause