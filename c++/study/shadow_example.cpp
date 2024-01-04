/*******************************************************************************
* 文 件 名: shadow_example.cpp
* 文件描述: 某语句块作用域变量与更大作用域的另一变量同名时发出警告（此警告未包含在-Wall选项中，需单独开启）
* 备    注: 
* 作    者: HanKin
* 创建日期: 2022.06.24
* 修改日期：2024.01.03
*
* Copyright (c) 2022 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <unistd.h>

int g;
static void test(int x, int y)
{
    short  x;
    int    y;
    double g;
    return;
}

int main()
{
    test(3, 4);
    return 0;
}
/*
[root@ubuntu0006:/media/sangfor/vdb/TransferStation] #g++ test_shadow.cpp -Wshadow
test_shadow.cpp: In function ‘void test(int, int)’:
test_shadow.cpp:8:12: error: declaration of ‘short int x’ shadows a parameter
     short  x;
            ^
test_shadow.cpp:9:12: error: declaration of ‘int y’ shadows a parameter
     int    y;
            ^
test_shadow.cpp:10:12: warning: declaration of ‘g’ shadows a global declaration [-Wshadow]
     double g;
            ^
test_shadow.cpp:5:5: note: shadowed declaration is here
 int g;
     ^
*/