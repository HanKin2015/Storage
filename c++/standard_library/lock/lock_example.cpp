#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


/**
 *  返回一片共享内存标识符，用于后续获取该共享内存，以及销毁该共享内存
 *  INDEX_OF_KEY —— 自定义的该共享内存序号
 *  LENGTH —— 共享内存大小
 */
const int create_flag(const int INDEX_OF_KEY, const unsigned int LENGTH) {
    // 生成key
    const char* FILE_PATH = "./";
    key_t key = ftok(FILE_PATH, INDEX_OF_KEY);

    // 创建共享内存空间
    const int FLAG = shmget(key, LENGTH, IPC_CREAT | 0666);

    return FLAG;
}


// 定义进程锁结构体
typedef struct MUTEX_PACKAGE {
    // 锁以及状态
    pthread_mutex_t lock;
    pthread_mutexattr_t lock_attr;
    // 在共享内存中的标识符
    int FLAG;
} mutex_package_t;


// 初始化进程锁结构体
const int init(void* pthis) {
    mutex_package_t* mp = (mutex_package_t*)pthis;
    // 初始化锁状态，设置状态状态为——进程共享
    pthread_mutexattr_init(&(mp->lock_attr));
    pthread_mutexattr_setpshared(&(mp->lock_attr), PTHREAD_PROCESS_SHARED);
    // 用锁状态来初始化锁
    pthread_mutex_init(&(mp->lock), &(mp->lock_attr));

    return 0;
}

// 在共享内存上定义进程锁结构体并且返回其位置
mutex_package_t* create_mutex_package(const int INDEX) {
    const int FLAG = create_flag(INDEX, sizeof(mutex_package_t));
    mutex_package_t* mp = (mutex_package_t*)shmat(FLAG, NULL, SHM_R | SHM_W);
    mp->FLAG = FLAG;

    assert(init(mp) == 0);

    return mp;
}

// 销毁进程锁结构体，利用其FLAG变量索引到其占用的共享内存并销毁
const int destory_mutex_package(mutex_package_t* mp) {
    // 销毁锁和锁状态
    pthread_mutex_destroy(&(mp->lock));
    pthread_mutexattr_destroy(&(mp->lock_attr));

    // 释放共享内存
    assert(shmctl(mp->FLAG, IPC_RMID, NULL) == 0);

    return 0;
}

int main()
{
    // 创建自定义进程锁
    mutex_package_t* mp = create_mutex_package(111);

    // 获取一片共享内存空间
    const int FLAG = create_flag(222, sizeof(int));
    volatile int* x = (int*)shmat(FLAG, NULL, 0);

    // 创建新进程
    int id = fork();
    assert(id >= 0);

    // 设置循环次数
    const int N = 1000000;

    // 父进程每次加1，子进程每次加2
    int i;
    for (i = 0; i < N; ++i) {
        if (id > 0) {  // 父进程
            // 加锁
            pthread_mutex_lock(&(mp->lock));
            int temp = *x;
            *x = temp+1;
            // 解锁
            pthread_mutex_unlock(&(mp->lock));
        } else {  // 子进程
            // 加锁
            pthread_mutex_lock(&(mp->lock));
            int temp = *x;
            *x = temp+2;
            // 解锁
            pthread_mutex_unlock(&(mp->lock));
        }

    }

    // 等待循环完毕
    sleep(1);

    // 打印
    printf("pid= %d, x_address= %x, x= %d\n", getpid(), x, *x);

    // 等待打印完毕
    sleep(1);

    // 销毁进程锁,释放申请的共享内存
    if (id > 0) {  // 父进程
        destory_mutex_package(mp);
        mp = NULL;
        shmctl(FLAG, IPC_RMID, NULL);
        x = NULL;
        printf("父进程释放资源完毕\n");
    }
    return 0;
}