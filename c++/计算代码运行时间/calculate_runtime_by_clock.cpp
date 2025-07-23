/*******************************************************************************
* 文 件 名: calculate_runtime_by_clock.cpp
* 文件描述: 无法统计线程睡眠时间，不推荐（clock() 测量的是CPU 时间（包括所有线程），而非实际经过的挂钟时间（wall clock time））
* 备    注: C语言传统方法，返回 CPU 时钟周期数，精度较低（通常为毫秒级）
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

void task()
{
    std::cout << "start task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return;
}

int main()
{
    clock_t start = clock();  // 开始计时

    std::thread t(task);

    // 待计时的代码
    std::cout << "start main task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    t.join();

    clock_t end = clock();    // 结束计时
    double time_taken = double(end - start) / CLOCKS_PER_SEC;  // 转换为秒
    std::cout << "Code took " << time_taken * 1000 << " milliseconds." << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp 
root@hankin:~/opencv# ./a.out 
start main task...
start task...
Code took 0.765 milliseconds.
*/