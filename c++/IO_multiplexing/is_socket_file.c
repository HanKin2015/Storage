/**
 * 文 件 名: is_socket_file.c
 * 文件描述: 判断文件是否是一个类型为 socket 的文件
 * 作    者: HanKin
 * 创建日期: 2021.09.07
 * 修改日期：2021.09.07
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

/*
在normal.c文件运行中会产生一个进程id

/proc/22424/fd/3 是一个类型为 socket 的文件。（准确来说，它是一个符号链接，链接到一个类型为 socket 的文件。）
*/
int main() 
{
    struct stat s;
    stat("/proc/22424/fd/3", &s);
    if (S_ISSOCK(s.st_mode)) {
        printf("is socket\n");
    } else {
        printf("is not socket\n");
    }
    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
is socket
*/