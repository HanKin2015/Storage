/**
 * 文 件 名: pthread_pool.c
 * 文件描述: 线程池
 * 作    者: HanKin
 * 创建日期: 2021.08.17
 * 修改日期：2021.08.17
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/* 链表头插法 */
#define LL_ADD(item, list) do { \
    item->pre  = NULL;          \
    item->next = list;          \
    if (list != NULL) list->pre = item; \
    list = item;                \
} while (0)

/* 链表移除元素 */
#define LL_REMOVE(item, list) do {          \
    if (item->pre != NULL) item->pre->next = item->next;    \
    if (item->next != NULL) item->next->pre = item->pre;    \
    if (list == item) list = item->next;    \
    item->pre = item->next = NULL;          \
} while (0)

typedef struct MANAGER THREADPOOL;

/* 执行队列 */
struct WORKER {
    pthread_t thread;
    bool terminate;
    THREADPOOL *pool;
    
    struct WORKER *pre;
    struct WORKER *next;
};

/* 任务队列 */
struct JOB {
    void (*func)(void *user_data);
    void *user_data;
    
    struct JOB *pre;
    struct JOB *next;
};

/* 管理组件 */
struct MANAGER {
    struct WORKER *workers;
    struct JOB *jobs;
    
    pthread_cond_t jobs_cond;
    pthread_mutex_t jobs_mtx;
};

static void *thread_callback(void *arg)
{
    struct WORKER *worker = (struct WORKER *)arg;
    
    while (true) {
        
        pthread_mutex_lock(&worker->pool->jobs_mtx);
        while (worker->pool->jobs == NULL) {
            if (worker->terminate) break;
            
            // int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
            // pthread_cond_wait内部操作先解锁再加锁，因此中间部分是没有在锁内
            pthread_cond_wait(&worker->pool->jobs_cond, &worker->pool->jobs_mtx);
        }
        
        if (worker->terminate) {
            pthread_mutex_unlock(&worker->pool->jobs_mtx);
            break;
        }
        
        struct JOB *job = worker->pool->jobs;
        LL_REMOVE(job, worker->pool->jobs);
        
        pthread_mutex_unlock(&worker->pool->jobs_mtx);

        job->func(job->user_data);
    }

    free(worker);
    pthread_exit(NULL);
}

/**
 * 线程池创建
 */
int thread_pool_create(THREADPOOL *pool, int workers_num)
{
    if (workers_num < 1) workers_num = 1;
    if (pool == NULL) return -1;
    
    memset(pool, 0, sizeof(THREADPOOL));
    
    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    memcpy(&pool->jobs_cond, &blank_cond, sizeof(pthread_cond_t));
    
    pthread_mutex_t blank_mtx = PTHREAD_MUTEX_INITIALIZER;
    memcpy(&pool->jobs_mtx, &blank_mtx, sizeof(pthread_mutex_t));
    
    for (int i = 0; i < workers_num; i++) {
        struct WORKER *worker = (struct WORKER *)malloc(sizeof(struct WORKER));
        if (worker == NULL) {
            perror("malloc");
            return -2;
        }
        memset(worker, 0, sizeof(struct WORKER));   // malloc之后一定要进行memset
        worker->pool = pool;
        
        // On success, pthread_create() returns 0; on error, it returns an error number, and the contents of *thread are undefined.
        int ret = pthread_create(&worker->thread, NULL, thread_callback, worker);
        if (ret) {
            perror("pthread_create");
            return -3;
        }

        LL_ADD(worker, pool->workers);
    }
    return 0;
}

/**
 * 线程池添加任务
 */
void thread_pool_push(THREADPOOL *pool, struct JOB *job)
{
    pthread_mutex_lock(&pool->jobs_mtx);
    
    LL_ADD(job, pool->jobs);
    pthread_cond_signal(&pool->jobs_cond);
    
    pthread_mutex_unlock(&pool->jobs_mtx);
    return;
}

/**
 * 线程池销毁
 *
 * todo: 还是有可能还有任务未完成
 */
int thread_pool_destroy(THREADPOOL *pool)
{
    while (pool->jobs != NULL);
    usleep(500);
    
    struct WORKER *worker = NULL;
    for (worker = pool->workers; worker != NULL; worker = worker->next) {
        worker->terminate = true;
        //pthread_join(worker->thread, NULL);
    }
    
    pthread_mutex_lock(&pool->jobs_mtx);
    pthread_cond_broadcast(&pool->jobs_cond);
    pthread_mutex_unlock(&pool->jobs_mtx);
    return 0;
}


/**
 * 0-999的计数
 * 用1000个任务，每一个任务打一个数字
 *
 * todo: job和job->user->data如何释放
 */
#if 0   // debug
void print_number(void *arg)
{
    int *number = static_cast<int *>(arg);
    printf("number: %d\n", *number);
}

int main()
{
    // 1.线程池大小
    const int thread_pool_size = 5;
    
    // 2.创建线程池
    THREADPOOL *pool;
    pool = (THREADPOOL *)malloc(sizeof(THREADPOOL));
    int ret = thread_pool_create(pool, thread_pool_size);
    if (ret != 0) {
        printf("thread_pool_create failed! ret = %d\n", ret);
        return -1;
    }
    
    // 3.创建任务并加入线程池
    struct JOB *job[1000];
    for (int i = 0; i < 1000; i++) {
        job[i] = (struct JOB*)malloc(sizeof(struct JOB));
        job[i]->func = print_number;
        int *tmp = (int *)malloc(sizeof(int));
        *tmp = i;
        job[i]->user_data = tmp;
        thread_pool_push(pool, job[i]);
    }
    
    // 4.销毁线程池
    thread_pool_destroy(pool);
    
    // 5.释放内存
    for (int i = 0; i < 1000; i++) {
        free(job[i]->user_data);
        job[i]->user_data = NULL;
        free(job[i]);
        job[i] = NULL;
    }
    free(pool);
    pool = NULL;
    return 0;
}
#endif
