/**
* 文 件 名: chmod.c
* 文件描述: chmod系统调用函数
* 作    者: HanKin
* 创建日期: 2022.07.12
* 修改日期：2022.07.12
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/ 

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int res = chmod("./a.txt", 0777);
    if (res == -1) {
        perror("chmod");
        exit(1);
    }
    printf("chmod success!\n");
    
    int fd = open("./b.txt", O_RDWR);
    if (fd == -1) {
       perror("open fail");
       exit(1);
    }
    if (fchmod(fd, 0777) == -1) {
        perror("fchmod fail");
        exit(1);
    }
    printf("fchmod success!\n");
    close(fd);
    return 0;
}