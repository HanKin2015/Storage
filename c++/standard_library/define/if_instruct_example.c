/**
* 文 件 名: if_instruct_example.c
* 文件描述: #if指令学习
* 备    注: #if只支持常量表达式
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

#define z 5
#define t 'k'

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
    
    printf("__cplusplus = %ld\n", __cplusplus);
    #if __cplusplus < 201103L || (defined(_CPPLIB_VER) && _CPPLIB_VER >= 520)
    printf("__cplusplus less than 201103L\n");
    #endif
    
    #if __cplusplus == 199711L || (defined(_CPPLIB_VER) && _CPPLIB_VER >= 520)
    printf("__cplusplus equal 199711L\n");
    #endif
    
    #if (x == 4)
        printf("main X_EQUAL_4\n");
    #else
        printf("main X_NOT_EQUAL_4\n");
    #endif
    
    long int y = 199711L;
    #if y == 199711L
        printf("main Y_EQUAL_199711L\n");
    #else
        printf("main Y_NOT_EQUAL_199711L\n");
    #endif
    
    #if (z == 5)
        printf("main Z_EQUAL_5\n");
    #else
        printf("main Z_NOT_EQUAL_5\n");
    #endif
    
    #if (t == 'k')
        printf("main T_EQUAL_K\n");
    #else
        printf("main T_NOT_EQUAL_K\n");
    #endif
    return 0;
}
/*
只有z是宏定义的，最终是两个数字之间进行比较，#if不能做变量值转换，只能是常量进行比较

C language support ==
__cplusplus = 199711
__cplusplus less than 201103L
__cplusplus equal 199711L
main X_NOT_EQUAL_4
main Y_NOT_EQUAL_199711L
main X_EQUAL_5
main T_EQUAL_K
*/