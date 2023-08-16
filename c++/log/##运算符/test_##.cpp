/**
* 文 件 名: test_##.cpp
* 文件描述: ##运算符的学习
* 作    者: HanKin
* 创建日期: 2021.05.21
* 修改日期：2023.08.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

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
/*
在这段代码中，## 是 C 预处理器中的一个运算符，用于将两个标记（token）连接成一个标记。在这里，## 运算符用于将 PRINT 宏的第一个参数 type 和 printf_ 这个字符串连接起来，形成一个新的字符串，从而构成一个函数名。

具体来说，当 PRINT(number, 123) 被展开时，预处理器会将 type 和 printf_ 这两个标记连接起来，形成一个新的标记 printf_number，从而将 PRINT 宏展开为 printf_number(123)。同样地，当 PRINT(string, "yes") 被展开时，预处理器会将 type 和 printf_ 这两个标记连接起来，形成一个新的标记 printf_string，从而将 PRINT 宏展开为 printf_string("yes")。

因此，## 运算符可以用于在宏定义中动态生成标识符，从而实现更加灵活的代码生成。
*/