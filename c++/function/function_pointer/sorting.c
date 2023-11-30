/*******************************************************************************
* 文 件 名: sorting.c
* 文件描述: 排序算法
* 备    注: 
* 作    者: HanKin
* 创建日期: 2023.11.30
* 修改日期：2023.11.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef int (*compare_func_t)(const void *, const void *);

void sort(int *array, size_t size, compare_func_t compare_func)
{
    qsort(array, size, sizeof(int), compare_func);
}

int compare_int(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int compare_reverse_int(const void *a, const void *b)
{
    return (*(int*)b - *(int*)a);
}

int main()
{
    int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    size_t size = sizeof(array) / sizeof(int);
    sort(array, size, compare_int);
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    sort(array, size, compare_reverse_int);
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
/*
1 1 2 3 3 4 5 5 5 6 9
9 6 5 5 5 4 3 3 2 1 1
*/