/*******************************************************************************
* 文 件 名: multi_thread_exec_command.c
* 文件描述: 多线程执行linux命令
* 作    者: HanKin
* 创建日期: 2023.10.16
* 修改日期：2023.10.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int read_file_content()
{
    FILE *fp;
    char output[512] = { 0 };

    // 使用popen以读取模式运行ls -l命令
    fp = popen("cat ./ret_value", "r");
    if (fp == NULL) {
        perror("popen错误");
        return -1;
    }

    // 读取命令的输出
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }

    // 关闭文件指针
    pclose(fp);
    return 0;
}    

int main(int argc, char *argv[])
{
    int n = 1;  // 默认一个线程执行
    if (argc == 2) {
        n = atoi(argv[1]);
    }

    printf("current thread count = %d\n", n);

    (void)read_file_content();
    
    printf("I am main, I'm a thread!\n" "main_thread_ID = %lu\n", pthread_self());
    return 0;
}

