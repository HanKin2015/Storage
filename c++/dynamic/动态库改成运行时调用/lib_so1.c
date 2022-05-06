//lib_so1.c
#include <stdio.h>
int fun();
int fun_so()
{
    printf("%s[%d]:%s\n", __FILE__, __LINE__, __FUNCTION__);
    fun();
    return 0;
}
