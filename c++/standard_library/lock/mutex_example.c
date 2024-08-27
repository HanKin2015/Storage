/*******************************************************************************
* 文 件 名: mutex_example.c
* 文件描述: 在编程中，mutex（互斥锁）是一种同步原语，用于保护共享资源，以防止多个线程同时访问或修改该资源
* 备    注: gcc mutex_example.c -lpthread
* 作    者: HanKin
* 创建日期: 2024.08.27
* 修改日期：2024.08.27
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;  // 全局变量

//可以尝试将关于锁的操作去掉，有什么效果
void *function(void *arg)
{
    char *m;
    m = (char *)arg;
    pthread_mutex_lock(&mutex);
    while (*m != '\0') {
        printf("%c", *m);
        fflush(stdout);
        m++;
        usleep(3e5);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
    //return;   // 加上会有警告：
}

int main(int argc, char *argv[])
{
    int rc1, rc2;

    char *str1 = (char *)"hello";
    char *str2 = (char *)"wolrd";
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex, NULL);
    if ((rc1 = pthread_create(&thread1, NULL, function, str1))) {
        fprintf(stdout,"thread 1 create failed: %d\n", rc1);
    }

    if (rc2 = pthread_create(&thread2, NULL, function, str2)) {
        fprintf(stdout,"thread 2 create failed: %d\n", rc2);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
hello
wolrd
[root@ubuntu0006:~/cmake] #vi l.c
[root@ubuntu0006:~/cmake] #gcc l.c -lpthread
[root@ubuntu0006:~/cmake] #./a.out
hwoellrldo

[root@ubuntu0006:~/cmake] #./a.out
whoellrldo

*/
