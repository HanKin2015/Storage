/**
* 文 件 名: compare_unsigned_int.cpp
* 文件描述: 
* 作    者: HanKin
* 创建日期: 2022.08.30
* 修改日期：2022.08.30
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <iostream>

int main(int argc, char *argv[])
{
    int b = -1;
    unsigned int a = 1;
    if (b > a) {
        printf("%d > %d %u > %u\n", b, a, b, a);    // -1 > 1 4294967295 > 1
    } else if (a > b) {
        printf("%d > %d  %u > %u\n", a, b, a, b);
    }

    unsigned int x = 1, y = 2;
    if (x > y) {
        printf("%d > %d\n", x, y);
    } else if ( y > x) {
        printf("%d > %d\n", y, x);  // 2 > 1
    }
    if (x - y > 0) {
        printf("%d > %d %u\n", x, y, x - y);  // 1 > 2 4294967295
    } else if ( y - x > 0) {
        printf("%d > %d\n", y, x);
    }
    unsigned int z = x - y;
    std::cout << z << std::endl;    // 4294967295
    return 0;
}
