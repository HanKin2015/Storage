/**
* 文 件 名: acm_callback_function_time.cpp
* 文件描述: 之前打比赛的时候也用到过回调函数
* 参    考：https://blog.csdn.net/u010835747/article/details/117459812
*           https://baike.baidu.com/item/sort%E5%87%BD%E6%95%B0/11042699
* 作    者: HanKin
* 创建日期: 2023.05.18
* 修改日期：2023.05.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>

struct NODE {
    int x;
    int y;
};

int cmp(struct NODE a, struct NODE b)
{
    return a.y < b.y;
}

int main()
{
    struct NODE p = {3, 8};
    struct NODE q = {5, 2};
    struct NODE arr[2] = {[0]=p, [1]=q};
    std::sort(arr, arr+2, cmp);
    for (int i = 0; i < 2; i++) {
        printf("(%d, %d)\n", arr[i].x, arr[i].y);
    }
    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
(5, 2)
(3, 8)
*/

