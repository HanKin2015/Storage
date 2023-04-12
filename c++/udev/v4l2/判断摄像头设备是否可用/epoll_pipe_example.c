/**
* 文 件 名: epoll_pipe_example.c
* 文件描述: pipe和epoll简单结合使用，残缺版
* 备    注: 来源于chargpt
* 作    者: HanKin
* 创建日期: 2023.04.12
* 修改日期：2023.04.12
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    struct epoll_event event;
    event.data.fd = pipefd[0];
    event.events = EPOLLIN;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, pipefd[0], &event) == -1) {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }

    char buf[256];
    int num_events, i;
    while (1) {
        num_events = epoll_wait(epollfd, &event, MAX_EVENTS, -1);
        for (i = 0; i < num_events; i++) {
            if (event.data.fd == pipefd[0]) {
                ssize_t count = read(pipefd[0], buf, sizeof(buf));
                if (count == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                printf("Received %ld bytes: %.*s\n", count, (int)count, buf);
            }
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
