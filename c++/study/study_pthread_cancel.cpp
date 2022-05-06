#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*
有sleep系统调用函数
*/
static void* pthread_func1(void* arg)
{
    while(1) {
        printf("haha\n");
        sleep(1);
    }
    return NULL;
}

/*
无系统调用，会进入死循环
*/
static void* pthread_func2(void* arg)
{
    int a = 0;
    for( ;; ) {
        printf("a = %d\n", a);
        a++;
    }
    return NULL;
}

/*

*/
static void* pthread_func3(void* arg)
{
    int a = 0;
    for( ;; ) {
        printf("a = %d\n", a);
        a++;
        pthread_testcancel();
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, pthread_func2, NULL);

    pthread_cancel(tid);
    pthread_join(tid, NULL);
    return 0;
}
