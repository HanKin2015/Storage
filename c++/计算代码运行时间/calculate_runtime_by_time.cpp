/*******************************************************************************
* 文 件 名: calculate_runtime_by_time.cpp
* 文件描述: 适合粗略测量长时间运行的程序
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

int main()
{
    time_t start = time(nullptr);
    
    std::thread t(task);

    // 待计时的代码
    std::cout << "start main task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    t.join();

    time_t end = time(nullptr);
    std::cout << "Code took " << (end - start) << " seconds." << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp 
root@hankin:~/opencv# ./a.out 
start main task...
start task...
Code took 3001173 milliseconds.
*/