/*******************************************************************************
* 文 件 名: thread_example3.cpp
* 文件描述: 线程池
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.13
* 修改日期：2025.07.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>
#include <vector>

int main()
{
	std::thread t([] {
		std::cout << 123 << std::endl;
	});
	t.join();

	std::vector<std::thread> v;
	v.emplace_back([] {
		std::cout << 321 << std::endl;
	});
	for (auto& elem : v) {
		elem.join();
	}
	return 0;
}
