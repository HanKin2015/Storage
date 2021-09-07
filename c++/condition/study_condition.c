/**
 * 文 件 名: study_condition1.c
 * 文件描述: 目的是让thread_2先于thread_1执行,可能会出现本身thread2_t先于1则会死锁
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

pthread_mutex_t lock;   // 互斥锁
pthread_cond_t cond;    // 条件变量

void *thread_1(void *data)
{
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond, &lock);    // 条件变量只能等待唤醒
    printf("%s\n", __func__);
    pthread_mutex_unlock(&lock);
}

void *thread_2(void *data)
{
    pthread_mutex_lock(&lock);
    printf("%s\n", __func__);
    pthread_mutex_unlock(&lock);

    pthread_cond_signal(&cond);
}

int main(int argc, char const *argv[])
{
    pthread_t pid[2];   // 两个线程
    
    // 动态初始化
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL); 

    // 静态初始化
    pthread_mutex_t blank_mtx = PTHREAD_MUTEX_INITIALIZER;
    memcpy(&lock, &blank_mtx, sizeof(pthread_mutex_t));
    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    memcpy(&cond, &blank_cond, sizeof(pthread_cond_t));
    
    pthread_create(&pid[0], NULL, thread_1, NULL);
    pthread_create(&pid[1], NULL, thread_2, NULL);

    pthread_join(pid[0], NULL);
    pthread_join(pid[1], NULL);

    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}

