/*******************************************************************************
* 文 件 名: calculate_runtime_by_average.cpp
* 文件描述: 对于短时间代码，多次运行取平均值更准确
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

template<typename Func>
double benchmark(Func func, int iterations = 10) {
    std::vector<long long> times;
    times.reserve(iterations);

    for (int i = 0; i < iterations; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    }

    // 计算平均值（排除最大值和最小值以减少误差）
    std::sort(times.begin(), times.end());
    long long sum = 0;
    for (int i = 1; i < iterations - 1; ++i) {
        sum += times[i];
    }
    return static_cast<double>(sum) / (iterations - 2) / 1e9;  // 转换为秒
}

int main()
{
    time_t start = time(nullptr);

    double avg_time = benchmark([]{
        std::thread t(task);

        // 待计时的代码
        std::cout << "start main task..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        t.join();
    }, 20);

    std::cout << "Average time: " << avg_time * 1000 << " milliseconds." << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp 
root@hankin:~/opencv# ./a.out 
start main task...
start task...
Code took 3001173 milliseconds.
*/