# qmake

## 1、简介
qmake 是 Qt 的一个构建系统工具，主要用于生成 Makefile，以便使用 make 命令编译 Qt 项目。qmake 本身并不直接编译 C++ 文件，而是通过生成的 Makefile 来调用编译器（如 g++ 或 clang++）进行编译。

## 2、使用
```
qmake myproject.pro
qmake myproject.pro -spec /root/code/prebuilts/include/x86_64-linux-gnu/qt-mkspecs
make
```
