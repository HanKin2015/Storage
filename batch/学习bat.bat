@echo off

::注意：bat脚本文件保存字符集类型是ANSI或者是GB2312，UTF-8会执行失败各种中文乱码

::输出当前路径
echo %cd%

::输出空行，注意点(句号)必须要，不要会报错ECHO处于关闭状态
echo.

echo 替换文件完毕，按任意键退出...
pause>nul