/*******************************************************************************
* 文 件 名: setsockopt_example.cpp
* 文件描述: 用于设置套接字的各种属性选项（如超时时间、缓冲区大小、地址复用等），可在套接字创建后、连接前或连接后调用
* 作    者: HanKin
* 备    注: 在C语言中，socketpair函数用于创建一对相互连接的套接字。这对套接字可以用于在同一台机器上的进程间通信。
* 创建日期: 2023.09.28
* 修改日期：2025.09.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("sockfd is invalid");
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1357);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 允许端口在 TIME_WAIT 状态下被重新绑定（允许端口复用）
    // 可在套接字创建后、连接前或连接后调用
    int opt = 1;    // 0 禁用，非 0 启用
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt failed");
        goto EXIT;
    }

    // 开始监听
    if (listen(sockfd, 10) == -1) {
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        goto EXIT;
    }

    // 无限循环接收请求
    printf("======waiting for client's request======\n"); 
    while(1) {
        printf("没有客户端连接就会卡住在accpt函数\n");
        int conn_handle = accept(sockfd, (struct sockaddr*)NULL, NULL);
        if (conn_handle == -1) { 
            printf("accept socket error: %s(errno: %d)", strerror(errno), errno); 
            continue; 
        }
        printf("sockfd=%d 接受到客户端conn_handle=%d\n", sockfd, conn_handle);
        printf("有客户端连接后就会卡住在recv函数\n");
        char buffer[BUFSIZ];
        memset(buffer, 0, sizeof(buffer));
        int msg_size = recv(conn_handle, buffer, BUFSIZ, 0); 
        buffer[msg_size] = '\0'; 
        printf("recv msg from client: %s\n", buffer); 
        close(conn_handle); 
    }

EXIT:
    if (sockfd != -1) {
        close(sockfd);
    }
    printf("1\n");
    return 0;
}
/*
我明明设置了允许端口复用，但是运行server时还是bind失败，想不通
搞明白了，如果当前server程序设置了允许端口复用，那么客户端连接后，server程序可以返回重新启动。但是如果没有设置，那么server程序无法反复重新启动，这时候会报错bind failed: Address already in use

当一个程序使用某个端口（比如 8080）进行网络通信后，若程序异常退出或正常关闭，这个端口并不会立即释放，而是会进入一个 TIME_WAIT 状态（通常持续几分钟）。这是 TCP 协议的设计，用于确保网络中残留的数据包被正确处理，避免混乱。

在默认情况下，如果此时有新的程序尝试绑定（bind）同一个端口，会出现 “地址已在使用”（Address already in use）的错误。

而通过 setsockopt 设置 SO_REUSEADDR 选项后，操作系统会允许新的套接字绑定到处于 TIME_WAIT 状态的端口，实现 “端口复用”。
*/