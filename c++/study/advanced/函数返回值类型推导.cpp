/*******************************************************************************
* 文 件 名: 函数返回值类型推导.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.09
* 修改日期：2025.07.09
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// C++11 后置返回类型语法
template<typename T, typename U>
auto add1(T t, U u) -> decltype(t + u) {
    return t + u;
}

// C++14 简化语法
template<typename T, typename U>
auto add2(T t, U u) {
    return t + u;  // 返回值类型自动推导（本质还是 decltype）
}

int main()
{
	int a = 10;
	double b = 2.5;
	std::cout << add1(a, b) << std::endl;	// 12.5
	std::cout << add2(a, b) << std::endl;	// 12.5
	return 0;
}