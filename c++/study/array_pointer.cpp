/*******************************************************************************
* 文 件 名: array_pointer.cpp
* 文件描述: 数组指针也能使用++进行传值，并且作为参数也能进行修改原来的值
* 作    者: HanKin
* 创建日期: 2023.11.21
* 修改日期：2023.11.21
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <time.h>
#include <string.h>

void func(int *arr)
{
    for (int i = 0 ; i < 10; i++) {
        *(arr++) = i;
    }
    return;
}

int main()
{
    int arr[100] = { 0 };
    func(arr);
    printf("arr[5] = %d\n", arr[5]);
    return 0;
}