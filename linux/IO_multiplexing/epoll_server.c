/**
 * 文 件 名: select_server.c
 * 文件描述: 学习select/poll/epoll函数对比
 * 测    试: socat - TCP:localhost:9999 或者写一个客户端demo
 * 作    者: HanKin
 * 创建日期: 2021.09.07
 * 修改日期：2021.09.07
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <poll.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define LISTENQ (1024)
#define MAXLINE (1024)
#define MAXCLIENT (1024)

/*
select 和 poll 都有一个缺点，就是只知道有多少个文件描述符已准备好，却不知道具体是哪些，因此需要使用线性扫描来确定，效率较低。试想：有没有别的函数，能不仅仅返回数量，并且一并返回已经准备好的文件描述符呢？

Linux 的 epoll 函数解决了这个问题。epoll 的用法和 select、poll 是类似的：将 socket_fd 加入监视，将新生成的连接加入监视，将已完成的连接退出监视。
*/
int main() 
{
    // 获取进程id
    pid_t pid = getpid();
    printf("pid: %d\n", pid);

    // 创建socket套接字
    int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    printf("socket_fd: %d\n", socket_fd);

    // 服务端地址设置
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9999);

    // 将地址和套接字绑定
    bind(socket_fd, (const struct sockaddr *)&server_address, sizeof(server_address));
    
    // 开始监听
    listen(socket_fd, LISTENQ);

    // 客户端
    struct sockaddr_in client_address;
    char buffer[MAXLINE];
    ssize_t n;
    socklen_t len = sizeof(client_address);

    // events 为 epoll_wait 函数输出结果所用的数组
    struct epoll_event events[MAXCLIENT], ev;

    // 与 select 和 poll 不同，epoll 会创建新的文件描述符
    int epoll_fd = epoll_create(MAXCLIENT);
    printf("epoll_fd: %d\n", epoll_fd);

    // 监视 EPOLLIN 事件
    ev.events = EPOLLIN;

    // ev.data 是自由写入的。epoll_wait 返回的时候，会将 ev.data 原样返回出来
    ev.data.fd = socket_fd;

    // 将 socket_fd 加入监视。当 socket_fd 发生 EPOLLIN 事件时，会将此时写好的 ev.data 的值返回出来
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &ev);

    while (1) {
        int nready = epoll_wait(epoll_fd, events, MAXCLIENT, -1);
        if (nready < 0) return 0;

        // events[0:nready] 是已准备好的文件描述符的 epoll_event 组成的数组。这里直接利用 events[i].data 部分
        for (int i = 0; i < nready; i++) {
            if (events[i].data.fd == socket_fd) { // 有新的 TCP 连接
                int fd = accept(socket_fd, (struct sockaddr *) &client_address, &len);
                printf("connection_fd: %d\n", fd);
                ev.data.fd = fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev); // 加入监视
            } else {
                if ((n = read(events[i].data.fd, buffer, sizeof(buffer))) > 0) {
                    printf("read: -----\n");
                    write(STDOUT_FILENO, buffer, n);
                    printf("\n-----------\n");
                    write(events[i].data.fd, buffer, n);
                } else { // read 返回零，表示 TCP 连接关闭
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, &ev); // 注意：必须先退出连接，再调用 close。这与 select 和 poll 的用法不同
                    close(events[i].data.fd);
                    printf("connection_fd: %d [CLOSED]\n", events[i].data.fd);
                }
            }
        }
    }

    return 0;
}