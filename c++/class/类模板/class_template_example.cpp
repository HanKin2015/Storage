/*******************************************************************************
* 文 件 名: template_example.cpp
* 文件描述: 类通用模板、默认模板参数、全特化
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 通用模板
template <typename T>
class Container {
public:
    void print() { std::cout << "通用版本" << std::endl; }
};

// 全特化：为 int 类型提供特殊实现
template <>
class Container<int> {
public:
    void print() { std::cout << "int 特化版本" << std::endl; }
};

// 默认模板参数
template <typename T = int, size_t N = 10>
class Buffer { /* ... */ };

int main()
{
	Container<double> c1;  // 使用通用模板
	Container<int> c2;     // 使用 int 特化版本

	c1.print();  // 输出：通用版本
	c2.print();  // 输出：int 特化版本
	
	Buffer<> buf;  // 等价于 Buffer<int, 10>
	return 0;
}