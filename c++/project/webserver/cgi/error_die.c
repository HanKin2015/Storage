/*******************************************************************************
* 文 件 名: error_die.c
* 文件描述: 通常用于处理致命错误 - 它会打印错误信息（通常结合系统错误信息）并终止程序。这在系统编程和网络编程中特别常见，用于快速处理无法恢复的错误
* 备    注: 非标准函数
* 作    者: HanKin
* 创建日期: 2025.09.18
* 修改日期：2025.09.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * 输出错误信息并终止程序
 * @param msg 自定义错误信息
 */
void error_die(const char *msg)
{
    // 打印自定义信息和系统错误信息
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    
    printf("EXIT_FAILURE = %d\n", EXIT_FAILURE);
    
    // 终止程序，返回非0状态码表示异常退出
    exit(EXIT_FAILURE);
}

// 使用示例
int main()
{
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        // 如果文件打开失败，调用error_die
        error_die("无法打开文件");
    }
    
    // 正常操作文件...
    fclose(file);
    return 0;
}
/*
root@hankin:~/opencv# ./a.out 
无法打开文件: No such file or directory
EXIT_FAILURE = 1
*/