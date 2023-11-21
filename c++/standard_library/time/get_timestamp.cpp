/*******************************************************************************
* 文 件 名: get_timestamp.cpp
* 文件描述: 获取时间戳
* 作    者: HanKin
* 创建日期: 2023.11.21
* 修改日期：2023.11.21
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <time.h>

void test_function() {
    // 模拟一个耗时的操作
    for (long long i = 0; i < 3000000000; i++);
}

int main()
{
    time_t timestamp;
    time(&timestamp);   // 方式一
    printf("当前时间戳为：%ld\n", timestamp);
    
    time_t timestamp2;  // 方式二
    timestamp2 = time(NULL);
    printf("当前时间戳为：%ld\n", timestamp2);
    
    char *timestr = ctime(&timestamp);
    printf("当前时间为：%s\n", timestr);
    
    struct tm *timeinfo;
    timeinfo = localtime(&timestamp);
    char buffer[80] = { 0 };
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("格式化后的时间为：%s\n", buffer);
    
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // 调用测试函数
    test_function();

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("程序执行了%f秒\n", cpu_time_used);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
当前时间戳为：1700536902
当前时间戳为：1700536902
当前时间为：Tue Nov 21 11:21:42 2023

格式化后的时间为：2023-11-21 11:21:42
程序执行了4.649594秒
*/