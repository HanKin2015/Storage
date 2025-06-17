#include <stdio.h>
#include "mylib.h"

int main()
{
    main_interface();
    call_hello();  // 调用新的共享库中的函数
    return 0;
}
