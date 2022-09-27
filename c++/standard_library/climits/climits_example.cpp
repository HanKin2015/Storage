/**
* 文 件 名: climits_example.cpp
* 文件描述: 输出数值类型范围
* 备    注: 编译去除警告(g++ climits_example.cpp -std=c++11 -Wno-format)
* 作    者: HanKin
* 创建日期: 2022.09.27
* 修改日期：2022.09.27
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <climits>
#include <cstdio>
#include <cstdint>
#include <inttypes.h>
using namespace std;

/*
C语言标准中的整型类型，用的是int关键字。
__int16、__int32、__int64这类关键字是在微软自家的VC编译器所扩展的类型。以__int64为例来说，不同的编译器对64位整数的扩展有所不同。VC6.0的64位整数分别叫做__int64与unsigned __int64，其范围分别是[-2^63, 2^63)与[0,2^64)，它实际上相当于long long 类型。
*/

int main(int argc, char *argv[])
{
    printf("不同int类型占用的字节数大小和范围：\n");
    printf("int      : %d    %d ~ %d\n", sizeof(int), INT_MIN, INT_MAX);
    printf("int8_t   : %d    %d ~ %d\n", sizeof(int8_t), INT8_MIN, INT8_MAX);
    printf("int16_t  : %d    %d ~ %d\n", sizeof(int16_t), INT16_MIN, INT16_MAX);
    printf("int32_t  : %d    %d ~ %d\n", sizeof(int32_t), INT32_MIN, INT32_MAX);
    printf("int64_t  : %d    %lld ~ %lld\n", sizeof(int64_t), INT64_MIN, INT64_MAX);
    printf("uint     : %d    0 ~ %ld\n", sizeof(unsigned int), UINT_MAX);
    printf("uint8_t  : %d    0 ~ %d\n", sizeof(uint8_t), UINT8_MAX);
    printf("uint16_t : %d    0 ~ %d\n", sizeof(uint16_t), UINT16_MAX);
    printf("uint32_t : %d    0 ~ %ld\n", sizeof(uint32_t), UINT32_MAX);
    printf("uint64_t : %d    0 ~ %lld\n", sizeof(uint64_t), UINT64_MAX);
    cout << "uint64_t : " << sizeof(uint64_t) << "    0 ~ " << UINT64_MAX << endl;
    return 0;
}

/*
不同int类型占用的字节数大小和范围：
int      : 4    -2147483648 ~ 2147483647
int8_t   : 1    -128 ~ 127
int16_t  : 2    -32768 ~ 32767
int32_t  : 4    -2147483648 ~ 2147483647
int64_t  : 8    -9223372036854775808 ~ 9223372036854775807
uint     : 4    0 ~ 4294967295
uint8_t  : 1    0 ~ 255
uint16_t : 2    0 ~ 65535
uint32_t : 4    0 ~ 4294967295
uint64_t : 8    0 ~ -1
uint64_t : 8    0 ~ 18446744073709551615
*/