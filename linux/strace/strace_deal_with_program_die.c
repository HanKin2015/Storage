/**
* 文 件 名: strace_deal_with_program_die.c
* 文件描述: 使用strace处理程序挂死
* 作    者: HanKin
* 创建日期: 2023.02.23
* 修改日期：2023.02.23
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    getpid(); //该系统调用起到标识作用
    if(argc < 2) {
        printf("hang (user|system)\n");
        return 1;
    }
    if(!strcmp(argv[1], "user")) {
        while(1);
    } else if (!strcmp(argv[1], "system")) {
        sleep(500);
    }
    return 0;
}