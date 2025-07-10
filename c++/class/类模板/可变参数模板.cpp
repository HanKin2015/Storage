/*******************************************************************************
* 文 件 名: 可变参数模板.cpp
* 文件描述: 可变参数模板是 C++11 引入的一项强大特性，允许模板接受任意数量和类型的参数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 函数模板示例
// 递归终止函数
template<typename T>
T sum(T value) {
    return value;
}

// 可变参数模板函数
template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...); // 递归展开参数包
}


// 类模板示例
template<typename... Values>
struct Tuple;

// 递归特化
template<typename Head, typename... Tail>
struct Tuple<Head, Tail...> {
    Head head;
    Tuple<Tail...> tail;
    
    Tuple(Head h, Tail... t) : head(h), tail(t...) {}
};

// 递归终止特化：空 Tuple
template<>
struct Tuple<> {};

int main()
{
	// 使用示例
	int result = sum(1, 2, 3, 4); // 结果：10
	std::cout << result << std::endl;
	
	Tuple<int, double, char> t(1, 3.14, 'a');
	return 0;
}