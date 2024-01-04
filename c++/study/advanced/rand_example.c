/*******************************************************************************
* 文 件 名: rand_example.c
* 文件描述: 随机数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.01.04
* 修改日期：2024.01.04
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    unsigned seed = time(NULL);
    srand(seed);
    const int MIN_VALUE = 10;
    const int MAX_VALUE = 188;
    for (int i = 0; i < 20; i++) {
        int number = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
        printf("%d%c", number, i == 19 ? '\n' : ' ');
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
172 178 155 55 18 108 183 60 147 161 134 183 152 186 103 166 158 78 28 154
[root@ubuntu0006:~/cmake] #./a.out
31 116 137 74 145 179 18 165 84 136 94 45 67 65 187 96 153 20 34 188
*/