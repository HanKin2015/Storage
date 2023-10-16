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
    fp = popen("cat /stmp/device_helper/ret_value", "r");
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

int cmd_count = 5;
void *tfn(void *arg)
{
    int i = *(int *)&arg;
    int status = -1;
    if (i % cmd_count == 0 || i % cmd_count == 1 || i % cmd_count == 2) {
        status = system("/stmp/device_helper/devicehelper -p hj");
        printf("policy命令退出状态: %d\n", status);
    } else if (i % cmd_count == 3) {
        status = system("/stmp/device_helper/devicehelper --agent_status hj");
        printf("agent_status命令退出状态: %d\n", status);
    } else if (i % cmd_count == 4) {
        status = system("/stmp/device_helper/devicehelper --internal_list_status hj");
        printf("internal_list_status命令退出状态: %d\n", status);
    }
    (void)read_file_content();
    
    printf("I'm %dth thread, Thread_ID = %lu\n", i+1, pthread_self());
    return NULL;
}

int main(int argc, char *argv[])
{
    int n = 1;  // 默认一个线程执行
    if (argc == 2) {
        n = atoi(argv[1]);
    }

    printf("current thread count = %d\n", n);

    pthread_t tid;
    for (int i = 0; i < n; i++) {
        pthread_create(&tid, NULL, tfn, (void *)(long)i);  //将i转换为指针，在tfn中再强转回整型。
    }

    sleep(n);
    printf("I am main, I'm a thread!\n" "main_thread_ID = %lu\n", pthread_self());
    return 0;
}

