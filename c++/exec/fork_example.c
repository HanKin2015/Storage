/**
* 文 件 名: fork_example.c
* 文件描述: 学习fork函数
* 作    者: HanKin
* 创建日期: 2024.09.24
* 修改日期：2024.09.24
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    pid_t pid = fork();
    int cnt = 0;
    if ( pid < 0 ) {
        fprintf(stderr, "错误！");
    } else if ( pid == 0 ) {
        cnt++;
        printf("son cnt = %d\n", cnt);
        printf("子进程空间，进程pid为%d\n", getpid());
        exit(0);
    } else {
        cnt++;
        printf("father cnt = %d\n", cnt);
        printf("父进程空间，进程pid为%d，子进程pid为%d\n", getpid(), pid);
    }
    // 注意！存在着父进程在子进程结束前结束的可能性。必要的时候可以使用wait或 waitpid函数让父进程等待子进程的结束并获取子进程的返回状态
    exit(0);
}
/*
[root@ubuntu0006:~/cmake] #./a.out
father cnt = 1
父进程空间，进程pid为29919，子进程pid为29920
son cnt = 1
子进程空间，进程pid为29920
*/