::
:: 文 件 名: 一键重命名文件并删除并覆盖.bat
:: 文件描述: 一键重命名文件并删除并覆盖
:: 作    者: HanKin
:: 创建日期: 2021.08.09
:: 修改日期：2022.01.19
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

@echo off

::注意：bat脚本文件保存字符集类型是ANSI或者是GB2312，UTF-8会执行失败各种中文乱码

::ren命令是将文件重命名，注意重命名的文件不要带路径
ren "D:\Users\User\Desktop\技术支持\V123" 编译环境.png

::删除重命名的文件
del "D:\Users\User\Desktop\技术支持\编译环境.png"

::剪切新文件到指定路径
move v4l2-ctl "D:\Users\User\Desktop\技术支持\"

::空行，点必现要，不要会报错ECHO处于关闭状态
echo.
echo 替换文件完毕，按任意键退出...
pause>nul