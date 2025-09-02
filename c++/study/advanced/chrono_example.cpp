/*******************************************************************************
* 文 件 名: chrono_example.cpp
* 文件描述: std::chrono 是 C++11 引入的一个库，用于处理时间和时钟
* 备    注: adj.计时的；慢性的；长期的
* 作    者: HanKin
* 创建日期: 2025.04.25
* 修改日期：2025.04.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <thread>

int main()
{
    // 时间戳
    std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
    std::cout << timestamp.time_since_epoch().count() << " 纳秒" << std::endl;
    
    // 1、获取当前时间点
    auto now = std::chrono::system_clock::now();    // 表示系统时间，通常与现实世界的时间相对应
    std::cout << "当前时间点: " << now.time_since_epoch().count() << " 纳秒" << std::endl;
    // 时间单位nanoseconds、microseconds、milliseconds、seconds、minutes、hours
    auto future_time = now + std::chrono::hours(1); // 当前时间加1小时
    std::cout << "未来时间点: " << future_time.time_since_epoch().count() << " 纳秒" << std::endl;

    // 2、格式化输出（std::chrono 本身不提供格式化输出的功能）
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "当前时间: " << std::put_time(std::localtime(&now_c), "%F %T") << std::endl;

    // 3、时间段
    auto start = std::chrono::high_resolution_clock::now();  // 提供高精度的计时，通常是系统时钟或单调时钟的别名
    // 模拟一些工作
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "耗时: " << elapsed.count() << " 毫秒" << std::endl;

    // 4、单调时间
    auto steady_now = std::chrono::steady_clock::now(); // 表示一个单调时钟，适合测量时间间隔，不会因系统时间的改变而改变
    std::cout << "当前单调时间点: " << steady_now.time_since_epoch().count() << " 纳秒" << std::endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake/advanced/build] #./a.out
当前时间点: 1396118676538226300 纳秒
未来时间点: 1396122276538226300 纳秒
当前时间: 2014-03-30 02:44:36
耗时: 100.106 毫秒
当前单调时间点: 10064180853944968 纳秒
[root@ubuntu0006:~/cmake/advanced/build] #date
2014年 03月 30日 星期日 02:44:48 CST
*/