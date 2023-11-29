/*源文件*/
#include <stdio.h>
#include "fun0.h"
#include "fun1.h"
#include "fun_lib_a.h"
#include "fun_lib_so.h"

int main(void)
{
    #ifdef USE_DEBUG
        printf("Debug Application startup.\r\n");
    #endif
    
        fun0_printf();
        fun1_printf();
        fun_lib_a_printf();
        fun_lib_so_printf();
        return 0;
}