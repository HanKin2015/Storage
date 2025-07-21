/*******************************************************************************
* 文 件 名: future_example2.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.01.12
* 修改日期：2024.01.12
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <future>
#include <thread>

int main()
{
    // std::launch::async：肯定会创建新线程，异步执行任务。
    // std::launch::deferred：采用惰性求值方式，等到调用 future.get() 或者 future.wait() 时才会同步执行任务。
    // 要是不指定策略，就由系统自行决定，可能是 async 也可能是 deferred。
    // 需通过 std::async 或者 std::promise 来初始化，直接用 lambda 赋值肯定会出错
    std::future<int> result = std::async(std::launch::deferred, []() {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
        return 42; // 返回结果
    });

    // 在这里可以做一些其他的工作...
    std::cout << "Main progress calculate result..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // 等待异步任务完成并获取结果
    std::cout << "Waiting for the result..." << std::endl;

    try {
        // deferred 策略：适合需要延迟执行且不希望创建新线程的场景，但会使超时机制失效。
        if (result.wait_for(std::chrono::seconds(3)) == std::future_status::ready) {
            std::cout << "Result: " << result.get() << std::endl;
        } else {
            std::cout << "Timeout!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
do else something
Waiting for the result...
The result is 42
*/