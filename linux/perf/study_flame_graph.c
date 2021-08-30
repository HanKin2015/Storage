#include <pthread.h>
#include <stdio.h>
#include <errno.h>

void func_d()
{
    int i;
    for(i = 0; i < 50000; i++);
}

void func_a()
{
    int i;
    for(i = 0; i < 100000; i++);
    func_d();
}

void func_b()
{
    int i;
    for(i = 0; i < 200000; i++);
}

void func_c()
{
    int i;
    for(i = 0; i < 300000; i++);
}

void *thread_fun(void *param)
{
    while (1) {
        int i;
        for(i = 0; i < 100000; i++);
        func_a();
        func_b();
        func_c();
    }
}

int main(void)
{
    pthread_t tid1, tid2;
    int ret;
    ret = pthread_create(&tid1, NULL, thread_fun, NULL);
    if (ret == -1) {
        perror("pthread_create");
        return -1;
    }

    ret = pthread_create(&tid2, NULL, thread_fun, NULL);
    if (ret == -1) {
        perror("pthread_create");
        return -1;
    }    

    if (pthread_join(tid1, NULL) != 0) {
        perror("pthread_join");
        return -2;
    }

    if (pthread_join(tid2, NULL) != 0) {
        perror("pthread_join");
        return -2;
    }
    return 0;
}