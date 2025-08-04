/*******************************************************************************
* 文 件 名: pointer_array.cpp
* 文件描述: 指针数组和数组指针
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.04
* 修改日期：2025.08.04
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

int main()
{
    int *ptr_array[5];  // 指针数组
    int (*array_ptr)[5];// 数组指针
    std::cout << ptr_array << ' ' << array_ptr << std::endl;

    int a = 1, b = 2, c = 3, d = 4, e = 5;
    // 为每个指针元素赋值（指向int变量）
    ptr_array[0] = &a;
    ptr_array[1] = &b;
    ptr_array[2] = &c;
    ptr_array[3] = &d;
    ptr_array[4] = &e;

    // 访问：通过数组下标取指针，再解引用
    std::cout << *ptr_array[0] << std::endl;  // 输出 1

    int arr[6] = {10, 20, 30, 40, 50};  // 长度为5的int数组
    // error: cannot convert ‘int (*)[6]’ to ‘int (*)[5]’ in assignment
    array_ptr = &arr;  // 赋值：指向数组arr（注意取地址符&）
    // 访问：先解引用指针得到数组，再通过下标访问元素
    std::cout << (*array_ptr)[0] << std::endl;  // 输出 10
    std::cout << (*array_ptr)[2] << std::endl;  // 输出 30

    // 也可简化为 array_ptr[0][i]（编译器自动转换）
    std::cout << array_ptr[0][3] << std::endl;  // 输出 40
    return 0;
}