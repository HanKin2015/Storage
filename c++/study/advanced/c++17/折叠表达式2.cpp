/*******************************************************************************
* 文 件 名: 折叠表达式2.cpp
* 文件描述: 折叠方向的重要性
* 备    注: 在大多数情况下，如加法运算，左右折叠的结果是相同的。但在某些情况下，折叠方向会影响结果
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstring>

template<typename... Args>
auto subtract_right(Args... args) {
    return (args - ...); // 右折叠：a1 - (a2 - (... - an))
}

template<typename... Args>
auto subtract_left(Args... args) {
    return (... - args); // 左折叠：(((a1 - a2) - ...) - an)
}

// 右折叠：从第一个参数开始打印
template<typename... Args>
void print_right(Args... args) {
    ((std::cout << args << " "), ...);
}

// 右折叠：从第一个参数开始打印
template<typename... Args>
void print_left(Args... args) {
    (... , (std::cout << args << " "));
}

int main()
{
	// 调用示例
	std::cout << subtract_right(10, 3, 2) << std::endl; // 等价于 10 - (3 - 2) = 9
	std::cout << subtract_left(10, 3, 2) << std::endl;  // 等价于 ((10 - 3) - 2) = 5
	
	// 调用示例
	print_right(1, 2, 3); // 输出：1 2 3
	print_left(1, 2, 3);  // 输出：1 2 3
	return 0;
}