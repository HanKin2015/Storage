/**
 * 文 件 名: study_condition2.c
 * 文件描述: 单播和广播实例
 * 作    者: HanKin
 * 创建日期: 2021.09.07
 * 修改日期：2021.09.07
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;

void *thread_1(void *data)
{
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond, &lock);
    printf("%s\n", __func__);
    pthread_mutex_unlock(&lock);
}

void *thread_2(void *data)
{
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond, &lock);
    printf("%s\n", __func__);
    pthread_mutex_unlock(&lock);
}

int main(int argc, char const *argv[])
{
    int cid = 0;
    pthread_t pid[2];
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&pid[0], NULL, thread_1, NULL);
    pthread_create(&pid[1], NULL, thread_2, NULL);

    while (1) {
        scanf("%d", &cid);
        getchar();

        if (cid == 1) {
            pthread_cond_signal(&cond); /* 单播，向其中一个线程发送信号 */
        } else if (cid == 2) {
            pthread_cond_broadcast(&cond); /* 广播，向所有等待条件变量的线程发送信号 */
        } else if (cid == 3) {
            break;
        }
    }

    pthread_join(pid[0], NULL);
    pthread_join(pid[1], NULL);

    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
