/**
* 文 件 名: fopen_example.c
* 文件描述: fopen函数学习
* 作    者: HanKin
* 创建日期: 2023.08.15
* 修改日期：2023.08.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>  // printf

int main(int argc, char *argv[])
{
    const char *file_path = "log.txt";
    FILE *fp = fopen(file_path, "a+");
    
    const char *data = "hello world";
    fprintf(fp, "%s\n", data);
    fclose(fp);  // 使用gcc open_example.c -fsanitize=address无法检测出内存泄露
    return 0;
}