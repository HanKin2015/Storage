/*******************************************************************************
* 文 件 名: structured_binding_example.cpp
* 文件描述: 结构化绑定
* 备    注: 标准库中的std::tuple基于可变参数模板实现
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <tuple>
#include <cstring>

int main()
{
	//std::tuple t = std::make_tuple(1, "hello", 3.14);
	std::tuple<int, std::string, int> t = std::make_tuple(1, "hello", 3.14);	// 1 hello 3
	auto [a, b, c] = t;
	std::cout << a << ' ' << b << ' ' << c << std::endl;	// 1 hello 3.14
	return 0;
}