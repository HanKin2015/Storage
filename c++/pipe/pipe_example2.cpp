/**
* 文 件 名: pipe_example2.cpp
* 文件描述: 创建父进程到子进程的管道，父进程通过管道向子进程传送数据
* 作    者: HanKin
* 创建日期: 2021.03.14
* 修改日期：2023.03.14
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE    80

int main()
{
    pid_t pid;
    int fd[2];
    char buf[MAXLINE];

    int ret = pipe(fd);
    if (ret < 0) {
        perror("pipe error\n");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    }
    else if (pid == 0) { // child
        close(fd[1]);
        
        int n = read(fd[0], buf, MAXLINE);
        printf("line: %d, pid: %d, buf: %s\n", __LINE__, pid, buf);
        write(STDOUT_FILENO, buf, n);
    }
    else { // parent
        close(fd[0]);

        const char *s = "hello world\n";
        write(fd[1], s, strlen(s));

        waitpid(pid, NULL, 0);
        exit(0);
    }

    return 0;
}
/*
[root@ubuntu0006:/media/hankin/vdb] #./a.out
line: 42, pid: 0, buf: hello world

hello world
*/
