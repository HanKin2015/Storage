/*******************************************************************************
* 文 件 名: poll_example.c
* 文件描述: /dev/poll 通过内核提供的接口，能够高效地处理大量并发连接
* 备    注: 适用于需要监视大量文件描述符的网络应用
* 作    者: HanKin
* 创建日期: 2025.04.25
* 修改日期：2025.04.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

int main()
{
    int fd = open("example.txt", O_RDONLY); // 打开文件
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN; // 监视可读事件

    while (1) {
        int ret = poll(&pfd, 1, -1); // 等待事件
        if (ret == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        } else if (ret > 0) {
            if (pfd.revents & POLLIN) {
                printf("文件可读\n");
                // 处理可读事件
            }
        }
    }

    close(fd);
    return 0;
}

