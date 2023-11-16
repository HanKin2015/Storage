/**
* 文 件 名: readlink_example.c
* 文件描述: 学习readlink函数
* 作    者: HanKin
* 备    注: 判断文件是否为符号链接并读取程序自身路径
* 创建日期: 2023.11.15
* 修改日期：2023.11.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int ret;
    struct stat st;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    argv[1] = "/proc/self/exe";

    ret = lstat(argv[1], &st);
    if (ret == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if (S_ISLNK(st.st_mode)) {
        char buf[1024] = { 0 };
        ssize_t len;

        len = readlink(argv[1], buf, sizeof(buf)-1);
        if (len < 0) {
            perror("readlink");
            exit(EXIT_FAILURE);
        }
        buf[len] = '\0';
        printf("%s is a symbolic link to %s\n", argv[1], buf);
    } else {
        printf("%s is not a symbolic link\n", argv[1]);
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out 4
/proc/self/exe is a symbolic link to /root/cmake/a.out
*/