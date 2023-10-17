/*******************************************************************************
* 文 件 名: system_example.c
* 文件描述: system函数的正确使用方式
* 作    者: HanKin
* 创建日期: 2023.10.17
* 修改日期：2023.10.17
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
 
int main()
{
    pid_t status;
    status = system("free | awk 'NR==2{print $2,$7}'");
 
    if (-1 == status) {
        printf("system error!");
    } else {
        printf("exit status value = [0x%x]\n", status);
 
        if (WIFEXITED(status)) {
            if (0 == WEXITSTATUS(status)) {
                printf("run shell script successfully.\n");
            } else {
                printf("run shell script fail, script exit code: %d\n", WEXITSTATUS(status));
            }
        } else {
            printf("exit status = [%d]\n", WEXITSTATUS(status));
        }
    }
    
    // 简介使用，使用system函数执行ls -l命令
    int status;
    status = system("ls -l");
    printf("命令退出状态: %d\n", status);
    return 0;
}