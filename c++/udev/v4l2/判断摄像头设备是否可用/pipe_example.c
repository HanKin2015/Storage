/**
* 文 件 名: pipe_example.c
* 文件描述: pipe的简单使用，只能在具有亲缘关系的父子进程之间进行通信
* 备    注: 来源于chargpt
* 作    者: HanKin
* 创建日期: 2023.04.12
* 修改日期：2023.04.12
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buf[1024];

    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {  // 子进程
        close(fd[1]);  // 关闭写端
        while (1) {
            memset(buf, 0, sizeof(buf));
            if (read(fd[0], buf, sizeof(buf)) == 0) {
                printf("parent close the pipe\n");
                break;
            }
            printf("child read from pipe: %s", buf);
        }
        close(fd[0]);  // 关闭读端
        exit(0);
    } else {  // 父进程
        close(fd[0]);  // 关闭读端
        while (1) {
            memset(buf, 0, sizeof(buf));
            printf("parent input: ");
            fgets(buf, sizeof(buf), stdin);
            if (strcmp(buf, "exit\n") == 0) {
                close(fd[1]);  // 关闭写端
                break;
            }
            write(fd[1], buf, strlen(buf));
        }
        close(fd[1]);  // 关闭写端
        wait(NULL);
        exit(0);
    }
}
