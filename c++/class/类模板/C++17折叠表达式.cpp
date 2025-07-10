/*******************************************************************************
* 文 件 名: C++17折叠表达式.cpp
* 文件描述: 最常见的方式，通过递归逐个处理参数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args) << '\n'; // C++17折叠表达式
}

template<typename... Args>
void print(Args... args) {
    int dummy[] = { (std::cout << args << ' ', 0)... };
    (void)dummy; // 避免未使用变量警告
}

template<typename... Args>
auto sum_all(Args... args) {
    return (args + ...); // 一元右折叠
}

int main()
{
	print_all(1, 2, 3, 4, 5);	// 12345
	
	print(1, 2, 3, 4, 5);	// 1 2 3 4 5 
	
	int sum = sum_all(1, 2, 3, 4, 5);
	std::cout << sum << std::endl;	// 15
	return 0;
}