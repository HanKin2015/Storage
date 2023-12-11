/*******************************************************************************
* 文 件 名: popen_example.c
* 文件描述: popen函数的使用
* 作    者: HanKin
* 创建日期: 2023.10.17
* 修改日期：2023.10.17
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

int main()
{
    FILE *fp = NULL;
    char output[512] = { 0 };

    // 使用popen以读取模式运行ls -l命令
    fp = popen("ls -l", "r");
    if (fp == NULL) {
        perror("popen错误");
        return 1;
    }

    // 读取命令的输出
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }

    // 关闭文件指针
    pclose(fp);
    return 0;
}
