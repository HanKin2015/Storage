/*******************************************************************************
* 文 件 名: timer_alarm.c
* 文件描述: alarm方式虽然很好，但这种方式的精度能达到1秒，是无法低于1秒的精度
* 作    者: HanKin
* 创建日期: 2025.03.31
* 修改日期：2025.03.31
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
 
void timer(int sig)
{
    if (SIGALRM == sig) {    // kill -l 14(SIGALRM)
        time_t timestamp;
        time(&timestamp);
        printf("%ld: timer\n", timestamp);
        alarm(1);       //重新继续定时1s
    }
    return;
}
 
int main()
{
    signal(SIGALRM, timer); // 注册安装信号
    
    time_t timestamp;
    time(&timestamp);
    printf("%ld: start\n", timestamp);
    
    alarm(5);       // 触发定时器（5s延时信号）

    time(&timestamp);
    printf("%ld: end\n", timestamp);
    getchar();
    
    return 0;
}
/*
[root@ubuntu0006:~] #gcc j.c
[root@ubuntu0006:~] #./a.out
1743406600: start
1743406600: end
1743406605: timer
1743406606: timer
1743406607: timer
1743406608: timer
1743406609: timer
1743406610: timer
1743406611: timer
1743406612: timer
1743406613: timer
1743406614: timer
*/