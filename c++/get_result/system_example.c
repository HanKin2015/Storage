/*******************************************************************************
* 文 件 名: system_example.c
* 文件描述: system函数的正确使用方式
* 作    者: HanKin
* 创建日期: 2023.10.17
* 修改日期：2023.10.17
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdlib.h>     // 提供通用工具函数，如 system
#include <sys/wait.h>   // 提供与进程等待相关的宏和函数，如 WIFEXITED 和 WEXITSTATUS
#include <stdio.h>      // 提供输入输出函数，如 printf
 
int main()
{
    pid_t status;
    // 执行 "free | awk 'NR==2{print $2,$7}'" 命令，用于获取系统内存的总量和空闲量
    status = system("free | awk 'NR==2{print $2,$7}'");
 
    if (-1 == status) {
        printf("system error!");
    } else {
        printf("exit status value = [0x%x]\n", status);
 
        if (WIFEXITED(status)) {    // 使用 WIFEXITED 宏检查命令是否正常退出
            if (0 == WEXITSTATUS(status)) { // 使用 WEXITSTATUS 宏获取命令的退出状态码
                printf("run shell script successfully.\n");
            } else {
                printf("run shell script fail, script exit code: %d\n", WEXITSTATUS(status));
            }
        } else {
            printf("exit status = [%d]\n", WEXITSTATUS(status));
        }
    }
    
    // 简介使用，使用system函数执行ls -l命令
    status = system("ls -l");
    printf("命令退出状态: %d\n", status);
    return 0;
}
/*
8174988 6975824
exit status value = [0x0]
run shell script successfully.
总用量 3000
-rw-r--r-- 1 root root    104 6月  26  2023 1
-rw-r--r-- 1 root root      0 6月  25  2023 321.txt
-rw-r--r-- 1 root root   3315 9月  24 11:30 a.cpp
命令退出状态: 0
*/