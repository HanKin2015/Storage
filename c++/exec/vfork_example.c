/**
* 文 件 名: vfork_example.c
* 文件描述: 学习vfork函数
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
    int cnt = 0;    // 注意这个变量的位置，一定要在vfork函数前面否则结果会不一样，但是没有找到这个解释
    pid_t pid = vfork();
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
son cnt = 21
子进程空间，进程pid为30517
father cnt = 21
父进程空间，进程pid为30516，子进程pid为30517
*/