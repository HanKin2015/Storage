/*******************************************************************************
* 文 件 名: struct_template_example.cpp
* 文件描述: 结构体模板，模板并不一定需要typename关键字
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 编译期计算斐波那契数列
template <int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template <>
struct Fibonacci<0> { static constexpr int value = 0; };

template <>
struct Fibonacci<1> { static constexpr int value = 1; };

int main()
{
	// 使用
	constexpr int fib_10 = Fibonacci<10>::value;  // 编译期计算完成
	
	std::cout << fib_10 << std::endl;
	
	return 0;
}