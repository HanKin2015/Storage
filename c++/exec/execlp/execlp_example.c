#include <stdio.h>
#include <errno.h>
#include <string.h>
/**
* 文 件 名: execlp_example.c
* 文件描述: 学习execlp函数
* 作    者: HanKin
* 创建日期: 2021.04.13
* 修改日期：2021.04.13
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/
#include <unistd.h>
#include "log.h"

int main()
{
    int ret = execlp("./execlp_son_program",
        "./execlp_son_program",
        "-h", "help", 
        "-p", "port",
        "-t", "time",
        NULL);

    printf("execlp ret %d, errno=%d, strerror=%s", ret, errno, strerror(errno));
    LOG_INFO();
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
argc: 7
./execlp_son_program
-h
help
-p
port
-t
time
Apr 13 2021 21:06:07 [creat_file.cpp: 23: main]
*/