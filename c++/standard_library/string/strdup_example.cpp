/**
* 文 件 名: strdup_example.cpp
* 文件描述: 学习strdup函数
* 作    者: HanKin
* 创建日期: 2022.12.05
* 修改日期：2022.12.05
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    const char *s = "Golden Global View";
    char *d = NULL;
    // strdup()在内部调用了malloc()为变量分配内存，不需要使用返回的字符串时，需要用free()释放相应的内存空间，否则会造成内存泄漏。
    d = strdup(s);
    if (NULL != d) {
        printf("%s\n",d);
        free(d);
        d = NULL;
    } else {
        printf("d is NULL\n");
    }
    return 0;
}