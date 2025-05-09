// mylib_caller.c
#include <stdio.h>

void hello_wrapper();  // 声明之前的共享库中的函数

void call_hello()
{
    hello_wrapper();  // 调用之前的共享库中的 hello_wrapper 函数
}
