/**
* 文 件 名: read_PIPE_BUF_value.cpp
* 文件描述: 无名管道pipe学习
* 作    者: HanKin
* 创建日期: 2023.02.16
* 修改日期：2023.02.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }
    
    printf("BUFSIZ: %d\n", BUFSIZ);

    // 获取管道大小（F_GETPIPE_SZ是一个用于获取管道缓冲区大小的文件描述符操作命令）
    int pipe_size = fcntl(pipe_fd[0], F_GETPIPE_SZ);
    printf("Pipe buffer size: %d\n", pipe_size);
    
    // 设置管道的大小（注意，F_SETPIPE_SZ只能增加管道缓冲区大小，不能减小。并且，管道缓冲区大小的实际值可能会受到系统限制，因此需要检查设置后的实际值。）
    // 这是因为缩小管道缓冲区大小可能会导致数据丢失或者阻塞进程，因此操作系统不允许缩小管道缓冲区大小。
    // 如果需要减小管道缓冲区大小，可以先关闭管道，然后重新创建一个大小合适的管道。或者，可以使用其他的进程间通信方式，如共享内存、消息队列等。
    //int set_size = 1024 * 1024; // 1MB
    int set_size = 4888;
    if (fcntl(pipe_fd[0], F_SETPIPE_SZ, set_size) == -1) {
        perror("fcntl");
        return 1;
    }
    
    // 设置1000或者2048返回都是4096，设置4888返回8192，设置1MB返回就是1MB
    pipe_size = fcntl(pipe_fd[0], F_GETPIPE_SZ);
    printf("new Pipe buffer size: %d\n", pipe_size);
    
    sleep(30);
    return 0;
}
/*
BUFSIZ: 8192
Pipe buffer size: 65536
new Pipe buffer size: 8192
*/
