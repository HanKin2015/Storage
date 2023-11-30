/*******************************************************************************
* 文 件 名: backtracking.c
* 文件描述: 函数指针与回溯法
* 备    注: 
* 作    者: HanKin
* 创建日期: 2023.11.30
* 修改日期：2023.11.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

typedef void (*callback_func_t)(const int *, size_t);

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void permute(int *nums, size_t len, size_t depth, callback_func_t callback)
{
    if (depth == len)
    {
        callback(nums, len);
        return;
    }
    for (size_t i = depth; i < len; i++)
    {
        swap(&nums[depth], &nums[i]);
        permute(nums, len, depth + 1, callback);
        swap(&nums[depth], &nums[i]);
    }
}

void print_array(const int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++) 
    { 
      printf("%d ", arr[i]);
    }
    printf("\n"); 
}

int main()
{
  int nums[] = {1, 2, 3};
  permute(nums, sizeof(nums) / sizeof(int), 0, print_array); 
  return 0;
}
/*
1 2 3
1 3 2
2 1 3
2 3 1
3 2 1
3 1 2
*/