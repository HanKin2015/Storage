/**
* 文 件 名: static_example.cpp
* 文件描述: 静态变量和静态函数
* 作    者: HanKin
* 创建日期: 2023.03.29
* 修改日期：2023.03.29
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

static void test()
{
    static int x = 0;
    x++;
    printf("x = %d\n", x);
    return;
}

int main(int argc, char *argv[])
{
    test();
    test();
    return 0;
}
/*
x = 1
x = 2
*/