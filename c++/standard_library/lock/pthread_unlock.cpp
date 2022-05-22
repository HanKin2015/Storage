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
    // 获取一片共享内存空间
    const int FLAG = create_flag(222, sizeof(int));
    volatile int* share_var = (int*)shmat(FLAG, NULL, 0);

    printf("share_var = %d\n", (*share_var));
    
    pid_t pid = fork();
    assert(pid >= 0);
    
    /*
    for(int i = 0; i < 10; i++) {
        if (pid == 0) {
            (*share_var) += 1;
            printf("-------child-------share_var+=1    %d\n", (*share_var));
        } else {
            (*share_var) += 2;
            printf("-------parent------share_var+=2   %d\n", (*share_var));
        }
    }
    */
    
    // 设置循环次数
    const int N = 100000;
    if (pid == 0) { // 子进程
        for(int i = 0; i < N; i++) {
            (*share_var) += 1;
            //printf("-------child-------share_var+=1    %d\n", (*share_var));
        }
        printf("----child---finally------share_var =   %d\n", (*share_var));
    } else {    // 父进程
        for(int i = 0; i < N; i++) {
            (*share_var) += 2;
            //printf("-------parent------share_var+=2   %d\n", (*share_var));
        }
        printf("----parent--finally------share_var =   %d\n", (*share_var));
        wait(NULL); // 等待子进程结束
    }
    
    shmctl(FLAG, IPC_RMID, NULL);
    share_var = NULL;
    return 0;
}
