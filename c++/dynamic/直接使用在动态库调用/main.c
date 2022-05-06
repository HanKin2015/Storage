//main.c 
#include <stdio.h>
int fun_so();

int fun()
{
    printf("%s[%d]:%s\n", __FILE__, __LINE__, __FUNCTION__);
    printf("in main\n");
    return 0;
}

int main()
{
    printf("%s[%d]:%s\n", __FILE__, __LINE__, __FUNCTION__);
    fun_so();
    return 0;
}
