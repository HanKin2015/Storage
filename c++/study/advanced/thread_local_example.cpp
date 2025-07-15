/*******************************************************************************
* 文 件 名: thread_local_example.cpp
* 文件描述: std::thread_local 是一个存储类说明符，用于声明线程局部存储（Thread-Local Storage, TLS）变量。每个线程都拥有该变量的独立副本，线程间互不干扰。这为多线程编程提供了一种高效且安全的变量管理方式。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>

void worker()
{
	// 测试发现是否存在没有关系
    thread_local int counter = 0;  // 每个线程独立计数
    counter++;
    std::cout << "Thread " << std::this_thread::get_id() 
              << ": counter = " << counter << std::endl;
}

int main()
{
    std::thread t1(worker);
    std::thread t2(worker);
    t1.join();
    t2.join();
    return 0;
}

// 可能输出：
// Thread 12345: counter = 1
// Thread 67890: counter = 1