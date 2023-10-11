/*******************************************************************************
* 文 件 名: socketpair_example.cpp
* 文件描述: 学习socketpair函数
* 作    者: HanKin
* 备    注: 在C语言中，socketpair函数用于创建一对相互连接的套接字。这对套接字可以用于在同一台机器上的进程间通信。
* 创建日期: 2023.09.28
* 修改日期：2023.09.28
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
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
    int send_len = send(sv[0], "ok\n", 3, 0);   // linux可以使用write
    int recv_len = recv(sv[1], buf, sizeof(buf) - 1, 0);
    printf("send_len %d recv_len %d buf %s\n", send_len, recv_len, buf);
    return 0;
}