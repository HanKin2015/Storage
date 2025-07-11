/*******************************************************************************
* 文 件 名: atomic_example.cpp
* 文件描述: C++11 引入的标准库组件，用于实现原子操作。原子操作是不可中断的操作，在多线程环境中无需锁即可保证数据一致性，常用于实现无锁（lock-free）算法
* 备    注: 底层实现：依赖硬件原子指令（如 CPU 的 CAS 操作），性能通常优于互斥锁
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <atomic>

int main()
{
	// 1. 初始化与赋值
	std::atomic<int> a(0);     // 直接初始化
	std::cout << a << std::endl;
	a = 42;                   // 原子赋值
	a.store(100, std::memory_order_seq_cst);  // 显式存储（带内存序）
	std::atomic<int> b{1};
	std::cout << b << std::endl;
	
	// 2. 读取值
	int value = a.load();     // 原子加载
	int value2 = a;           // 隐式加载（等价于 load()）
	std::cout << value << ' ' << value2 << std::endl;
	
	// 3. 原子算术操作
	int ret = a.fetch_add(5);           // 原子加法（返回旧值）
	std::cout << a << ' ' << ret << std::endl;
	a += 5;                   // 等价于 fetch_add()，但返回新值
	std::cout << a << std::endl;
	a.fetch_sub(3);           // 原子减法
	std::cout << a << std::endl;
	a--;                      // 原子自减
	std::cout << a << std::endl;

	// 4. 比较并交换（CAS）
	int expected = 10;
	bool success = a.compare_exchange_weak(expected, 20);
	// 如果 a 的当前值等于 expected，则将 a 设置为 20，并返回 true
	// 否则将 expected 更新为 a 的当前值，并返回 false
	std::cout << a << ' ' << expected << ' ' << success << std::endl;
	
	return 0;
}