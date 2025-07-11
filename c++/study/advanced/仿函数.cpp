/*******************************************************************************
* 文 件 名: 仿函数.cpp
* 文件描述: 仿函数（Functor）也被称为函数对象（Function Object），是一种能够像函数一样被调用的对象。
* 备    注: 本质是一个类或结构体，通过重载operator()（函数调用运算符）来实现函数调用的语法
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <algorithm>

struct Adder {
    // 重载函数调用运算符
    int operator()(int a, int b) const {
        return a + b;
    }
};

#include <set>
struct ReverseOrder {
    bool operator()(int a, int b) const {
        return a > b; // 降序排列
    }
};

bool comp(int a, int b)
{
	return a > b;
}

int main()
{
	// 使用仿函数
	Adder adder;
	int result = adder(3, 4); // 等价于 adder.operator()(3, 4)，结果为7
	int ret = adder.operator()(4, 5);
	std::cout << result << ' ' << ret << std::endl;
	
	// 使用仿函数定义降序set
	std::set<int, ReverseOrder> s = {3, 1, 4, 1, 5};
	// s中的元素顺序为：5, 4, 3, 1
	for_each(s.cbegin(), s.cend(), [](int elem) {
        std::cout << elem << " ";
    });
	std::cout << std::endl;
	
	// lambda表达式
	std::set<int, bool(*)(int, int)> ss(comp);
    ss.insert({3, 1, 4, 1, 5});
	for_each(ss.cbegin(), ss.cend(), [](int elem) {
        std::cout << elem << " ";
    });
	std::cout << std::endl;
	
	std::plus<int> add;
	result = add(5, 3); // 等价于5 + 3，结果为8
	std::cout << result << std::endl;
	return 0;
}