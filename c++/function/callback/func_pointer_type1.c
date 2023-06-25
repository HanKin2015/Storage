/**
* 文 件 名: func_pointer_type1.c
* 文件描述: 函数指针类型的使用例子
* 作    者: HanKin
* 创建日期: 2023.06.25
* 修改日期：2023.06.25
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>

typedef int (*compare_func)(const void *, const void *);

int compare_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x - y;
}

int main()
{
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n = sizeof(arr) / sizeof(int);
    
    /*
    这三种方法居然都是对的
    
    #include <stdlib.h>

    void qsort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
    */

    //qsort(arr, n, sizeof(int), (compare_func)compare_int);
    qsort(arr, n, sizeof(int), compare_int);
    qsort(arr, n, sizeof(int), &compare_int);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
1 1 2 3 3 4 5 5 5 6 9
*/
