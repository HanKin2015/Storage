/*******************************************************************************
* 文 件 名: decltype_example.cpp
* 文件描述: decltype 是 C++11 引入的一个关键字，用于在编译时推导表达式的类型，而无需实际执行表达式
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
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

decltype(auto) f() {
    int x = 42;
    return (x);  // 返回 int&（保留表达式类型）
}

// SFINAE 技术
template<typename T>
auto has_size(const T& obj) -> decltype(obj.size(), std::true_type{});

int main()
{
    int x = 42;
	decltype((x)) y = x;  // 双层括号使表达式成为左值，y 的类型为 int&
	int& z = x;
	std::cout << typeid(x).name() << std::endl;
	std::cout << typeid(y).name() << std::endl;
	std::cout << x << y << z << std::endl;

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
1
2
1
0x7ffe0d67cf70
0x7ffe0d67cf6c
2
*/