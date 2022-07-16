/**
* 文 件 名: truncate.c
* 文件描述: truncate系统调用函数
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
#include<sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int res = truncate("./a.txt", 100);     // //将其扩大为100
    //int res = truncate("./a.txt", 25);    // 将其缩小为25
    if (res == -1) {
        perror("truncate");
        exit(1);
    }
    printf("truncate success!\n");
    return 0;
}