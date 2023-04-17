/**
* 文 件 名: epoll_pipe_demo.c
* 文件描述: epoll和pipe结合使用
* 备    注: 父进程间接性地发送消息，子进程通过epoll进行监控接收消息
* 作    者: HanKin
* 创建日期: 2023.04.12
* 修改日期：2023.04.12
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <time.h>

#define MAX_EVENTS 10

int main()
{
    int pipefd[2];
    pid_t pid;
    char buf[1024];

    if (pipe(pipefd) < 0) {
        perror("pipe error");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {      // 子进程
        close(pipefd[1]);       // 关闭写端
        
        // 创建epoll
        int epollfd = epoll_create1(0);
        if (epollfd == -1) {
            perror("epoll_create1");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }

        struct epoll_event event;
        event.data.fd = pipefd[0];
        event.events = EPOLLIN;

        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, pipefd[0], &event) == -1) {
            perror("epoll_ctl");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }
        
        char buf[BUFSIZ];
        int num_events, i;
        while (1) {
            num_events = epoll_wait(epollfd, &event, MAX_EVENTS, -1);
            for (i = 0; i < num_events; i++) {
                if (event.data.fd == pipefd[0]) {
                    memset(buf, 0, sizeof(buf));
                    ssize_t count = read(pipefd[0], buf, sizeof(buf));
                    if (count == -1) {
                        perror("read");
                        close(pipefd[0]);
                        exit(EXIT_FAILURE);
                    } else if (count == 0) {
                        printf("parent close the pipe\n");
                        close(pipefd[0]);
                        exit(EXIT_FAILURE);
                    }
                    
                    time_t timep = time(NULL);
                    struct tm *lt = localtime(&timep);
                    char ntime[BUFSIZ] = {0};
                    strftime(ntime, sizeof(ntime), "%Y-%m-%d %H:%M:%S", lt);
                    printf("%s [INFO] Child received %ld bytes from pipe: %.*s\n", ntime, count, (int)count, buf);
                }
            }
        }
    
        close(pipefd[0]);  // 关闭读端
        exit(EXIT_FAILURE);
    } else {               // 父进程
        close(pipefd[0]);  // 关闭读端
        
        long long count = 0;
        while (1) {
            char* bufs[3] = {"hello world", "I love you", "how old are you"};
            for (int i = 0; i < 3; i++) {
                memset(buf, 0, sizeof(buf));
                memcpy(buf, bufs[i], strlen(bufs[i]) + 1);
                write(pipefd[1], buf, strlen(buf));
                sleep(1);
            }
            
            sleep(2);
            
            count++;
            if (count > 3) {
                printf("current count %lld, stop demo\n", count); 
                break;      // 停止程序
            }
        }
        close(pipefd[1]);   // 关闭写端
        wait(NULL);
        exit(0);
    }
    
    return 0;
}
/*
手动点击的Enter键出现空行的。

[root@ubuntu0006:/media/hankin/vdb] #./a.out
2023-04-12 14:41:26 [INFO] Child received 11 bytes from pipe: hello world
2023-04-12 14:41:27 [INFO] Child received 10 bytes from pipe: I love you
2023-04-12 14:41:28 [INFO] Child received 15 bytes from pipe: how old are you

2023-04-12 14:41:31 [INFO] Child received 11 bytes from pipe: hello world
2023-04-12 14:41:32 [INFO] Child received 10 bytes from pipe: I love you
2023-04-12 14:41:33 [INFO] Child received 15 bytes from pipe: how old are you

2023-04-12 14:41:36 [INFO] Child received 11 bytes from pipe: hello world
2023-04-12 14:41:37 [INFO] Child received 10 bytes from pipe: I love you
2023-04-12 14:41:38 [INFO] Child received 15 bytes from pipe: how old are you

current count 4, stop demo
parent close the pipe
[root@ubuntu0006:/media/hankin/vdb] #
*/
