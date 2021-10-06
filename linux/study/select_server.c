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

    int client_fd[MAXCLIENT]; // connection_fd 改为数组
    bzero(client_fd, sizeof(client_fd)); // 假设不会有 fd 等于 0。实际上，0 通常是 stdin 的文件描述符

    fd_set all_set;
    FD_ZERO(&all_set);
    FD_SET(socket_fd, &all_set); // 记录 select 将监控哪些文件描述符
    int max_index = 0; // client_fd 数组中使用过的最大下标
    int max_client_fd = socket_fd; // 文件描述符中的最大值

    while (1) {
        fd_set read_set = all_set;

        // select 函数将检查 0 至 max_client_fd 的所有文件描述符。
        // 当这些文件描述符与 read_set 的交集中，部分文件描述符已准备好时，
        // select 函数将返回，并且在 read_set 记录哪些文件描述符已准备好。
        // read_set 将被改变，所以有必要保留 all_set 而把 read_set 传入参数。
        int nready = select(max_client_fd+1, &read_set, NULL, NULL, NULL);

        // socket_fd 已准备好，表示可接受新的连接
        if (FD_ISSET(socket_fd, &read_set)) {
            int fd = accept(socket_fd, (struct sockaddr *) &client_address, &len);
            printf("connection_fd: %d\n", fd);
            FD_SET(fd, &all_set);
            if (fd > max_client_fd) {
                max_client_fd = fd;
            }
            for (int i = 0; i <= MAXCLIENT; ++i) {
                if (i == MAXCLIENT) {
                    write(STDERR_FILENO, "too many clients\n", 17);
                    return 0;
                }
                if (client_fd[i] == 0) {
                    client_fd[i] = fd;
                    if (i > max_index) max_index = i;
                    break;
                }
            }
            nready--;
        }

        // client_fd 中，有部分已准备好，可处理数据
        for (int i = 0; i <= max_index && nready > 0; ++i) {
            if (client_fd[i] == 0) continue;
            if (FD_ISSET(client_fd[i], &read_set)) {
                if ((n = read(client_fd[i], buffer, sizeof(buffer))) > 0) {
                    printf("read: -----\n");
                    write(STDOUT_FILENO, buffer, n);
                    printf("\n-----------\n");
                    write(client_fd[i], buffer, n);
                } else {
                    close(client_fd[i]);
                    printf("connection_fd: %d [CLOSED]\n", client_fd[i]);
                    FD_CLR(client_fd[i], &all_set);
                    client_fd[i] = 0;
                }
                nready--;
            }
        }
    }
    return 0;
}