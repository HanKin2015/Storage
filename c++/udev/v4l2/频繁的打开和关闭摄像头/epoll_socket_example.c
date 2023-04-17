/**
* 文 件 名: epoll_socket_example.c
* 文件描述: epoll和socket结合
* 备    注: 来源于chatgpt
* 作    者: HanKin
* 创建日期: 2023.04.12
* 修改日期：2023.04.12
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

int main(int argc, char *argv[]) {
    int listen_sock, conn_sock, epoll_fd, nfds, n, i;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    struct epoll_event ev, events[MAX_EVENTS];

    // 创建监听 socket
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 绑定地址和端口
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);
    if (bind(listen_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // 开始监听
    if (listen(listen_sock, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // 创建 epoll 实例
    epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    // 添加监听 socket 到 epoll 实例
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_sock, &ev) < 0) {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    // 循环等待事件
    while (1) {
        nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds < 0) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        // 处理所有事件
        for (i = 0; i < nfds; i++) {
            if (events[i].data.fd == listen_sock) {
                // 有新连接
                conn_sock = accept(listen_sock, (struct sockaddr *)&cli_addr, &cli_len);
                if (conn_sock < 0) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }

                // 将新连接添加到 epoll 实例
                ev.events = EPOLLIN;
                ev.data.fd = conn_sock;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_sock, &ev) < 0) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            } else {
                // 有数据可读
                char buf[1024];
                n = read(events[i].data.fd, buf, sizeof(buf));
                if (n < 0) {
                    perror("read");
                    exit(EXIT_FAILURE);
                } else if (n == 0) {
                    // 连接关闭
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL) < 0) {
                        perror("epoll_ctl: conn_sock");
                        exit(EXIT_FAILURE);
                    }
                    close(events[i].data.fd);
                } else {
                    // 打印收到的数据
                    printf("Received %d bytes: %.*s\n", n, n, buf);
                }
            }
        }
    }

    return 0;
}
