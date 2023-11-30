/*******************************************************************************
* 文 件 名: function_pointer_array.c
* 文件描述: 函数指针数组
* 备    注: 
* 作    者: HanKin
* 创建日期: 2023.11.30
* 修改日期：2023.11.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

void add(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a + b);
}

void subtract(int a, int b)
{
    printf("%d - %d = %d\n", a, b, a - b);
}

void multiply(int a, int b)
{
    printf("%d * %d = %d\n", a, b, a * b);
}

void divide(int a, int b)
{
    if (b == 0)
    {
        printf("cannot divide by zero\n");
    }
    else
    {
        printf("%d / %d = %d\n", a, b, a / b);
    }
}

typedef void (*operation_func_t)(int, int);

int main()
{
    operation_func_t operations[] = {add, subtract, multiply, divide};
    size_t num_operations = sizeof(operations) / sizeof(operation_func_t);
    int a = 10, b = 5;
    for (size_t i = 0; i < num_operations;i++)
    {
      operations[i](a,b);
    }
    return 0;
}
/*
10 + 5 = 15
10 - 5 = 5
10 * 5 = 50
10 / 5 = 2
*/