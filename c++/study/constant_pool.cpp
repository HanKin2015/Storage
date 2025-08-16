/*******************************************************************************
* 文 件 名: constant_pool.cpp
* 文件描述: 常量池
* 备    注: 相同常量只存储一份，避免重复占用空间
* 作    者: HanKin
* 创建日期: 2025.08.15
* 修改日期：2025.08.15
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>

int main()
{
    const char* s1 = "hello";
    const char* s2 = "hello";
    // s1和s2指向同一份常量池数据，s1 == s2 → true
    // 要使用cout输出指针s1和s2的地址（而不是它们指向的字符串内容），需要将指针显式转换为void*类型。
    // 这是因为cout对char*类型有特殊处理，会自动输出字符串内容而非地址。
    std::cout << static_cast<void*>(const_cast<char*>(s1)) << ' ' 
         << static_cast<void*>(const_cast<char*>(s2)) << std::endl;
    printf("%p %p\n", s1, s2);      // 保证两者相同

    std::string s3 = "hello";
    std::string s4 = "hello";
    // 多数编译器中，s3和s4的底层数据可能指向常量池（优化），但也可能复制数据（取决于实现）
    std::cout << &s3 << ' ' << &s4 << std::endl;
    printf("%p %p\n", &s3, &s4);    // 不保证两者相同
    return 0;
}