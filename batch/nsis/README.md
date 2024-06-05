# NSIS学习
官网：https://nsis.sourceforge.io/Download

## 1、中文乱码问题
https://blog.csdn.net/xiaowa2012/article/details/123731614

问题1：在英文系统环境在安装界面中文显示乱码
解决方案：在NSI脚本增加
```!include "MUI2.nsh"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"
```
这样安装界面语言会适配当前操作系统语言

问题2：QA测试把英文操作系统的语言改为中文，安装界面中文依旧显示乱码
解决方案：在NSI脚本增加
```
Unicode True
```
备注：一开始在NSI增加这行后导致打包脚本编译失败，后来才知道，原因云编译环境安装的NSI脚本是2.0.XXX版本。查了下资料才知道Unicode编码在NSI 3.0版本才支持的，NSIS用户手册说明。

Unicode 的安装程序
从 MakeNSIS V3.0 开始，您便可以选择通过设置 Unicode 属性来创建Unicode的安装程序。这些安装程序不能在Windows95/98/ME下工作，但他们允许你在任何支持 Unicode 语言的系统下显示您的安装程序。

当构建一个 Unicode 的安装程序时，NSIS变量可以保存 Unicode 字符（0000-FFFF）。并且不需要修改现有的脚本。如果你想读/写Unicode文件，具体的说明请查看FileReadUTF16。
NSIS-3.10版本编译通过

## 2、NSIS-3.10版本里不能中文注释
NSIS脚本中文报错 Bad text encoding：将nsi文件的编码格式从utf8改为gb2312（ANSI编码）。

Nsis脚本应该采用ANSI编码，其他格式编码编译不过去，或者在makensis上显示乱码。

