// 生产者-消费者模型
#include "demo_pthread.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

pthread_cond_t _cond;
pthread_mutex_t _lock;

volatile unsigned int size = 0;
#define MAX_THREAD_NUM 32
int thread_num = 0;
volatile int producer_size = 0;
volatile int consumer_size = 0;
pthread_t tid_list[MAX_THREAD_NUM];


void *consumer(void *ctx)
{

    while (true) {
        pthread_mutex_lock(&_lock);
        while (size == 0) {
            pthread_cond_wait(&_cond, &_lock);
        }
        size--;
        DLOG("[%lu] run consumer... %d", pthread_self(), size);
        pthread_mutex_unlock(&_lock);
        sleep(1);
    }
}

void *producer(void *ctx)
{
    while (true) {
        pthread_mutex_lock(&_lock);
        size += 3;
        DLOG("[%lu] run producer... %d", pthread_self(), size);
        pthread_cond_broadcast(&_cond);/* 通知所有等待的消费者 */
        pthread_mutex_unlock(&_lock);
        sleep(1);
    }
}

void create_consumer()
{
    if (thread_num == MAX_THREAD_NUM) {
        DLOG("%s", "too many thread!");
        return;
    }
    if (pthread_create(&tid_list[thread_num++], NULL, consumer, NULL) != 0) {
        DLOG("create thread-consumer failed: %s", strerror(errno));
    }
    consumer_size++;
    DLOG("[%lu] create thread-consumer success: %lu", pthread_self(), tid_list[thread_num - 1]);
}

void create_producer()
{
    if (thread_num == MAX_THREAD_NUM) {
        DLOG("%s", "too many thread!");
        return;
    }
    if (pthread_create(&tid_list[thread_num++], NULL, producer, NULL) != 0) {
        DLOG("create thread-producer failed: %s", strerror(errno));
    }
    producer_size++;
    DLOG("[%lu] create thread-producer success: %lu", pthread_self(), tid_list[thread_num - 1]);
}


// gcc demo_pthred.c -o demo_pthread -I./ -lpthread
int main(int argc, char *argv[])
{

    int i, j;

    if (pthread_cond_init(&_cond, NULL) != 0) {
        DLOG("init condition failed: %s ", strerror(errno));
    }
    if (pthread_mutex_init(&_lock, NULL)) {
        DLOG("init mutex failed: %s ", strerror(errno));
    }

    create_producer();
    create_producer();
    create_consumer();

    for (j = 0; j < thread_num; ++j) {
        pthread_join(tid_list[j], NULL);
    }
    return 0;
}