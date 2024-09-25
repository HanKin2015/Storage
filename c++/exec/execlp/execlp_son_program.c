/**
* 文 件 名: execlp_son_program.c
* 文件描述: execlp函数调用子程序
* 备    注: gcc execlp_son_program.c -o execlp_son_program
* 作    者: HanKin
* 创建日期: 2021.04.13
* 修改日期：2021.04.13
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/
#include <stdio.h>
#include "log.h"

bool ProcessCmdLine(int argc, char *argv[])
{
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (!ProcessCmdLine(argc, argv)) {
        printf("[main] parse cmd line failed");
        return -1;
    }

    FILE *fp = fopen("./log.txt", "a");
    fprintf(fp, "%s %s [%s: %d: %s]\n", __DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__);
    fclose(fp);
    
    LOG_INFO(); // 测试log.h文件
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
argc: 1
./execlp_son_program
Apr 13 2021 21:06:07 [creat_file.cpp: 23: main]
*/