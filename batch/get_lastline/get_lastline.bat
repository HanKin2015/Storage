@echo off

:: 1.注意不能使用双引号
:: 2.多行使用括号
:: 3.delims意思是将所有内容读取到a中
for /f "delims=" %%a in (D:\Github\Storage\batch\get_lastline\info) do set str=%%~a
echo %str%
