/**
* 文 件 名: redefinition.c
* 文件描述: 大意了，没有理解到其中的玄妙
* 背    景: 一个模块需要使用到node定义，因此单独编译需要。而另外一个模块需要调用这个模块函数，
*           如果不定义就报错未定义，定义了又是重复定义，就是这么一回事儿
* 作    者: HanKin
* 创建日期: 2023.06.26
* 修改日期：2023.06.26
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>

#ifndef test
#define test
typedef struct __node {
    int x;
    int y;
} node;
#endif

#ifndef test
#define test
typedef struct __node {
    int x;
    int y;
} node;
#endif

int main(int argc, char *argv[])
{
    printf("hello redefinition\n");
    return 0;
}
/*
在这段代码中，使用了预处理指令 #ifndef 和 #define 来避免重复定义结构体 node。这是因为在 C 语言中，如果同一个标识符被定义了多次，编译器会报错，提示重复定义。

在第一次使用 #ifndef 和 #define 定义结构体 node 时，预处理器会检查 test 是否已经被定义。由于在此之前 test 没有被定义过，因此预处理器会将 test 定义为一个宏，并且定义结构体 node。

在第二次使用 #ifndef 和 #define 定义结构体 node 时，预处理器会检查 test 是否已经被定义。由于在第一次定义时已经将 test 定义为一个宏，因此第二次定义时 test 已经被定义过了，预处理器会跳过这段代码，不会再次定义结构体 node。

因此，虽然在代码中出现了两次对结构体 node 的定义，但由于使用了预处理指令 #ifndef 和 #define，避免了重复定义，因此编译器不会报错。
*/