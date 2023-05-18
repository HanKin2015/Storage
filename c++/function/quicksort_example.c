/**
* 文 件 名: quicksort_example.c
* 文件描述: 快速排序算法可以使用回调函数来比较元素
* 备    注：可以证明，快速排序的平均时间复杂度也是O(nlog2n)。因此，该排序方法被认为是目前最好的一种内部排序方法。
* 作    者: HanKin
* 创建日期: 2023.05.18
* 修改日期：2023.05.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>

int compare(const void* a, const void* b)
{
    int x = *(const int*)a;
    int y = *(const int*)b;
    if (x < y) return -1;
    else if (x > y) return 1;
    else return 0;
}

// 这个可以理解为第三方库，但是里面具体的排序方式可以自定义，如修改compare就可以从大到小排序
void quicksort(int* arr, int left, int right, int (*cmp)(const void*, const void*))
{
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (cmp(&arr[j], &pivot) < 0) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        for (int k = 0; k < 5; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;
        int p = i + 1;
        for (int k = 0; k < 5; k++) {
            printf("%d ", arr[k]);
        }
        printf("%d(p)\n", p);
        quicksort(arr, left, p - 1, cmp);
        quicksort(arr, p + 1, right, cmp);
    }
}

int main()
{
    int arr[] = {5, 4, 1, 3, 2};
    quicksort(arr, 0, 4, compare);
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
