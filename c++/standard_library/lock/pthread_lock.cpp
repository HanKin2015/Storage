/*
    互斥量 实现 多进程 之间的同步 
*/
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <assert.h>

// 定义进程锁结构体
typedef struct MUTEX_PACKAGE {
    int flag;    // 内存中标识符
    pthread_mutex_t mutex;  // 锁
    pthread_mutexattr_t mutexattr;  // 状态对象
} mutex_package_t;

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

int main()
{
    // 创建自定义进程锁
    mutex_package_t* mp;

    /*
    // 创建映射区文件
    int fd = open("mt_test",O_CREAT|O_RDWR,0777);
    if (fd == -1 ) {
        perror("open file:"); 
        exit(1); 
    }
    ftruncate(fd,sizeof(*mp));
    mp = mmap(NULL,sizeof(*mp),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    unlink("mt_test");
    */
 
    // 建立映射区
    mp = (mutex_package_t*)mmap(NULL, sizeof(*mp), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);

    memset(mp, 0x00, sizeof(*mp));
 
    pthread_mutexattr_init(&mp->mutexattr); // 初始化 mutex 属性
    pthread_mutexattr_setpshared(&mp->mutexattr, PTHREAD_PROCESS_SHARED);   // 修改属性为进程间共享
    pthread_mutex_init(&mp->mutex, &mp->mutexattr);      // 初始化一把 mutex 锁
    
    // 获取一片共享内存空间
    const int FLAG = create_flag(222, sizeof(int));
    int* share_var = (int*)shmat(FLAG, NULL, 0);

    printf("share_var = %d\n", (*share_var));
    
    pid_t pid = fork();
    assert(pid >= 0);
    
    // 设置循环次数：次数越大效果越明显，概率更高
    const int N = 100000;
    if (pid == 0) { // 子进程
        for(int i = 0; i < N; i++) {
            pthread_mutex_lock(&mp->mutex);
            (*share_var) += 1;
            //printf("-------child-------share_var+=1    %d\n", (*share_var));
            pthread_mutex_unlock(&mp->mutex);
        }
        printf("----child---finally------share_var =   %d\n", (*share_var));
    }
    else {  // 父进程
        for(int i = 0; i < N; i++) {
            pthread_mutex_lock(&mp->mutex);
            (*share_var) += 2;
            //printf("-------parent------share_var+=2   %d\n", (*share_var));
            pthread_mutex_unlock(&mp->mutex);
        }
        printf("----parent--finally------share_var =   %d\n", (*share_var));
        wait(NULL); // 等待子进程结束
    }
    
    pthread_mutexattr_destroy(&mp->mutexattr);  // 销毁 mutex 属性对象
    pthread_mutex_destroy(&mp->mutex);          // 销毁 mutex 锁
    mp = NULL;
    shmctl(FLAG, IPC_RMID, NULL);   // 释放共享内存，否则共享变量值不变，不会从0开始
    share_var = NULL;
    return 0;
}
