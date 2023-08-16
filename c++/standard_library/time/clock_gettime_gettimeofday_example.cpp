/**
* 文 件 名: clock_gettime_gettimeofday_example.cpp
* 文件描述: clock_gettime和gettimeofday函数学习
* 作    者: HanKin
* 创建日期: 2021.11.12
* 修改日期：2023.08.15
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <time.h>

#define HAVE_CLOCK_GETTIME

uint64_t get_monolithic_time()
{
#ifdef HAVE_CLOCK_GETTIME
    struct timespec time_space;
    clock_gettime(CLOCK_MONOTONIC, &time_space);
    return uint64_t(time_space.tv_sec) * 1000 * 1000 * 1000 + uint64_t(time_space.tv_nsec);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return uint64_t(tv.tv_sec) * 1000 * 1000 * 1000 + uint64_t(tv.tv_usec) * 1000;
#endif
}

/*
 1692081169332827 = 1692081169 332 827
[root@ubuntu0006:~/cmake] #date +%s
1692081187
[root@ubuntu0006:~/cmake] #date
2023年 08月 15日 星期二 14:33:10 CST
*/
static char * get_abstime_us_str(void)
{
    static char abstime_str[128] = {0};
    struct timeval tv;
    gettimeofday(&tv, NULL);
    // 秒 毫秒 微妙
    snprintf(abstime_str, sizeof(abstime_str) - 1, "%17llu = %10llu %3llu %3llu",
        (long long unsigned int)tv.tv_sec * 1000000LL + (tv.tv_usec),
        (long long unsigned int)tv.tv_sec,
        (long long unsigned int)tv.tv_usec/1000,
        (long long unsigned int)tv.tv_usec%1000);
    return abstime_str;
}

int main()
{
    uint64_t mm_time = get_monolithic_time();
    printf("mm_time: %llu\n", mm_time);
    return 0;
}