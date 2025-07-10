/*******************************************************************************
* 文 件 名: function_template_example.cpp
* 文件描述: 函数模板
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 通用函数模板
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
	std::cout << "通用版本" << std::endl;
}

// 全特化：为指针类型提供特殊实现
template <>
void swap<int*>(int*& a, int*& b) {
    int* temp = a;
    a = b;
    b = temp;
	std::cout << "int* 特化版本" << std::endl;
}

int main()
{
	int a = 10, b = 100;
	swap<int>(a, b);
	std::cout << a << ' ' << b << std::endl;
	
	int *p = &a, *q = &b;
	swap<int *>(p, q);
	std::cout << a << ' ' << b << std::endl;
	std::cout << *p << ' ' << *q << std::endl;
	
	return 0;
}
/*
通用版本
100 10
int* 特化版本
100 10
10 100
*/