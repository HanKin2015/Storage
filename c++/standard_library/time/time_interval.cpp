/**
* 文 件 名: time_interval.cpp
* 文件描述: linux时间间隔计算
* 作    者: HanKin
* 创建日期: 2023.02.14
* 修改日期：2023.02.14
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <sys/select.h>

static void method1()
{
    time_t begin = time(NULL);
    sleep(2);
    time_t end;
    time(&end); /*当前time_t类型UTC时间*/
    printf("time(): begin = %ld, end = %ld\n", begin, end);
    printf("diff = %ld s\n\n", end - begin);
    return;
}

// 使用sleep函数就是很有问题，结果是0.000024s
static void method2()
{
    clock_t begin = clock();
    //sleep(2);
    sleep(10);
    clock_t end = clock();
    printf("clock(): begin = %ld, end = %ld\n", begin, end);
    printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);
    printf("diff = %f s\n\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

// 以毫秒为单位，所以是2000ms
static void method3()
{
    struct timespec ts;
    
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t begin = (ts.tv_sec * (1000ULL) + ts.tv_nsec / (1000000ULL));
    sleep(2);
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t end = (ts.tv_sec * (1000ULL) + ts.tv_nsec / (1000000ULL));
    printf("clock_gettime(): begin = %lu, end = %lu\n", begin, end);
    printf("diff = %lu ms\n\n", end - begin);
    return;
}

static void clock_example1()
{
    int index = 3;
    while (index--) {
        printf("count: %f\n", (double)clock() / CLOCKS_PER_SEC);
        sleep(1);
    }
    printf("\n");
    return;
}

static void clock_example2()
{
    clock_t begin = clock();
    for (int i = 0; i < 1e5; i++) {
        for (int j = 0; j < 1e5; j++) {
        }
    }
    clock_t end = clock();
    printf("clock(): begin = %ld, end = %ld\n", begin, end);
    printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);
    printf("diff = %f s\n\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

// 和clock_example2进行对比，大约花费14-15s
static void clock_example3()
{
    time_t begin = time(NULL);
    for (int i = 0; i < 1e5; i++) {
        for (int j = 0; j < 1e5; j++) {
        }
    }
    time_t end;
    time(&end); /*当前time_t类型UTC时间*/
    printf("time(): begin = %ld, end = %ld\n", begin, end);
    printf("diff = %ld s\n\n", end - begin);
    return;
}

// 尝试了三种睡眠函数都不行
static void clock_example4()
{
    clock_t begin = clock();
    //usleep(2000000);
    //sleep(2);
    
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 2*1000000;
    select(0, NULL, NULL, NULL, &tv);
        
    clock_t end = clock();
    printf("clock(): begin = %ld, end = %ld\n", begin, end);
    printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);
    printf("diff = %f s\n\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

int main(int argc, char *argv[])
{
    method1();
    method2();
    method3();
    clock_example1();
    clock_example2();
    clock_example3();
    clock_example4();
    return 0;
}
/*
time(): begin = 1676343881, end = 1676343883
diff = 2 s

clock(): begin = 973, end = 996
CLOCKS_PER_SEC = 1000000
diff = 0.000023 s

clock_gettime(): begin = 11614324593, end = 11614326593
diff = 2000 ms

count: 0.001108
count: 0.001134
count: 0.001184

clock(): begin = 1251, end = 14736018
CLOCKS_PER_SEC = 1000000
diff = 14.734767 s

time(): begin = 1676343913, end = 1676343927
diff = 14 s

clock(): begin = 29387314, end = 29387340
CLOCKS_PER_SEC = 1000000
diff = 0.000026 s
*/