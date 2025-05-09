# 学习静态库

## 1、编译.a静态文件
```
编译源文件为目标文件: gcc -c mylib.c -o mylib.o
创建静态库: ar rcs libmylib.a mylib.o
验证静态库: nm libmylib.a
```

## 2、使用静态库
两种链接编译方式都可以：
```
gcc main.c -L. -lmylib -o main

gcc main.c ./libmylib.a -o main
```
