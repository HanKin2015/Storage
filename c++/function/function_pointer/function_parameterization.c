/*******************************************************************************
* 文 件 名: function_parameterization.c
* 文件描述: 函数参数化
* 备    注: 
* 作    者: HanKin
* 创建日期: 2023.11.30
* 修改日期：2023.11.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

void process_array(int *array, size_t size, int (*process)(int))
{
    for (size_t i = 0; i < size; i++)
    {
        array[i] = process(array[i]);
    }
}

int increment(int n)
{
    return n + 1;
}

int main()
{
    int array[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(array) / sizeof(int);
    process_array(array, size, increment);
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
/*
2 3 4 5 6
*/