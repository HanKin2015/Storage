/*******************************************************************************
* 文 件 名: enum_example.cpp
* 文件描述: 枚举变量
* 备    注: 枚举变量不能在预处理时替换，只能在编译时替换
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

#if RC_TYPE_UNKNOW <= RC_TYPE_MAX
    #error "value is less than or equal to RC_TYPE_MAX."
#endif

#if HJ <= RC_TYPE_MAX
    #error "value is less than or equal to RC_TYPE_MAX."
#endif

#if HH <= RC_TYPE_MAX
    #error "value is less than or equal to RC_TYPE_MAX."
#endif

#if JH <= RC_TYPE_MAX
    #error "value is less than or equal to RC_TYPE_MAX."
#endif

int main()
{
    return 0;
}
/*
[root@ubuntu0006:/media/vdb/study] #g++ enum_example.cpp
enum_example.cpp:28:6: error: #error "value is less than or equal to RC_TYPE_MAX."
     #error "value is less than or equal to RC_TYPE_MAX."
      ^
enum_example.cpp:32:6: error: #error "value is less than or equal to RC_TYPE_MAX."
     #error "value is less than or equal to RC_TYPE_MAX."
      ^
enum_example.cpp:36:6: error: #error "value is less than or equal to RC_TYPE_MAX."
     #error "value is less than or equal to RC_TYPE_MAX."
      ^

原因是枚举变量值并没有被替换，进一步验证见pragma_example.cpp文件
*/