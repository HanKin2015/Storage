/*******************************************************************************
* 文 件 名: calculate_runtime_by_chrono.cpp
* 文件描述: C++ 标准库中最推荐的方式，提供纳秒级精度，跨平台且类型安全
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

void task()
{
    std::cout << "start task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();  // 开始计时

    std::thread t(task);

    // 待计时的代码
    std::cout << "start main task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    t.join();

    auto end = std::chrono::high_resolution_clock::now();    // 结束计时
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();  // 转换为秒
    std::cout << "Code took " << duration << " milliseconds." << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp 
root@hankin:~/opencv# ./a.out 
start main task...
start task...
Code took 3001 milliseconds.
*/