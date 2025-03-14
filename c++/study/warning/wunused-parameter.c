/*******************************************************************************
* 文 件 名: wunused-parameter.c
* 文件描述: 使用下划线 _ 作为未使用参数的名称是一种常见的约定，但并不是 C++ 语言的强制要求。这种约定主要是为了提高代码的可读性，表明该参数是故意未使用的。
* 备    注: gcc wunused_parameter.c -Wall -Wextra -Werror（使用下划线 _ 并不会自动消除wunused_parameter警告）
* 作    者: HanKin
* 创建日期: 2025.03.11
* 修改日期：2025.03.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

// error: unused parameter ‘_’ [-Werror=unused-parameter]
void test1(int _)
{
    printf("hello\n");
    return;
}

// 注意[[maybe_unused]]需要写在最前面，是C++17特性，因此需要 GCC 7 或更高版本
// 使用gcc 14.2.0版本编译无此警告
void test2([[maybe_unused]] int _)
{
    printf("hello\n");
    return;
}

void test3(int _)
{
    (void)_;    // 显示地使用参数，使用 (void) 来避免未使用参数的警告
    printf("hello\n");
    return;
}

// 没有使用的函数
[[maybe_unused]] void test4(int _)
{
    (void)_;
    printf("hello\n");
    return;
}

int main()
{
    return 0;
}
