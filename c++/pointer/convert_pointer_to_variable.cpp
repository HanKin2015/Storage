/**
* 文 件 名: convert_pointer_to_variable.cpp
* 文件描述: 转换指针为变量
* 作    者: HanKin
* 创建日期: 2022.12.14
* 修改日期：2022.12.14
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <inttypes.h>
using namespace std;

int main(int argc, char *argv[])
{
    uint64_t x = 2022;
    uint64_t *p = &x;
    printf("p = %p\n", p);
    
    uint64_t addr = (uint64_t)(void *)p;
    printf("addr = 0x%lx\n", addr); // 这里一定要lx打印，否则会有截断
    
    uint64_t y = 0;
    memcpy(&y, (void *)addr, sizeof(y));
    printf("y = %ld\n", y);
    return 0;
}
/*
p = 0x7ffec17b4718
addr = 0x7ffec17b4718
y = 2022
*/