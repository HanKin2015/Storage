/**
* 文 件 名: getuid_example.c
* 文件描述: 学习getuid函数
* 作    者: HanKin
* 备    注: getuid函数是一个系统调用，用于获取当前进程的用户ID。在Linux中，每个用户都有一个唯一的UID（User Identifier），用于标识用户的身份。getuid函数的作用就是返回当前进程的UID，以便程序进行相应的权限控制。
* 创建日期: 2023.11.15
* 修改日期：2023.11.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>

int main (void) 
{ 
    uid_t uid = getuid(); // 获取当前进程UID
    if(uid == -1) {
        printf("getuid fled, errno=%d\n", errno);
        return -1;
    }
    printf("Current UID is %d\n", uid);
    
    struct passwd *passwd = getpwuid(uid); 
    printf("Username:%s\n", passwd->pw_name); 
    printf("Password:%s\n", passwd->pw_passwd); 
    printf("uid:%d\n", passwd->pw_uid); 
    printf("gid:%d\n", passwd->pw_gid); 
    printf("shell:%s\n", passwd->pw_shell); 
    printf("dir:%s\n", passwd->pw_dir); 
    return 0; 
}
/*
[root@ubuntu0006:~/cmake] #su hejian
hejian@ubuntu0006:/root/cmake$ ./a.out
Current UID is 1001
Username:hejian
Password:x
uid:1001
gid:1001
shell:
dir:/home/hejian
hejian@ubuntu0006:/root/cmake$ ls /run/systemd/users/
0  1001  108
*/