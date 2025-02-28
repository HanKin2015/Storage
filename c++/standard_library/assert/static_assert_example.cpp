/*******************************************************************************
* 文 件 名: static_assert_example.cpp
* 文件描述: static_assert函数是c++11的特性，用于在编译时进行断言的工具
* 备    注: 第二个参数应该是一个字符串，而不是格式化字符串。C++ 的 static_assert 只接受一个字符串作为错误消息，不能像 printf 那样使用格式化参数
* 作    者: HanKin
* 创建日期: 2025.02.20
* 修改日期：2025.02.20
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cassert>
#include <cstdio>
using namespace std;

enum RC_TYPE
{
    RC_TYPE_WINSERVERSBC = 2,
    RC_TYPE_SPICEC_SBC = 34,
    RC_TYPE_UNKNOW = 39,
};

#define HJ 23
#define JH 32
#define RC_TYPE_MAX 31

// 使用 static_assert 进行编译时检查（枚举变量只能通过此函数）
static_assert(RC_TYPE_UNKNOW <= RC_TYPE_MAX, "rc type max value must be less than or equal to RC_TYPE_MAX.");

// 不是枚举变量，等价于
#if JH >= RC_TYPE_MAX
    #error "value must be less than or equal to RC_TYPE_MAX."
#endif

int main()
{
    return 0;
}
/*
#pragma message 不能计算表达式的值，只能输出字符串字面量。
如果需要在编译时检查条件，可以使用 static_assert。
如果需要输出枚举常量的值，可以手动将其值写入字符串中。

#if 在预处理阶段执行，决定是否编译后续代码。因此无法计算枚举变量值
static_assert 在编译阶段执行，检查条件并生成错误。

[root@ubuntu0006:/media/vdb/study] #g++ static_assert_example.cpp --std=c++11
static_assert_example.cpp:32:6: error: #error "value must be less than or equal to RC_TYPE_MAX."
     #error "value must be less than or equal to RC_TYPE_MAX."
      ^
static_assert_example.cpp:28:1: error: static assertion failed: rc type max value must be less than or equal to RC_TYPE_MAX.
 static_assert(RC_TYPE_UNKNOW <= RC_TYPE_MAX, "rc type max value must be less than or equal to RC_TYPE_MAX.");
 ^
*/