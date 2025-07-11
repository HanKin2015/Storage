/*******************************************************************************
* 文 件 名: SFINAE_example.cpp
* 文件描述: 当模板参数替换导致无效的类型或表达式时，编译器不会报错，而是选择其他更匹配的模板（如果存在）
* 备    注: 一种规定或规则，不是语法
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 模板 1：T 是可调用类型
template<typename T>
auto invoke(T t) -> decltype(t()) {
    return t();
}

// 模板 2：T 不是可调用类型（SFINAE 排除）
template<typename T>
void invoke(...) {
    std::cout << "Not callable!" << std::endl;
}

int main()
{
    auto lambda = []() { return 42; };
    invoke(lambda);  // 调用模板 1，返回 42

    int x = 10;
    invoke(x);     // 调用模板 2，输出 "Not callable!"
	return 0;
}