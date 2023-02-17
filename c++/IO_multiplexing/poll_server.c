/**
 * 文 件 名: select_server.c
 * 文件描述: 学习select/poll/epoll函数对比
 * 测    试: socat - TCP:localhost:9999 或者写一个客户端demo
 * 作    者: HanKin
 * 创建日期: 2021.09.07
 * 修改日期：2023.02.15
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
与 select 函数使用 fd_set 相比，poll 函数则使用 pollfd 数组作为参数
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

    struct pollfd client_pollfd[MAXCLIENT];
    bzero(client_pollfd, sizeof(client_pollfd));

    int max_index = 0;

    client_pollfd[0].fd = socket_fd;
    client_pollfd[0].events = POLLIN; // events 记录当前文件描述符需要监控哪些内容，POLLIN 代表监控可读内容

    printf("\n---------poll socket server---------\n");
    while (1) {
        printf("wait new socket connect......\n");
        int nready = poll(client_pollfd, max_index+1, -1);

        printf("client_pollfd[0].revents = %d, POLLIN = %d\n", client_pollfd[0].revents, POLLIN);
        if (client_pollfd[0].revents & POLLIN) { // 监控结果放在 revents 内。与 select 函数不同，监控结果不会覆盖原来的参数
            // 这里不再阻塞，会直接返回fd值
            int fd = accept(socket_fd, (struct sockaddr *) &client_address, &len);
            printf("connection_fd: %d\n", fd);

            for (int i = 0; i <= MAXCLIENT; ++i) {
                if (i == MAXCLIENT) {
                    write(STDERR_FILENO, "too many clients\n", 17);
                    return 0;
                }
                if (client_pollfd[i].fd <= 0) {
                    printf("new socket connect, i = %d, fd = %d\n", i, fd);
                    client_pollfd[i].fd = fd;
                    client_pollfd[i].events = POLLIN;
                    if (i > max_index) max_index = i;
                    break;
                }
            }
            nready--;
        }
        
        printf("current max_index = %d, nready = %d\n", max_index, nready);
        for (int i = 0; i <= max_index && nready > 0; ++i) {
            if (client_pollfd[i].fd <= 0) continue;
            if (client_pollfd[i].revents & POLLIN) {
                // 这里不再阻塞，会直接进行read操作，读取失败说明断开了连接
                if ((n = read(client_pollfd[i].fd, buffer, sizeof(buffer))) > 0) {
                    printf("---------read client message---------\n");
                    write(STDOUT_FILENO, buffer, n);
                    printf("--------------------\n\n");
                    write(client_pollfd[i].fd, buffer, n);
                } else {
                    close(client_pollfd[i].fd);
                    printf("connection_fd: %d [CLOSED]\n", client_pollfd[i].fd);
                    client_pollfd[i].fd = -1; // 负的文件描述符表示 poll 函数将忽略当前项
                }
                nready--;
            }
        }
    }

    return 0;
}
/*
跟select流程差不多：
不同的是poll通过client_pollfd[0].revents的事件来判断是否有新的socket连接，如果为1则是新连接，为0则为消息
也可以通过nready值来判断
通过检测client_pollfd[i].revents的事件来判断，select则是通过socket是否在set集合中

[root@ubuntu0006:/media/vdb] #./a.out
pid: 1319
socket_fd: 3

---------poll socket server---------
wait new socket connect......
client_pollfd[0].revents = 1, POLLIN = 1
connection_fd: 4
new socket connect, i = 1, fd = 4
current max_index = 1, nready = 0
wait new socket connect......


client_pollfd[0].revents = 0, POLLIN = 1
current max_index = 1, nready = 1
---------read client message---------
1111111111111
--------------------

wait new socket connect......


client_pollfd[0].revents = 1, POLLIN = 1
connection_fd: 5
new socket connect, i = 2, fd = 5
current max_index = 2, nready = 0
wait new socket connect......


client_pollfd[0].revents = 0, POLLIN = 1
current max_index = 2, nready = 1
---------read client message---------
111
--------------------

wait new socket connect......


client_pollfd[0].revents = 0, POLLIN = 1
current max_index = 2, nready = 1
connection_fd: 4 [CLOSED]
wait new socket connect......
client_pollfd[0].revents = 0, POLLIN = 1
current max_index = 2, nready = 1
connection_fd: 5 [CLOSED]
wait new socket connect......
*/