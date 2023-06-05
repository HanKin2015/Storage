/**
* 文 件 名: shmget_example.c
* 文件描述: shmget是System V IPC机制中的一个函数，它通过一个键值来创建或获取一个共享内存段。shmget函数创建的共享内存段可以通过shmat函数映射到进程的地址空间中，从而实现进程间的共享内存
* 作    者: HanKin
* 创建日期: 2023.06.05
* 修改日期：2023.06.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>

#define SIZE 1024

int main()
{
    int shmid ;
    char *shmaddr ;
    struct shmid_ds buf ;
    int flag = 0 ;
    int pid ;
    shmid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT|0600 ) ;
    if ( shmid < 0 )
    {
            perror("get shm  ipc_id error") ;
            return -1 ;
    }
    pid = fork() ;
    if ( pid == 0 )
    {
        shmaddr = (char *)shmat( shmid, NULL, 0 ) ;
        if ( (int)shmaddr == -1 )
        {
            perror("shmat addr error") ;
            return -1 ;
        }
        strcpy( shmaddr, "Hi, I am child process!\n") ;
        shmdt( shmaddr ) ;
        return  0;
    } else if ( pid > 0) {
        sleep(3 ) ;
        flag = shmctl( shmid, IPC_STAT, &buf) ;
        if ( flag == -1 )
        {
            perror("shmctl shm error") ;
            return -1 ;
        }
        printf("shm_segsz =%d bytes\n", buf.shm_segsz ) ;
        printf("parent pid=%d, shm_cpid = %d \n", getpid(), buf.shm_cpid ) ;
        printf("chlid pid=%d, shm_lpid = %d \n",pid , buf.shm_lpid ) ;
        shmaddr = (char *) shmat(shmid, NULL, 0 ) ;
        if ( (int)shmaddr == -1 )
        {
            perror("shmat addr error") ;
            return -1 ;
        }
        printf("%s", shmaddr); 
        shmdt( shmaddr );
        shmctl(shmid, IPC_RMID, NULL) ;
    }else{
        perror("fork error") ;
        shmctl(shmid, IPC_RMID, NULL) ;
    }
    return 0 ;
}