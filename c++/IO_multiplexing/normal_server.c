/**
 * 文 件 名: normal.c
 * 文件描述: 学习select/poll/epoll函数对比
 * 测    试: socat - TCP:localhost:9999 或者写一个客户端demo
 * 作    者: HanKin
 * 创建日期: 2021.09.07
 * 修改日期：2023.02.14
 *
 * Copyright (c) 2023 HanKin. All rights reserved.
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
socket_fd 和 connection_fd 与其它文件描述符并无二致，就像使用 <fcntl.h> 里的 open 函数
打开文件时，返回的文件描述符一样。实际上，在 Linux 系统中，每个进程打开的文件描述符可以
在 /proc/<pid>/fd/ 文件夹下找到。
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
    
    printf("\n---------normal socket server---------\n");
    while (1) {
        // 连接客户端（会卡住在accept函数）
        printf("wait socket connect......\n");
        int connection_fd = accept(socket_fd, (struct sockaddr *)&client_address, &len);
        printf("connection_fd: %d\n", connection_fd);
        
        // 读取客户端下发的消息
        printf("wait client message......\n");
        while ((n = read(connection_fd, buffer, sizeof(buffer))) > 0) {
            printf("read clien msg:\n");
            write(STDOUT_FILENO, buffer, n);    // 输出消息到标准输出端
            printf("-------回射消息--------\n");
            write(connection_fd, buffer, n);    // 回射消息到客户端
        }

        // 关闭服务端
        close(connection_fd);
        printf("connection_fd: %d [CLOSED]\n\n", connection_fd);
    }

    return 0;
}
/*
pid: 1943
socket_fd: 3

---------normal socket server---------
wait socket connect......
connection_fd: 4
wait client message......
read clien msg:
222222
-------回射消息--------
read clien msg:
1111
-------回射消息--------
connection_fd: 4 [CLOSED]

wait socket connect......
connection_fd: 4
wait client message......
connection_fd: 4 [CLOSED]

wait socket connect......
^C

客户端第一次连接，发送了两条消息，然后断开再连接再断开。

打开新的控制台，进入 root 用户：
[root@ubuntu0006:~] #ll /proc/22424/fd
总用量 0
dr-x------ 2 root root  0 2月  14 14:28 ./
dr-xr-xr-x 9 root root  0 2月  14 14:26 ../
lrwx------ 1 root root 64 2月  14 14:28 0 -> /dev/pts/4
lrwx------ 1 root root 64 2月  14 14:28 1 -> /dev/pts/4
lrwx------ 1 root root 64 2月  14 14:28 2 -> /dev/pts/4
lrwx------ 1 root root 64 2月  14 14:28 3 -> socket:[1054079230]
*/