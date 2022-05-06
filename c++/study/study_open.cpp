/**
 * 文 件 名: study_open.cpp
 * 文件描述: 学习open函数
 * 作    者: HanKin
 * 创建日期: 2021.08.12
 * 修改日期：2021.08.12
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static void open_exist_file()
{
    int fd = open("data_study_open.txt", O_RDWR);
    if(fd < 0) {
        fprintf(stderr, "[%d] open: error %d, %s\n", __LINE__, errno, strerror(errno));
        exit(1);
    }
    const char *msg = "hello  hahaha\n";
    int count = 10;
    while(count--) {
        write(fd, msg, strlen(msg));
    }
    char buf[1024] = {0};
    int num = 10;
    while(num--) {
        read(fd, buf, strlen(msg));
    }

    // 打开的文件描述符一定要记得关闭，否则资源会被大量的占用，导致内存不够
    close(fd);
    return;
}

static void open_not_exist_file()
{
    int fd = open("data_study_open.txt", O_WRONLY | O_CREAT, 0644);
    //file文件不存在，所以在书写第二个参数时，记得把O_CREAT加上，
    //如果不加O_CREAT的话，程序就会报此文件不存在
    if(fd < 0) {
        fprintf(stderr, "[%d] open: error %d, %s\n", __LINE__, errno, strerror(errno));
        exit(1);
    }
    const char *msg = "hello file\n";
    int count = 10;
    while(count--) {
        write(fd, msg, strlen(msg));
    }
    close(fd);
    return;
}

int main()
{
    open_not_exist_file();
    open_exist_file();
    return 0;
}
