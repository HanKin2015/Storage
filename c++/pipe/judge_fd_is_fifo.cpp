/**
* 文 件 名: judge_fd_is_fifo.cpp
* 文件描述: 确认一个fd是PIPE还是FIFO
* 作    者: HanKin
* 创建日期: 2023.03.29
* 修改日期：2023.03.29
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

int main()
{
    printf("PIPE_BUF = %d\n", PIPE_BUF);
    
    int fds[2];
    if (pipe(fds) < 0) {
        perror("pipe error");
        exit(-1);
    }

    pid_t pid = fork();
    if (pid < 0) { // error
        perror("fork error");
        exit(-1);
    }
    else if (pid == 0) { // parent
        ::close(fds[1]); // close write port

    } else { // child
        ::close(fds[0]); // close read port

        struct stat st;
        fstat(fds[1], &st);
        if (S_ISFIFO(st.st_mode)) { // test if FIFO
            printf("this fds[1] is fifo\n");
        } else {
            printf("this fds[1] is not fifo\n");
        }
    }
    return 0;
}
/*
PIPE_BUF = 4096
this fds[1] is fifo
*/