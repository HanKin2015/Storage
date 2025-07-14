/*******************************************************************************
* 文 件 名: 右值引用.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <vector>
#include <iostream>

int main()
{
	std::vector<int> vec;
    vec.emplace_back(11);
	vec.push_back(22);
	
	for (const auto& elem : vec) {
		std::cout << elem << std::endl;
	}
	
	// error: cannot bind rvalue reference of type 'const int&&' to lvalue of type 'int'
	//for (const auto&& elem : vec) {
	//	std::cout << elem << std::endl;
	//}
	
	// 创建临时vector（右值）
    auto getVector = []() { return std::vector<int>{1, 2, 3}; };
    
    // 使用auto&&捕获右值引用
	// 加了const后error: cannot bind rvalue reference of type 'const int&&' to lvalue of type 'int'
    for (const auto&& elem : getVector()) {
        std::cout << elem << std::endl;
    }
/*
for (auto&& elem)	int&&		✅ 可以 右值引用可绑定到临时对象中的元素（尽管元素本身是左值，但此处允许特殊转换）
for (const auto& e)	const int&	✅ 可以	常量左值引用可绑定到任何类型的值（包括右值中的左值元素）
for (const auto&&)	const int&&	❌ 错误	常量右值引用只能绑定到常量右值，无法绑定到容器中的非常量左值元素
*/
	return 0;
}