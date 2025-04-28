/*******************************************************************************
* 文 件 名: kqueue_example.cpp
* 文件描述: kqueue 是 BSD 系统（如 FreeBSD、macOS）上的事件通知机制（编译不过fatal error: sys/event.h: 没有那个文件或目录）
* 备    注: kqueue 和 dev/poll 是两种用于处理 I/O 事件的高效机制，主要用于提高网络应用程序的性能
* 作    者: HanKin
* 创建日期: 2025.04.25
* 修改日期：2025.04.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/event.h>
#include <sys/time.h>

#ifdef __FreeBSD__  // 或 #ifdef __APPLE__
#include <sys/event.h>
#else
#include <sys/epoll.h>  // 或其他 Linux 头文件
#endif

int main() {
    int kq = kqueue(); // 创建 kqueue
    if (kq == -1) {
        perror("kqueue");
        exit(EXIT_FAILURE);
    }

    int fd = open("example.txt", O_RDONLY); // 打开文件
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct kevent change;
    EV_SET(&change, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL); // 监视可读事件

    while (1) {
        struct kevent event;
        int nev = kevent(kq, &change, 1, &event, 1, NULL); // 等待事件
        if (nev == -1) {
            perror("kevent");
            exit(EXIT_FAILURE);
        } else if (nev > 0) {
            printf("文件可读\n");
            // 处理可读事件
        }
    }

    close(fd);
    close(kq);
    return 0;
}

