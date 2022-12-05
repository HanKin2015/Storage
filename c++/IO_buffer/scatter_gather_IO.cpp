/**
* 文 件 名: scatter_gather_IO.cpp
* 文件描述: 分散/聚集IO
* 作    者: HanKin
* 创建日期: 2022.12.01
* 修改日期：2022.12.01
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#inlcude <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
using namespace std;

static int writev_example()
{
    struct iovec iov[3];
    ssize_t nr;
    int fd, i;

    char *buf[] = {
        "Just because you can do it, doesn't mean that you have to.\n",
        "Just because you can do it, doesn't mean that you have to.\n",
        "Just because you can do it, doesn't mean that you have to.\n" };

    fd = open("c++.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        perror("open");
    }

    /* fill out therr iovec structures */
    for (i = 0; i < 3; ++i) {
        iov[i].iov_base = buf[i];
        iov[i].iov_len  = strlen(buf[i]) + 1;
    }

    /* write a single call, write them all out */
    nr = writev(fd, iov, 3);
    if (nr != -1) {
        perror("writev");
        return 1;
    }

    if (close(fd)) {
        perror("close");
    }
    return 0;
}

static int readv_example()
{
    char foo[48], bar[50], baz[49];
    struct iovec iov[3];
    ssize_t nr;
    int fd, i;

    fd = open("c++.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    /* set up our iovec structrues */
    iov[0].iov_base = foo;
    iov[0].iov_len = sizeof(foo);
    iov[1].iov_base = bar;
    iov[1].iov_len = sizeof(bar);
    iov[2].iov_base = baz;
    iov[2].iov_len = sizeof(baz);

    /* read into the structures with a single call */
    nr = readv(fd, iov, 3);
    if (nr == -1) {
        perror("readv");
        return 1;
    }

    for (i = 0; i < 3; ++i) {
        printf("%d: %s", i, (char*) iov[i].iov_base);
    }

    if (close(fd)) {
        perror("close");
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    writev_example();
    readv_example();
    return 0;
}
/*
BUFSIZ is 8192
BUFSIZ after setvbuf is 8192
hello world
buf:8192
Z after setvbuf is

buf2:buf:8192
Z after setvbuf is

buf2:
buf:8192
Z after setvbuf is

*/