/**
* 文 件 名: umask_example.cpp
* 文件描述: 学习umask函数
* 作    者: HanKin
* 创建日期: 2023.06.30
* 修改日期：2023.06.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#ifdef _WIN32
#define open _open
#define close _close
#define read _read
#define write _write
#define lseek _lseek
#define O_CREAT _O_CREAT
#define O_TRUNC _O_TRUNC
#define O_RDONLY _O_RDONLY
#define O_WRONLY _O_WRONLY
#define O_RDWR _O_RDWR
#endif
using namespace std;

/*
在C语言中，umask是一个系统调用，用于设置进程的文件创建掩码，它可以限制文件的默认权限。文件创建掩码是一个权限掩码，用于限制新建文件的默认权限。它与文件的默认权限进行按位与运算，从而得到文件的实际权限。umask函数的原型如下：
mode_t umask(mode_t mask);

其中，mask是一个权限掩码，表示要屏蔽的权限位。umask函数返回之前的文件创建掩码。

umask函数的作用是屏蔽掉进程创建文件时的某些权限，例如屏蔽掉其他用户的写权限，从而保护文件的安全性。umask函数的返回值是之前的文件创建掩码。
*/

static int test()
{
    mode_t old_mask = umask(S_IWGRP | S_IWOTH); // 屏蔽组写和其他用户写权限
    int fd = open("file.txt", O_CREAT | O_WRONLY, 0644); // 创建文件，权限为rw-r--r--
    umask(old_mask);    // 恢复之前的文件创建掩码
    return 0;
}

static int printf_mode_t()
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // 创建一个文件权限为644的mode_t变量
    printf("mode = %o\n", mode); // 使用八进制格式化字符串打印mode_t变量
    printf("mode = %x\n", mode); // 使用十六进制格式化字符串打印mode_t变量
    return 0;
}

static int umask_example()
{
    mode_t old_mask = umask(0); // 获取之前的文件创建掩码，并设置新的掩码0000
    printf("a.out file create old umask: 0%03o\n", old_mask);
    mode_t new_create_file_right = 0666 & (~old_mask);  // 新创建的文件读写权限
    printf("new_create_file_right: 0%03o\n", new_create_file_right);
    int fd = open("test1.txt", O_CREAT | O_WRONLY, 0666); // 创建一个文件
    mode_t new_mask = umask(old_mask); // 恢复之前的文件创建掩码
    printf("a.out file create new umask: 0%03o\n", new_mask);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    write(fd, "Hello, world!", 13); // 写入数据
    close(fd); // 关闭文件
    return 0;
}

int main(int argc, char *argv[])
{
    int fd = open("test0.txt", O_CREAT | O_WRONLY, 0666); // 创建一个文件
    if (fd == -1) {
        perror("open");
        return 1;
    }
    write(fd, "Hello, world!", 13); // 写入数据
    close(fd); // 关闭文件
    
    umask_example();
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
a.out file create old umask: 0022
new_create_file_right: 0644
a.out file create new umask: 0000
[root@ubuntu0006:~/cmake] #ll test*.txt
-rw-r--r-- 1 root root 13 9月  23 21:35 test0.txt
-rw-rw-rw- 1 root root 13 9月  23 21:35 test1.txt

理解：
test0.txt: 0666 & (~0022) = 644
test1.txt: 0666 & (~0000) = 666
*/