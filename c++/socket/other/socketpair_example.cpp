/*******************************************************************************
* 文 件 名: socketpair_example.cpp
* 文件描述: 学习socketpair函数
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
using namespace std;

int main(int argc, char *argv[])
{
    int sv[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
        perror("socketpair");
        return 1;
    }

    printf("socket pair created: %d, %d\n", sv[0], sv[1]);

    // 使用sv[0]和sv[1]进行进程间通信
    // socketpair函数只能用于同一台机器上的进程间通信，如果需要在不同机器之间进行通信，可以考虑使用网络套接字

    char buf[1024] = { 0 };
    const char *msg = "I am sv[0], hello sv[1]";
    int send_len = send(sv[0], msg, strlen(msg), 2);   // linux可以使用write
    int recv_len = recv(sv[1], buf, sizeof(buf) - 1, 0);
    printf("send_len = %d, recv_len = %d, recv buf is '%s'\n", send_len, recv_len, buf);
    
    char read_buf[1024] = { 0 };
    int write_len = write(sv[0], msg, strlen(msg));
    int read_len = read(sv[1], read_buf, sizeof(read_buf));
    printf("write_len = %d, read_len = %d, read buf is '%s'\n", write_len, read_len, read_buf);
    return 0;
}
/*
root@hankin:~/opencv# ./a.out 
socket pair created: 3, 4
send_len = 23, recv_len = 23, recv buf is 'I am sv[0], hello sv[1]'
write_len = 23, read_len = 23, read buf is 'I am sv[0], hello sv[1]'

#include <sys/socket.h>
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

flags：
控制发送行为的标志，通常设为 0（默认行为）。常见取值：
MSG_OOB：发送带外数据（紧急数据），用于 TCP 紧急模式。
MSG_DONTROUTE：不经过路由表，直接发送到本地网络。
MSG_NOSIGNAL：发送失败时不产生 SIGPIPE 信号（适用于避免程序崩溃）。

send(sockfd, buf, len, 0) 等价于 write(sockfd, buf, len)。
flags 参数是 send() 相对于 write() 的扩展。
*/