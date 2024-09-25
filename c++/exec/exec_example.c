/**
* 文 件 名: exec_example.c
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

int execl_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    execl("/bin/ls", "ls", "-l", (char *)NULL);
    printf("这句话都打印不出来，你信不信？\n");
    return 0;
}

int execle_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    char *envp[] = { "USER=guest", "PATH=/tmp", (char *)NULL };
    execle("/bin/ls", "ls", "-l", (char *)NULL, envp);
    return 0;
}

int execv_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    char *argv[] = { "ls", "-l", (char *)NULL };
    execv("/bin/ls", argv);
    return 0;
}

int execve_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    char *argv[] = { "ls", "-l", (char *)NULL };
    char *envp[] = { "USER=guest", "PATH=/tmp", (char *)NULL };
    execve("/bin/ls", argv, envp);
    return 0;
}

int execvp_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    char *argv[] = { "ls", "-l", (char *)NULL };
    execvp("ls", argv);
    return 0;
}

int execlp_example()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    execlp("ls", "ls", "-l", (char *)NULL);
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
具体来说，当 execl_example 调用 execl 成功时，当前进程的地址空间会被 /bin/ls 程序替换，execle_example 函数和 main 函数中的后续代码将不会被执行。

[root@ubuntu0006:~/cmake/hj] #../a.out
===== execl_example(15) =====
总用量 20
-rw-r--r-- 1 root root  778 12月 29  2023 en_US.po
drwxr-xr-x 4 root root 4096 12月 29  2023 locale
-rw-r--r-- 1 root root  653 12月 29  2023 msg.pot
-rwxr-xr-x 3 root root  576 12月 29  2023 test.sh
-rw-r--r-- 1 root root  816 12月 29  2023 zh_CN.po
*/