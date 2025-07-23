/*******************************************************************************
* 文 件 名: calculate_runtime_by_timeval.cpp
* 文件描述: 这是 Unix/Linux 系统专用方法，提供微秒级精度
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.22
* 修改日期：2025.07.22
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <sys/time.h>

void task()
{
    std::cout << "start task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return;
}

long long get_time() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000000LL + tv.tv_usec;  // 转换为微秒
}

int main()
{
    long long start = get_time();
    
    std::thread t(task);

    // 待计时的代码
    std::cout << "start main task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    t.join();

    long long end = get_time();
    std::cout << "Code took " << (end - start) << " microseconds." << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp 
root@hankin:~/opencv# ./a.out 
start main task...
start task...
Code took 3001173 milliseconds.
*/