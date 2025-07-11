/*******************************************************************************
* 文 件 名: greater_example.cpp
* 文件描述: mutex、lock_guard、adopt_lock
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <mutex>
#include <thread>
#include <iostream>

std::mutex mtx;
int shared_data = 0;

// mutex不推荐
void unsafe_increment()
{
    mtx.lock();
    try {
        // 临界区：保护共享资源
        shared_data++;
        std::cout << shared_data << std::endl;
    } catch (...) {
        mtx.unlock();  // 必须手动释放锁，否则死锁
		std::cerr << "has exception" << std::endl;
        return;
    }
    mtx.unlock();  // 容易忘记！
}

// 推荐
void safe_increment()
{
    std::lock_guard<std::mutex> lock(mtx);
    try {
        // 临界区：保护共享资源
        shared_data++;
        std::cout << shared_data << std::endl;
    } catch (...) {
		std::cerr << "has exception" << std::endl;
        return;
    }
}

int main()
{
	unsafe_increment();
	safe_increment();
	
	mtx.lock();  // 手动加锁
	{
		// 当 mutex 已经被手动锁定时，可以使用 std::adopt_lock 告诉 lock_guard 无需再次加锁，仅负责解锁
		std::lock_guard<std::mutex> lock(mtx, std::adopt_lock);
		// 使用已锁定的mutex
	}  // 自动解锁
	return 0;
}