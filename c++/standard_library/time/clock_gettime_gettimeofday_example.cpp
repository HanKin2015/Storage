/**
* 文 件 名: clock_gettime_gettimeofday_example.cpp
* 文件描述: clock_gettime和gettimeofday函数学习
* 作    者: HanKin
* 创建日期: 2021.11.12
* 修改日期：2021.11.12
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

int main()
{
    uint64_t mm_time = get_monolithic_time();
    printf("mm_time: %llu\n", mm_time);
    return 0;
}