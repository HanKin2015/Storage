/**
* 文 件 名: print_define.cpp
* 文件描述: 调试打印宏值
* 作    者: HanKin
* 创建日期: 2022.12.16
* 修改日期：2022.12.16
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <cstdio>

#define LOG_TIGGER 111

int main(int argc, char *argv[])
{
    int x = LOG_TIGGER;
    printf("x = %d\n", x);
    return 0;
}
