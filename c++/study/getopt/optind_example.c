/*******************************************************************************
* 文 件 名: optind_example.c
* 文件描述: 使用 optind 变量来获取额外的参数
* 备    注: optind 是 getopt 函数中的一个全局变量，它指示下一个将被处理的 argv 元素的索引
* 作    者: HanKin
* 创建日期: 2023.11.23
* 修改日期：2023.11.23
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "p:h:j:")) != -1) {
        switch (opt) {
        case 'p':
            printf("Option -p with value %s\n", optarg);
            while (optind < argc && *argv[optind] != '-') {
                printf("Extra argument: %s\n", argv[optind]);
                optind++;
            }
            break;
        case 'h':
            printf("Option -h with value %s\n", optarg);
            break;
        case 'j':
            printf("Option -j with value %s\n", optarg);
            break;
        case '?':
            printf("invalid params!\n");
            return -1;
        }
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out -p a b c -j h -h k
Option -p with value a
Extra argument: b
Extra argument: c
Option -j with value h
Option -h with value k
*/