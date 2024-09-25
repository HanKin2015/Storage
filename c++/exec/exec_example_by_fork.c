/**
* 文 件 名: exec_example_by_fork.c
* 文件描述: exec系列函数
* 备    注: 这些 exec 系列函数会用指定的新程序替换当前进程的地址空间，并且不会返回到调用它们的程序中。如果 exec 系列函数调用成功，后续的代码将不会被执行。
* 作    者: HanKin
* 创建日期: 2024.09.25
* 修改日期：2024.09.25
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int execl_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        // 如果 execl 失败，打印错误信息并退出
        perror("execl failed");
        _exit(1);
    } else if (pid > 0) {
        // 父进程，等待子进程结束
        wait(NULL);
    } else {
        // fork 失败
        perror("fork failed");
    }
    return 0;
}

int execle_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        char *envp[] = { "USER=guest", "PATH=/tmp", (char *)NULL };
        execle("/bin/ls", "ls", "-l", (char *)NULL, envp);
        // 如果 execl 失败，打印错误信息并退出
        perror("execl failed");
        _exit(1);
    } else if (pid > 0) {
        // 父进程，等待子进程结束
        wait(NULL);
    } else {
        // fork 失败
        perror("fork failed");
    }
    return 0;
}

int execv_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        char *argv[] = { "ls", "-l", (char *)NULL };
        execv("/bin/ls", argv);
        // 如果 execl 失败，打印错误信息并退出
        perror("execl failed");
        _exit(1);
    } else if (pid > 0) {
        // 父进程，等待子进程结束
        wait(NULL);
    } else {
        // fork 失败
        perror("fork failed");
    }
    return 0;
}

int execve_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        char *argv[] = { "ls", "-l", (char *)NULL };
        char *envp[] = { "USER=guest", "PATH=/tmp", (char *)NULL };
        execve("/bin/ls", argv, envp);
        // 如果 execl 失败，打印错误信息并退出
        perror("execl failed");
        _exit(1);
    } else if (pid > 0) {
        // 父进程，等待子进程结束
        wait(NULL);
    } else {
        // fork 失败
        perror("fork failed");
    }
    return 0;
}

int execvp_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        char *argv[] = { "ls", "-l", (char *)NULL };
        execvp("ls", argv);
        // 如果 execl 失败，打印错误信息并退出
        perror("execl failed");
        _exit(1);
    } else if (pid > 0) {
        // 父进程，等待子进程结束
        wait(NULL);
    } else {
        // fork 失败
        perror("fork failed");
    }
    return 0;
}

int execlp_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        execlp("ls", "ls", "-l", (char *)NULL);
        // 如果 execl 失败，打印错误信息并退出
        perror("execl failed");
        _exit(1);
    } else if (pid > 0) {
        // 父进程，等待子进程结束
        wait(NULL);
    } else {
        // fork 失败
        perror("fork failed");
    }
    return 0;
}

int main()
{
    execl_example();
    execle_example();
    execv_example();
    execve_example();
    execvp_example();
    execlp_example();
    return 0;
}
/*
[root@ubuntu0006:~/cmake/hj] #../a.out
===== execl_example(17) =====
总用量 20
-rw-r--r-- 1 root root  778 12月 29  2023 en_US.po
drwxr-xr-x 4 root root 4096 12月 29  2023 locale
-rw-r--r-- 1 root root  653 12月 29  2023 msg.pot
-rwxr-xr-x 3 root root  576 12月 29  2023 test.sh
-rw-r--r-- 1 root root  816 12月 29  2023 zh_CN.po
===== execle_example(37) =====
total 20
-rw-r--r-- 1 root root  778 Dec 29  2023 en_US.po
drwxr-xr-x 4 root root 4096 Dec 29  2023 locale
-rw-r--r-- 1 root root  653 Dec 29  2023 msg.pot
-rwxr-xr-x 3 root root  576 Dec 29  2023 test.sh
-rw-r--r-- 1 root root  816 Dec 29  2023 zh_CN.po
===== execv_example(58) =====
总用量 20
-rw-r--r-- 1 root root  778 12月 29  2023 en_US.po
drwxr-xr-x 4 root root 4096 12月 29  2023 locale
-rw-r--r-- 1 root root  653 12月 29  2023 msg.pot
-rwxr-xr-x 3 root root  576 12月 29  2023 test.sh
-rw-r--r-- 1 root root  816 12月 29  2023 zh_CN.po
===== execve_example(79) =====
total 20
-rw-r--r-- 1 root root  778 Dec 29  2023 en_US.po
drwxr-xr-x 4 root root 4096 Dec 29  2023 locale
-rw-r--r-- 1 root root  653 Dec 29  2023 msg.pot
-rwxr-xr-x 3 root root  576 Dec 29  2023 test.sh
-rw-r--r-- 1 root root  816 Dec 29  2023 zh_CN.po
===== execvp_example(101) =====
总用量 20
-rw-r--r-- 1 root root  778 12月 29  2023 en_US.po
drwxr-xr-x 4 root root 4096 12月 29  2023 locale
-rw-r--r-- 1 root root  653 12月 29  2023 msg.pot
-rwxr-xr-x 3 root root  576 12月 29  2023 test.sh
-rw-r--r-- 1 root root  816 12月 29  2023 zh_CN.po
===== execlp_example(122) =====
总用量 20
-rw-r--r-- 1 root root  778 12月 29  2023 en_US.po
drwxr-xr-x 4 root root 4096 12月 29  2023 locale
-rw-r--r-- 1 root root  653 12月 29  2023 msg.pot
-rwxr-xr-x 3 root root  576 12月 29  2023 test.sh
-rw-r--r-- 1 root root  816 12月 29  2023 zh_CN.po
*/