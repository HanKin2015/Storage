/**
* 文 件 名: time_sleep_example.cpp
* 文件描述: sleep函数是否可以睡眠0.5秒，答案是不可以
* 作    者: HanKin
* 创建日期: 2023.02.13
* 修改日期：2023.02.13
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>

int main(int argc, char *argv[])
{
    int index = 1;
    while (true) {
        time_t timep = time(NULL);
        struct tm *lt = localtime(&timep);
        char ntime[BUFSIZ] = { 0 };
        strftime(ntime, sizeof(ntime), "%Y-%m-%d %H:%M:%S", lt);
        printf("usleep now time: %s\n", ntime);
        // sleep(0.5);  // 精度只能到秒
        usleep(500000);
        if (index++ > 10) break;
    }
    
    while (true) {
        time_t timep = time(NULL);
        struct tm *lt = localtime(&timep);
        char ntime[BUFSIZ] = { 0 };
        strftime(ntime, sizeof(ntime), "%Y-%m-%d %H:%M:%S", lt);
        printf("nanosleep now time: %s\n", ntime);
        
        struct timespec req;
        req.tv_sec = 0;
        req.tv_nsec = 1000000000 - 1;   // 这个是long类型，纳秒字段的值必须在0到999999999之间。
        nanosleep(&req, NULL);
        
        if (index++ > 20) break;
    }
    
    while (true) {
        time_t timep = time(NULL);
        struct tm *lt = localtime(&timep);
        char ntime[BUFSIZ] = { 0 };
        strftime(ntime, sizeof(ntime), "%Y-%m-%d %H:%M:%S", lt);
        printf("select now time: %s\n", ntime);
        
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 2*1000000;
        select(0, NULL, NULL, NULL, &tv);
        
        if (index++ > 30) break;
    }
    
    while (true) {
        time_t timep = time(NULL);
        struct tm *lt = localtime(&timep);
        char ntime[BUFSIZ] = { 0 };
        strftime(ntime, sizeof(ntime), "%Y-%m-%d %H:%M:%S", lt);
        printf("sleep now time: %s\n", ntime);
        sleep(1);
        if (index++ > 40) break;
    }
    return 0;
}
/*
[root@ubuntu0006:/media/vdb] #vi time_sleep_example.cpp
[root@ubuntu0006:/media/vdb] #g++ time_sleep_example.cpp
[root@ubuntu0006:/media/vdb] #./a.out
usleep now time: 2023-02-13 17:07:08
usleep now time: 2023-02-13 17:07:09
usleep now time: 2023-02-13 17:07:09
usleep now time: 2023-02-13 17:07:10
usleep now time: 2023-02-13 17:07:10
usleep now time: 2023-02-13 17:07:11
usleep now time: 2023-02-13 17:07:11
usleep now time: 2023-02-13 17:07:12
usleep now time: 2023-02-13 17:07:12
usleep now time: 2023-02-13 17:07:13
usleep now time: 2023-02-13 17:07:13
nanosleep now time: 2023-02-13 17:07:14
nanosleep now time: 2023-02-13 17:07:15
nanosleep now time: 2023-02-13 17:07:16
nanosleep now time: 2023-02-13 17:07:17
nanosleep now time: 2023-02-13 17:07:18
nanosleep now time: 2023-02-13 17:07:19
nanosleep now time: 2023-02-13 17:07:20
nanosleep now time: 2023-02-13 17:07:21
nanosleep now time: 2023-02-13 17:07:22
nanosleep now time: 2023-02-13 17:07:23
select now time: 2023-02-13 17:07:24
select now time: 2023-02-13 17:07:26
select now time: 2023-02-13 17:07:28
select now time: 2023-02-13 17:07:30
select now time: 2023-02-13 17:07:32
select now time: 2023-02-13 17:07:34
select now time: 2023-02-13 17:07:36
select now time: 2023-02-13 17:07:38
select now time: 2023-02-13 17:07:40
select now time: 2023-02-13 17:07:42
sleep now time: 2023-02-13 17:07:44
sleep now time: 2023-02-13 17:07:45
sleep now time: 2023-02-13 17:07:46
sleep now time: 2023-02-13 17:07:47
sleep now time: 2023-02-13 17:07:48
sleep now time: 2023-02-13 17:07:49
sleep now time: 2023-02-13 17:07:50
sleep now time: 2023-02-13 17:07:51
sleep now time: 2023-02-13 17:07:52
sleep now time: 2023-02-13 17:07:53
*/