// main.c
#include <stdio.h>
#include "mylib.h"

void hello_wrapper();  // 声明共享库中的函数

int main()
{
    main_interface();
    hello_wrapper();  // 调用共享库中的函数
    return 0;
}
