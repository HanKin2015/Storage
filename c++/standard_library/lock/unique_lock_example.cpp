/*******************************************************************************
* 文 件 名: unique_lock_example.cpp
* 文件描述: 
* 备    注: 灵活（可延迟锁定、手动解锁、转移所有权）
* 作    者: HanKin
* 创建日期: 2025.07.13
* 修改日期：2025.07.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

std::condition_variable cv;
std::mutex mtx;
bool ready = false;

void worker()
{
    std::unique_lock<std::mutex> lock(mtx);
	// 支持手动加解锁，但是lock_guard不支持	
	//lock.lock();	// 重复锁定同一互斥锁会导致死锁（第二次 lock() 永久阻塞）
	lock.unlock();
	lock.lock();
	std::cout << "wait ready convert to true" << std::endl;
    cv.wait(lock, []{ return ready; });  // 必须使用unique_lock
    // 执行任务
	std::cout << "start exec task" << std::endl;
}

void master()
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
		std::cout << "Master set ready to true" << std::endl;
    }  // 离开作用域时自动解锁
    cv.notify_one();  // 通知等待线程
	std::cout << "notify wait thread" << std::endl;
}

int main()
{
	std::thread t1(worker);
	// 将时间改为1秒在线编译器执行失败
    std::this_thread::sleep_for(std::chrono::milliseconds(100));   // 确保worker先等待
    master();
    t1.join();
	return 0;
}
/*
wait ready convert to true
Master set ready to true
notify wait thread
start exec task
*/