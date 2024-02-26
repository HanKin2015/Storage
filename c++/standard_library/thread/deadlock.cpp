/*******************************************************************************
* 文 件 名: deadlock.cpp
* 文件描述: 操作是非原子的，导致两个线程如果同时对一个文件指针做fclose(double free or corruption)
* 备    注: g++ deadlock.cpp -lpthread -std=c++11
* 作    者: HanKin
* 创建日期: 2024.02.01
* 修改日期：2024.02.01
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>

void closeFile(std::FILE *file)
{
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟一些耗时操作
    std::fclose(file);
}

int main()
{
    std::FILE *file = std::fopen("test.txt", "w");
    if (file == nullptr) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::thread t1(closeFile, file);
    std::thread t2(closeFile, file);

    t1.join();
    t2.join();

    return 0;
}