// main.c
#include <stdio.h>
#include "mylib.h"

void call_hello();  // 声明新的共享库中的函数

int main()
{
    main_interface();
    call_hello();  // 调用新的共享库中的函数
    return 0;
}
