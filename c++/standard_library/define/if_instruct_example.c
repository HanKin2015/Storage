/**
* 文 件 名: if_instruct_example.c
* 文件描述: #if指令学习
* 备    注: gcc if_instruct_example.c
* 作    者: HanKin
* 创建日期: 2023.08.17
* 修改日期：2023.08.17
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>

const char test = 'k';
const int x = 4;
#if (test == 'k')
    #define TEST_EQUAL_K
#else
    #define TEST_NOT_EQUAL_K
#endif

#if (x == 4)
    #define X_EQUAL_4
#else
    #define X_NOT_EQUAL_4
#endif

#if (x > 4)
    #define X_MORE_THAN_4
#else
    #define X_NOT_MORE_THAN_4
#endif

int main(int argc, char *argv[])
{
    #ifdef TEST_EQUAL_K
    printf("TEST_EQUAL_K\n");
    #endif
    
    if (test == 'k') {
        printf("C language support ==\n");
    } else {
        printf("C language not support ==\n");
    }
    
    #ifdef X_EQUAL_4
    printf("X_EQUAL_4\n");
    #endif
    
    #ifdef X_MORE_THAN_4
    printf("X_MORE_THAN_4\n");
    #endif
    return 0;
}