#pragma once

#include <iostream>
#include <thread>
#include <ctime>
#include <cstdio>
#include <windows.h>
#include <list>
#include <mutex>

using namespace std;

void threadHandle1(int time)
{
	// 让子线程睡眠time秒
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread1!" << endl;

	// 获取线程id
	std::cout << "inside thread :: ID = " << std::this_thread::get_id() << std::endl;
}
void threadHandle2(int time)
{
	// 让子线程睡眠time秒
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread2!" << endl;
}

/*
* 当线程启动后，一定要在和线程相关联的std::thread对象销毁前，对线程运用join()或者detach()方法。
* 
* 体现一下join和detach的重要性。
* 
* 在一般情况下，如果主线程结束，就代表整个进程结束，如果这时有子线程还未结束就会出现运行错误。
* 当设置子线程为分离线程，主线程结束，子线程也自动结束。
*/
void test_join_detach()
{
	// 创建了一个线程对象,传入一个线程函数,新线程就开始运行了
	std::thread t1(threadHandle1, 2);
	std::cout << "t1 thread :: ID = " << t1.get_id() << std::endl;

	std::thread t2(threadHandle2, 3);
	//t1.join();
	t1.detach();
	//t2.join();
	t2.detach();
	cout << __FUNCTION__ << " done!" << endl;
	return;
}

std::mutex mtx;			// 全局的一把互斥锁
int ticketCount = 100;	// 车站有100张车票，由三个窗口一起卖票

/*
* 模拟卖票的线程函数 lock_guard unique_lock
*/
void sellTicket(int index)
{
	while (ticketCount > 0) { // ticketCount=1 锁+双重判断
		// 保证所有线程都能释放锁，防止死锁问题的发生 scoped_ptr
		lock_guard<std::mutex> lock(mtx);	// 把锁包装成了一个类，保证能出函数一定会释放锁
		if (ticketCount > 0) {
			// 临界区代码段 =》 原子操作 =》 线程间互斥操作了 =》 mutex
			cout << "窗口:" << index << "卖出第:" << ticketCount << "张票!" << endl;
			ticketCount--;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return;
}

/*
* 多线程编程：假设有车站的三个买票窗口来卖100张票。
*/
void multi_thread_tickets()
{
	list<std::thread> tlist;
	for (int i = 1; i <= 3; ++i) {
		tlist.push_back(std::thread(sellTicket, i));
	}

	for (std::thread& t : tlist) {
		t.join();
	}
	cout << "所有窗口卖票结束!" << endl;
	return;
}

// volatile保证了每次数据都是从内存拿，而不是有一定安全性风险的寄存器
volatile std::atomic_bool isReady = false;
volatile std::atomic_int mycount = 0;
void task()
{

	while (!isReady)
	{

		std::this_thread::yield(); // 线程出让当前的CPU时间片，等待下一次调度
	}

	for (int i = 0; i < 100; ++i)
	{

		mycount++;
	}
}

/*
* CAS原子操作：因为锁的操作是比较重，而且在临界区代码做的事情比较复杂，比较多。所以引入了CAS来保证上面的--操作的原子特性。同时这也是无锁操作。
*/
void study_CAS()
{
	list<std::thread> tlist;
	for (int i = 0; i < 10; ++i) {
		tlist.push_back(std::thread(task));
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));
	isReady = true;

	for (std::thread& t : tlist) {
		t.join();
	}
	cout << "mycount:" << mycount << endl;

	return;
}


void test_study_lock()
{
	//test_join_detach();
	//multi_thread_tickets();
	study_CAS();
	return;
}