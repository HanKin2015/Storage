/**
* 文 件 名: malloc_no_free.cpp
* 文件描述: malloc分配的内存未被释放
* 作    者: HanKin
* 创建日期: 2023.08.15
* 修改日期：2023.08.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main()
{
    // 被测代码：预埋一个栈溢出bug
    int *p = (int *)malloc(sizeof(int));
    *p = 5;
    printf("%p = %d\n", p, *p);
    free(p);    // 使用g++ malloc_no_free.cpp -fsanitize=address可检测出内存泄露
    return 0;
}
