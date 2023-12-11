/*******************************************************************************
* 文 件 名: getcwd_example.c
* 文件描述: getcwd函数的使用
* 作    者: HanKin
* 创建日期: 2023.10.17
* 修改日期：2023.10.17
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <unistd.h>

int main()
{
    char cwd[1024] = { 0 };
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("当前工作目录: %s\n", cwd);
    } else {
        perror("获取工作目录失败");
        return 1;
    }
    chdir("/path/to/directory");
    return 0;
}
