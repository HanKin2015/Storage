/*******************************************************************************
* 文 件 名: setitimer_example.c
* 文件描述: 跟timer_alarm.c差不多
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.31
* 修改日期：2025.03.31
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

static int count = 0;
static struct itimerval oldtv;

void set_timer()
{
    struct itimerval itv;
    itv.it_interval.tv_sec = 1;	// 间隔1秒执行一次信号函数
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &itv, &oldtv);
}

void signal_handler(int m)
{
    count++;
    time_t timestamp;
    time(&timestamp);
    printf("%ld: count = %d (count < 10)\n", timestamp, count);
}

int main()
{
    signal(SIGALRM, signal_handler);
    set_timer();
    while(count < 10);
    exit(0);
    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
1743421190: count = 1 (count < 10)
1743421191: count = 2 (count < 10)
1743421192: count = 3 (count < 10)
1743421193: count = 4 (count < 10)
1743421194: count = 5 (count < 10)
1743421195: count = 6 (count < 10)
1743421196: count = 7 (count < 10)
1743421197: count = 8 (count < 10)
1743421198: count = 9 (count < 10)
1743421199: count = 10 (count < 10)
*/