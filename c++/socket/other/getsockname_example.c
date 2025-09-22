/*******************************************************************************
* 文 件 名: getsockname_example.cpp
* 文件描述: 用于获取套接字当前关联的本地地址和端口信息（适用于已绑定的套接字）
* 作    者: HanKin
* 备    注: 
* 创建日期: 2025.09.18
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
        return -1;
    }

    // 获取本地地址信息
    struct sockaddr_in local_addr;
    socklen_t len = sizeof(local_addr);
    if (getsockname(sockfd, (struct sockaddr*)&local_addr, &len) == -1) {
        perror("getsockname failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    // 转换端口为宿主字节序并打印
    printf("本地端口: %d\n", ntohs(local_addr.sin_port));
    close(sockfd);
    return 0;
}
/*
root@hankin:~/opencv# ./a.out 
本地端口: 1357
*/