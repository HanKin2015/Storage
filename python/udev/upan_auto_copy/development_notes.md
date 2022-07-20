# 开发笔记

## 1、开发步骤
- 修改src中源码文件
- 修改doc中file_version_info.txt内容
- pyinstaller.exe --version-file=doc/file_version_info.txt -i doc/dog.ico -F src/upan_auto_copy.py
- 取出exe文件，删除多余的文件夹

## 2、改进点
- 日志改进
2022-05-31 21:36:24 test.py[main:31] WARNING: hello world

- 程序停止改进
使用ctrl+c的方式可能会给U盘带来未知的损伤，可以尝试在拷贝进行的时候读取本地文件方式判断是否停止

- bug修改
查看帮助文档，日志打印：U盘自动拷贝程序开始

- 优化点
想做个文件负责数据统计，并不是现在需要写个脚本去日志中解析收集

- 帮助文档优化
自己在几个月后都有些忘记如何调试了，还要来看源码

- 小数点保留位数有问题
代码中写保留3位，但是遇到如3.140时会输出3.14

- 英文版系统运行会报编码错误

- 英文版在开启DEBUG日志后无法正常运行

