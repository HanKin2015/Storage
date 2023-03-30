/**
* 文 件 名: socketpair_example.cpp
* 文件描述: 创建一对套接字，用于父子进程通信
* 作    者: HanKin
* 创建日期: 2023.03.30
* 修改日期：2023.03.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>

int main()
{
    int fds[2];
    int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
    if (ret < 0) {
        perror("socketpair error");
        exit(-1);
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(-1);
    } else if (pid == 0) { // parent
        close(fds[0]); // close one port
        char buf[128];
        snprintf(buf, sizeof(buf), "hello, I am parent process");
        write(fds[1], buf, strlen(buf));
        printf("Parent write: %s\n", buf);
    } else { // child
        close(fds[1]); // close another port
        char buf[128];
        read(fds[0], buf, sizeof(buf));
        printf("Child read: %s\n", buf);
    }
    return 0;
}
/*
Parent write: hello, I am parent process
Child read: hello, I am parent process
*/
