/**
* 文 件 名: vfork_example2.c
* 文件描述: 学习vfork函数，死锁
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
        //exit(0);    // 必须要有这个，否则会进入死锁
    } else {
        cnt++;
        printf("father cnt = %d\n", cnt);
        printf("父进程空间，进程pid为%d，子进程pid为%d\n", getpid(), pid);
    }
    // 注意！存在着父进程在子进程结束前结束的可能性。必要的时候可以使用wait或 waitpid函数让父进程等待子进程的结束并获取子进程的返回状态
    //exit(0);
    return 0;
}
/*
尽管子进程没有调用 _exit 或 exec，它没有进入死锁的原因可能是因为以下几点：
子进程的快速退出：
子进程执行完 printf 语句后，立即返回到父进程的代码中，并且父进程和子进程几乎同时退出。这种情况下，虽然不安全，但可能没有明显的死锁现象。

调度器的行为：
操作系统的调度器可能在子进程执行完 printf 语句后立即调度父进程执行，从而避免了明显的死锁。

两个地方的exit缺一不可，如果都缺一定会进入死锁：
[root@ubuntu0006:~/cmake] #./a.out
son cnt = 1
子进程空间，进程pid为31681
father cnt = -874057642
父进程空间，进程pid为31680，子进程pid为31681
a.out: cxa_atexit.c:100: __new_exitfn: Assertion `l != NULL' failed.
已放弃
*/