/**
* 文 件 名: wait_waitpid_example.c
* 文件描述: 学习wait和waitpid函数
* 作    者: HanKin
* 创建日期: 2024.09.25
* 修改日期：2024.09.25
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int wait_example()
{
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        printf("子进程\n");
        _exit(0);
    } else {
        // 父进程
        int status;
        wait(&status);
        printf("子进程结束，状态：%d\n", status);
    }
    return 0;
}

int waitpid_example()
{
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        printf("子进程\n");
        _exit(0);
    } else {
        // 父进程
        int status;
        waitpid(pid, &status, 0);
        printf("子进程 %d 结束，状态：%d\n", pid, status);
    }
    return 0;
}

int main(int argc,char *argv[])
{
    wait_example();
    waitpid_example();
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
子进程
子进程结束，状态：0
子进程
子进程 326 结束，状态：0
*/