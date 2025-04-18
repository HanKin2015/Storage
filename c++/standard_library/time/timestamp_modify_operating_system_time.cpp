/*******************************************************************************
* 文 件 名: timestamp_modify_operating_system_time.cpp
* 文件描述: 修改系统时间是否影响时间戳的获取
* 备    注: g++ timestamp_modify_operating_system_time.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2025.04.16
* 修改日期：2025.04.16
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <ctime>
#include <cstdio>
#include <chrono>

long long updateTimestamp1()
{
    auto now = std::chrono::system_clock::now();
    auto timestamp_seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    return timestamp_seconds.time_since_epoch().count();
}

long long updateTimestamp2()
{
    auto now = std::chrono::steady_clock::now();
    auto timestamp_seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    return timestamp_seconds.time_since_epoch().count();
}

long long updateTimestamp3()
{
    struct timespec ts;
    // 获取系统实时时钟
    clock_gettime(CLOCK_REALTIME, &ts);

    // 将时间转换为秒和纳秒
    std::cout << "Current time: " << ts.tv_sec << " seconds and "
              << ts.tv_nsec << " nanoseconds since the epoch." << std::endl;
    return 0;
}

long long updateTimestamp()
{
    time_t timestamp = time(NULL);
    return timestamp;
}

int main()
{
    long long current_time = updateTimestamp();
    printf("%lld\n", current_time);
    return 0;
}