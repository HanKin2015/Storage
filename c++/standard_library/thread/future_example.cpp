/*******************************************************************************
* 文 件 名: future_example.cpp
* 文件描述: 使用 std::future 可以帮助你编写并发代码，同时避免直接处理线程同步的复杂性
* 备    注: g++ future_example.cpp -std=c++11 -lpthread
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
    // 使用 std::async 启动一个异步任务
    std::future<int> result = std::async([]() {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
        return 42; // 返回结果
    });

    // 在这里可以做一些其他的工作...
    std::cout << "do else something" << std::endl;

    // 等待异步任务完成并获取结果
    std::cout << "Waiting for the result..." << std::endl;
    std::cout << "The result is " << result.get() << std::endl; // 阻塞直到结果准备好

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
do else something
Waiting for the result...
The result is 42
*/