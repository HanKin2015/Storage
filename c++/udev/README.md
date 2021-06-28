# 1、简介
zip文件存储大量usb设备信息数据。

数据存储在json文件中，需要对usb设备信息数据进行收集在一起。

# 2、要求
1. 去重
2. 快速查找

# 3、数据结构算法
## 数据存储
存储设备的唯一标识pvid

map<string, struct>

使用字典树算法可以快速进行查找

## 需要文件锁

## 需要Makefile文件

## 需要单元测试

## 需要多线程进行解压缩

# 去除7z程序解压

# 4、计划
1. 增加日志模块
2. 增加Makefile文件或者增加cmake编译文件

gcc安装包：https://ftp.gnu.org/gnu/gcc/
g++安装包：https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/

# 5、部分问题及解决
## error: template with C linkage
不要在extern "C"的中引用C++ STL库的头文件，如<map>, <vector>等具有template的头文件。
需要检查extern "C"后面为函数；extern "C" { }的定义是否完整。
