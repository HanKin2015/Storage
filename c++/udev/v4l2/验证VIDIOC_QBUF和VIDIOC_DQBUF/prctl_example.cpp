/**
* 文 件 名: prctl_example.cpp
* 文件描述: prctl函数学习
* 备    注: g++ prctl_example.cpp -lpthread
* 作    者: HanKin
* 创建日期: 2023.02.10
* 修改日期：2023.02.10
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <unistd.h>

void *tmain(void *arg)
{
    char name[32] = { 0 };
    prctl(PR_SET_NAME, (unsigned long)"wangzherongyao");
    prctl(PR_GET_NAME, (unsigned long)name);
    printf("%s\n", name);
    while (1);
    sleep(1);
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, tmain, NULL);
    pthread_join(tid, NULL);
    return 0;
}
/*
一个窗口运行：
[root@ubuntu0006:/media/hankin/vdb] #g++ hj.cpp -lpthread
[root@ubuntu0006:/media/hankin/vdb] #./a.out
wangzherongyao
^C

另外一个窗口查看进程：
[root@ubuntu0006:~] #ps aux | grep a.out
root      1717  0.0  0.0  17088   964 pts/7    S+   15:40   0:00 grep --color=auto a.out
root     23416 99.7  0.0  80248   868 pts/4    Sl+  15:39   1:35 ./a.out
[root@ubuntu0006:~] #cd /proc/23416/task/
[root@ubuntu0006:/proc/23416/task] #ls
23416  23417
[root@ubuntu0006:/proc/23416/task] #cd 23417
[root@ubuntu0006:/proc/23416/task/23417] #cat cmdline
./a.out[root@ubuntu0006:/proc/23416/task/23417] #ps -L -p 23416
  PID   LWP TTY          TIME CMD
23416 23416 pts/4    00:00:00 a.out
23416 23417 pts/4    00:03:09 wangzherongyao
*/