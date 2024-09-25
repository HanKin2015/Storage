/**
* 文 件 名: _exit_and_exit_example.c
* 文件描述: exit和_exit函数区别
* 作    者: HanKin
* 创建日期: 2024.09.25
* 修改日期：2024.09.25
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cleanup() {
    printf("Cleanup function called.\n");
}

int main(int argc, char *argv[])
{
    // 注册一个清理函数
    atexit(cleanup);
    
    if (argc > 1) {
        printf("Using exit:\n");
        printf("This will be printed.\n");
        exit(0);
    } else {
        printf("Using _exit:\n");
        printf("This will not be printed.\n");
        _exit(0);
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
Using _exit:
This will not be printed.
[root@ubuntu0006:~/cmake] #./a.out 2
Using exit:
This will be printed.
Cleanup function called.
*/