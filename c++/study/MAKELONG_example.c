/**
* 文 件 名: MAKELONG_example.c
* 文件描述: windows中MAKELONG宏
* 作    者: HanKin
* 创建日期: 2024.07.18
* 修改日期：2024.07.18
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#define MAKELONG(a, b) (((long)a) | (((long)b) << 16))

int main()
{
    printf("MAKELONG(067b:2303) = %ld\n", MAKELONG(0x2207, 0x0019));
    long ret = (1659 | (8963 << 16));
    printf("ret = %ld\n", ret);
    return 0;
}
