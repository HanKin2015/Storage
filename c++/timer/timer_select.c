/*******************************************************************************
* 文 件 名: timer_select.c
* 文件描述: select定时器是阻塞的，在等待时间到来之前什么都不做。要定时可以考虑再开一个线程来做
* 备    注: 能精确到1us，目前精确定时的最流行方案。通过使用select()，来设置定时器；原理利用select()方法的第5个参数
* 作    者: HanKin
* 创建日期: 2025.03.31
* 修改日期：2025.03.31
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <sys/time.h>
#include <sys/select.h>
#include <time.h>
#include <stdio.h>
 
/*seconds: the seconds; mseconds: the micro seconds*/
void setTimer(int seconds, int mseconds)
{
    struct timeval temp;
    
    temp.tv_sec = seconds;
    temp.tv_usec = mseconds * 1000;
    
    select(0, NULL, NULL, NULL, &temp);
    
    time_t timestamp;
    time(&timestamp);
    printf("%ld: timer\n", timestamp);
    
    return ;
}
 
int main()
{
    for(int i = 0 ; i < 100; i++) {
        setTimer(2, 0); // 2秒打印一次
    }
    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
1743420933: timer
1743420935: timer
1743420937: timer
1743420939: timer
1743420941: timer
*/