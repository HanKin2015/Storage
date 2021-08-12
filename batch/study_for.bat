@echo off

:: 默认的分隔符是空格和tab键
for /f %%i in (data.txt) do echo %%i

:: 无/f参数，单纯输出文件名
for %%i in (data.txt) do echo %%i

:: 修改分隔符为a
for /f "delims=a" %%i in (data.txt) do echo %%i

:: 分隔符为空格，输出分隔中第二个元素，默认输出第一个元素
for /f "tokens=2 delims= " %%i in (data.txt) do echo %%i

:: 支持通配符以及限定范围，必须是按照英文字母顺序排列的，%%j不能换成%%k，因为i后面是j
for /f "tokens=2-3 delims= " %%i in (data.txt) do echo %%i %%j

:: 对于通配符*，就是把这一行全部或者这一行的剩余部分当作一个元素
for /f "tokens=* delims= " %%i in (data.txt) do echo %%i

echo.

:: 用skip来告诉for跳过前2行
for /f "skip=2 tokens=2 delims= " %%i in (data.txt) do echo %%i

:: eol来告诉for忽略以“.”开头的行
for /f "eol=. skip=2 tokens=2 delims= " %%i in (data.txt) do echo %%i