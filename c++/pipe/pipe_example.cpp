/**
* 文 件 名: pipe_example.cpp
* 文件描述: 无名管道pipe学习
* 作    者: HanKin
* 创建日期: 2021.09.16
* 修改日期：2023.02.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <unistd.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX_BUF 1024

static int test(int pid)
{
    int fd[2];             // 文件描述符
    char writebuf[] = "this is a test!\n";    //写缓冲区
    char readbuf[20];      //读缓冲区
    if((pipe(fd)) < 0)     //创建管道
    {
        printf("创建管道失败!\n");
        return -1;
    }
    write(fd[1],writebuf,sizeof(writebuf) );   //向管道写入端写入数据
    read(fd[0], readbuf, sizeof(writebuf) );   //从管道读出端读出数据
    printf("%s", readbuf); //输出字符串
    printf("管道的读fd是%d,管道的写fd是%d pid是%d \n", fd[0], fd[1], pid);  //打印管道描述符
    close(fd[0]);              // 关闭管道的读出端文件描述符
    close(fd[1]);              // 关闭管道的写入端文件描述符
    return 0;
}

int main()
{
    int pipefd[2];
    char buf[MAX_BUF];
    pid_t pid;
        
    printf("line:%d pid:%d\n", __LINE__, getpid());

    // 定义函数 int pipe(int pipefd[2]);
    pipe(pipefd);
    pid = fork();        
    if (pid > 0) {
        printf( "This is in the father process,here write a string to the pipe.\n" );
        char s[] = "Hello world , this is write by pipe.\n";
        close(pipefd[0]);
        write(pipefd[1], s, sizeof(s));
        printf("line:%d pid:%d\n", __LINE__, pid);
    } else if (pid == 0) {
        printf( "This is in the child process,here read a string from the pipe.\n" );
        close(pipefd[1]);
        read(pipefd[0], buf, sizeof(buf));
        printf("%s\n", buf);
        printf("line:%d pid:%d\n", __LINE__, pid);
    }

    // 定义函数 pid_t waitpid(pid_t pid,int * status,int options);
    waitpid(pid, NULL, 0);
    close(pipefd[0]);
    close(pipefd[1]);

    test(getpid());
    return 0;
}
