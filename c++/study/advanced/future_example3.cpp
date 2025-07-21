/*******************************************************************************
* 文 件 名: future_example3.cpp
* 文件描述: wait_for()：等待相对时间（如等待 3 秒）。
            wait_until()：等待到绝对时间点（如等待到 2025 年 7 月 22 日 12:00:00）。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.21
* 修改日期：2025.07.21
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int async_task()
{
    std::this_thread::sleep_for(std::chrono::seconds(3)); // 模拟3秒耗时操作
    return 42;
}

int main()
{
    // 启动异步任务
    std::future<int> future = std::async(std::launch::async, async_task);

    // 计算绝对超时时间点（当前时间 + 2秒）
    auto timeout_time = std::chrono::steady_clock::now() + std::chrono::seconds(2);

    // 等待到指定时间点
    std::cout << "Waiting until timeout_time..." << std::endl;
    auto status = future.wait_until(timeout_time);

    // 根据返回状态处理结果
    if (status == std::future_status::ready) {
        std::cout << "Result is ready: " << future.get() << std::endl;
    } else if (status == std::future_status::timeout) {
        std::cout << "Timeout! Result is not ready yet." << std::endl;
        // 可以选择继续等待或执行其他操作
        std::cout << "Waiting for another 2 seconds..." << std::endl;
        status = future.wait_for(std::chrono::seconds(2));
        if (status == std::future_status::ready) {
            std::cout << "Result is now ready: " << future.get() << std::endl;
        } else {
            std::cout << "Still not ready! Giving up." << std::endl;
        }
    } else if (status == std::future_status::deferred) {
        std::cout << "Task is deferred. Getting result now..." << std::endl;
        std::cout << "Result: " << future.get() << std::endl;
    }

    return 0;
}