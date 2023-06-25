/**
* 文 件 名: callback_example.c
* 文件描述: 函数指针类型的使用例子
* 作    者: HanKin
* 创建日期: 2023.06.25
* 修改日期：2023.06.25
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>

void print_data(int data)
{
    printf("%d\n", data);
}

void process_data(int data[], int count, void (*callback)(int))
{
    for (int i = 0; i < count; i++) {
        callback(data[i]);
    }
    return;
}

int main()
{
    int data[] = {1, 2, 3, 4, 5};
    int count = sizeof(data) / sizeof(int);
    process_data(data, count, print_data);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
1
2
3
4
5
*/
