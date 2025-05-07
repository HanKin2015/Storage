/*******************************************************************************
* 文 件 名: signal_example.c
* 文件描述: 学习信号
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.06
* 修改日期：2025.05.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t stop = 0; // 用于标志信号

void signal_handler(int signum)
{
    printf("Received signal %d\n", signum);
    stop = 1; // 设置标志位
}

static void signal_register()
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = signal_handler;
    // 注册信号处理
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
}

int main()
{
    signal_register();

    while (!stop) {
        time_t timestamp = time(NULL);
        printf("current time: %s", ctime(&timestamp));  // 自带换行符
        sleep(1);
    }

    printf("main exit\n");
    return 0;
}
/*
kill -14 `pidof a.out`
[root@ubuntu0006:~/cmake] #./a.out
current time: Tue May  6 10:40:41 2025
current time: Tue May  6 10:40:42 2025
current time: Tue May  6 10:40:43 2025
current time: Tue May  6 10:40:44 2025
current time: Tue May  6 10:40:45 2025
current time: Tue May  6 10:40:46 2025
闹钟

kill -15 `pidof a.out`
[root@ubuntu0006:~/cmake] #./a.out
current time: Tue May  6 10:41:10 2025
current time: Tue May  6 10:41:11 2025
current time: Tue May  6 10:41:12 2025
current time: Tue May  6 10:41:13 2025
Received signal 15
main exit
*/