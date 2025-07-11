/*******************************************************************************
* 文 件 名: volatile_example.cpp
* 文件描述: 在 C++ 中，cv 限定符（cv-qualifier）是指 const 和 volatile 关键字，用于修饰类型以表达不同的语义约束
* 备    注: 告诉编译器 “这个变量可能会被意外修改”（如硬件、多线程环境）。
*			禁用编译器优化，确保每次访问都直接从内存读取或写入。
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

int main()
{
	// const volatile：表示对象不可被程序修改，但可能被外部因素（如硬件）改变。
	const volatile int* clock_reg = (const volatile int*)0xFFFFFFF0;
	// 程序不能修改 *clock_reg，但硬件可能更新它

	const int* ptr1;    // 指向常量的指针（对象不可变）
	
	// C++ 规则：任何类型的 const 变量（包括指针）必须在声明时初始化，否则会导致编译错误
	int xx = 1234;
	int* const ptr2 = &xx;    // 常量指针（指针本身不可变）
	const int* const ptr3 = &xx;  // 指向常量的常量指针
	
	volatile int x = 100;
	x = 1000;
	std::cout << x << std::endl;
	return 0;
}