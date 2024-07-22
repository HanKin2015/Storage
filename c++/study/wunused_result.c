/**
* 文 件 名: wunused_result.c
* 文件描述: 函数返回值未使用警告
* 作    者: HanKin
* 创建日期: 2024.07.18
* 修改日期：2024.07.18
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iconv.h>

// 需要指定才能发出警告
int __attribute__((__warn_unused_result__)) add(int a, int b)
{
    return a + b;
}

// 不指定发不出警告
int sub(int a, int b)
{
    return a - b;
}

int main()
{
    char cmd[BUFSIZ] = { 0 };
    sprintf(cmd, "ps -aux | grep monitor | head -1 | awk '{print $2}' | xargs kill -9");
    system(cmd);

    double ret;
    int n;
    scanf("%d", &n);
    printf("n = %d\n", n);

    add(1, 1);
    int result = add(2, 2);
    (void)add(3, 3);
    sub(4, 4);
    return 0;
}
