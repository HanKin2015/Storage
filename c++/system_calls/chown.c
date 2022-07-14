/**
* 文 件 名: chown.c
* 文件描述: chown系统调用函数
* 作    者: HanKin
* 创建日期: 2022.07.12
* 修改日期：2022.07.12
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/ 

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int res = chown("./a.txt", 1001, 1001);
    if (res == -1) {
        perror("chown");
        exit(1);
    }
    printf("chown success!\n");
    return 0;
}