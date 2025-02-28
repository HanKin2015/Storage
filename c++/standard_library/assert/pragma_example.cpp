/*******************************************************************************
* 文 件 名: pragma_example.cpp
* 文件描述: #pragma message
* 备    注: #pragma message 不能计算表达式的值，只能输出字符串字面量
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

// 使用宏来输出调试信息（#将传入的参数 x 转换为字符串字面量。例如，STRINGIFY(Hello) 会被替换为 "Hello"）
// IFY 并不是一个特定单词的正式简写，而是一个常见的后缀，用于构成动词或形容词，表示某种状态或过程。在编程中，尤其是在宏定义中，IFY 通常用于表示“使得某种状态”或“转换为某种形式”。
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#pragma message("RC_TYPE_SPICEC_SBC = " TOSTRING(RC_TYPE_SPICEC_SBC))
#pragma message("RC_TYPE_MAX = " TOSTRING(RC_TYPE_MAX))

// 宏定义的地方一定要两层
#define VALUE 42
#pragma message(STRINGIFY(VALUE)) // 输出 "VALUE"
#pragma message(TOSTRING(VALUE))  // 输出 "42"

int main()
{
    return 0;
}
/*
[root@ubuntu0006:/media/vdb/study] #g++ pragma_example.cpp
pragma_example.cpp:20:69: note: #pragma message: RC_TYPE_SPICEC_SBC = RC_TYPE_SPICEC_SBC
 #pragma message("RC_TYPE_SPICEC_SBC = " TOSTRING(RC_TYPE_SPICEC_SBC))
                                                                     ^
pragma_example.cpp:21:55: note: #pragma message: RC_TYPE_MAX = 31
 #pragma message("RC_TYPE_MAX = " TOSTRING(RC_TYPE_MAX))
                                                       ^
pragma_example.cpp:25:33: note: #pragma message: VALUE
 #pragma message(STRINGIFY(VALUE)) // 输出 "VALUE"
                                 ^
pragma_example.cpp:26:32: note: #pragma message: 42
 #pragma message(TOSTRING(VALUE))   // 输出 "42"
                                ^

#pragma message 不能计算表达式的值，只能输出字符串字面量。
*/