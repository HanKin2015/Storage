::
:: 文 件 名: 学习batch脚本.bat
:: 文件描述: 学习batch脚本
:: 学习网站：https://baike.baidu.com/item/%E6%89%B9%E5%A4%84%E7%90%86/1448600?fromtitle=Batch&fromid=1079355&fr=aladdin
:: Rem和::都是注释，推荐::，美观简洁；脚本推荐使用ANCI编码，否则可能出现中文乱码
:: 注    意：bat脚本文件保存字符集类型是ANSI或者是GB2312，UTF-8会执行失败各种中文乱码；输出的字符串不需要双引号
:: 作    者: HanKin
:: 创建日期: 2021.06.04
:: 修改日期：2022.08.04
:: 
:: Copyright (c) 2020 HanKin. All rights reserved.
::

:: 关闭回显(只会显示脚本中输出内容，否则会显示当前路径以及执行的命令)
@echo off

:: 1、echo命令：打开回显或关闭请求回显功能，或显示消息。
echo hello world

:: 2、rem命令：注释功能，可用::代替
Rem 你好

:: 3、pause命令：暂停命令
Rem 显示Press any key to continue. . .(或：请按任意键继续. . .)

:: 4、call命令：从一个批处理程序调用另一个批处理程序，并且不终止父批处理程序
call:slave.bat

:: 5、start命令：调用外部程序，所有的DOS命令和命令行程序都可以由start命令来调用。
start slave.bat

::6 、goto命令：跳转命令。程序指针跳转到指定的标签，从标签后的第一条命令开始继续执行批处理程序。
goto here
:here
echo jump to here

:: 7、set命令：显示、设置或删除变量。
set aa=abcd
echo %aa%
set aa=
echo %aa%

:: 8、assoc命令：添加文件扩展名
assoc .txp=错误

:: 9、将输入的字符串存储到input变量中
set /p "input=>"
echo 您输入的是%input%

:: 10、输出空行，注意点(句号)必须要，不要会报错ECHO处于关闭状态
echo.

:: 11、输出当前路径
echo %cd%

:: 12、可以将默认的退出字段进行更换(默认请按任意键退出...)
echo 替换文件完毕，按任意键退出...
::pause>nul
pause