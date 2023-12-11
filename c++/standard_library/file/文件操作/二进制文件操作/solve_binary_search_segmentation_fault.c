/*******************************************************************************
* 文 件 名: solve_binary_search_segmentation_fault.c
* 文件描述: 之前写的代码中未考虑到二分查找失败导致段错误
* 作    者: HanKin
* 创建日期: 2023.12.07
* 修改日期：2023.12.07
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

int main()
{
    int arr[512] = { 0 };
    for (int i = 0; i < 20; i++) {
        arr[i] = i+1;   // 1~20
    }
    for (int i = 20; i <= 25; i++) {
        arr[i] = i+5;   // 25~30
    }
    for (int i = 0; i < 25; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
    
    //二分查找start_time所在记录位置
    int count = 25;
    int low = 0;
    int high = count - 1;
    int mid = (low + high) / 2;
    int target = 21;
    
    while (low < high && mid >= 1) {
        if (arr[mid] == target) {
            break;
        } else if (arr[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
        mid = (low + high) / 2;
    }
    printf("mid = %d, value = %d\n", mid, arr[mid]);    // 20 25
    return 0;
}