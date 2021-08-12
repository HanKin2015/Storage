@echo off

:: 入参
echo param0=%0
echo param1=%1
echo param2=%2

:: for循环
for %%i in (1, 3, 5, 8) do echo %%i

:: 当成字符串输出
set var1=1
set /a var2=var1+1
echo var1
echo var2

:: 正确输出变量值
set var3=%var2%
echo %var1%
echo %var2%
echo %var3%

:: 批处理脚本执行机制导致,会按行执行,在执行之前会先预处理,提前将%var%替换成110
set var1=110
set var1=120&echo %var1%

:: 开启延迟环境变量扩展
setlocal enabledelayedexpansion
set var1=110
set var1=120&echo !var1!

:: 变量名区分大小写
set ab=123
set AB=456
echo %ab%
echo %AB%

:: 赋值等号前后是否可以有空格(不可以)
set cde = 22
echo %cde%

:: 输出未定义的变量会怎样(报错: ECHO 处于关闭状态)
echo %gg%

pause
