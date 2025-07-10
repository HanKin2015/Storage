/*******************************************************************************
* 文 件 名: 模板元编程.cpp
* 文件描述: 模板元编程（TMP）
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cassert>

template <typename T>
struct Traits {
    static constexpr bool is_pointer = false;
};

// 指针类型的全特化
template <typename T>
struct Traits<T*> {
    static constexpr bool is_pointer = true;
};

int main()
{
	// 使用
	static_assert(Traits<int*>::is_pointer, "Must be a pointer!");
	static_assert(!Traits<int>::is_pointer, "Must be not a pointer!");
	return 0;
}