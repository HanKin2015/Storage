#include <stdio.h>

// 打印数字
void printf_number(int num)
{
    printf("number is %d\n", num); 
    return ;
}

// 打印字符串
void printf_string(char *str)
{
    printf("string is %s\n", str); 
    return ;
}

// 工厂模式打印
#define PRINT(type, value) {    \
    printf_##type(value);       \
}

int main()
{
    PRINT(number, 123);
    PRINT(string, "yes");
    return 0;
}
