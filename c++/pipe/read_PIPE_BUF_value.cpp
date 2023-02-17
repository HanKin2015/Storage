/**
* 文 件 名: read_PIPE_BUF_value.cpp
* 文件描述: 无名管道pipe学习
* 作    者: HanKin
* 创建日期: 2023.02.16
* 修改日期：2023.02.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <unistd.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    int fds[2];
    pipe(fds);
    int fd = fds[1];

    // 获取管道大小
    int pipe_capacity = fcntl(fd, F_GETPIPE_SZ);
    printf("old pipe_capacity = %d\n", pipe_capacity);
    // 设置管道的大小
    int size = 1000;
    int ret = fcntl(fd, F_SETPIPE_SZ, size);
    pipe_capacity = fcntl(fd, F_GETPIPE_SZ);
    printf("new pipe_capacity = %d\n", pipe_capacity);
	return 0;
}
