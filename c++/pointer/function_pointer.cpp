/*******************************************************************************
* 文 件 名: function_pointer.cpp
* 文件描述: 函数指针
* 备    注: 当函数名（如 add）出现在需要指针的语境中时，编译器会自动将其转换为指向该函数的指针（即函数的入口地址）。
因此，add 在表达式中等价于 &add（取函数地址），二者含义相同。
* 作    者: HanKin
* 创建日期: 2025.08.04
* 修改日期：2025.08.04
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 声明一个函数指针类型
typedef void (*FuncPtrType)(int);  // FuncPtr 是一个指向返回类型为 void，参数为 int 的函数指针类型
 
// 定义一个函数
void myFunction(int x) {
    // 函数体
}

// 定义一个函数
int add(int a, int b) {
    return a + b;
}
 
// 另一个函数，返回一个函数指针
int (*getAddFunctionPointer())(int, int) {
    return &add;
}

int main() {
    // 声明一个函数指针变量并初始化
    FuncPtrType ptr = &myFunction;
    // 通过函数指针调用函数
    ptr(10);  // 相当于调用 myFunction(10);

    // 声明一个函数指针
    int (*funcPtr)(int, int);  // funcPtr 是一个函数，返回类型为 int*，参数为两个 int
    // 获取 add 函数的函数指针
    funcPtr = getAddFunctionPointer();
    // 通过函数指针调用函数
    int result = funcPtr(3, 4);  // 相当于调用 add(3, 4)，result 等于 7
    std::cout << result << std::endl;
    
    funcPtr = add;              // 隐式转换：函数名自动转为指针
    result = funcPtr(3, 4);
    std::cout << result << std::endl;
    
    funcPtr = &add;
    result = funcPtr(3, 4);     // 显式取地址：效果相同
    std::cout << result << std::endl;
    return 0;
}