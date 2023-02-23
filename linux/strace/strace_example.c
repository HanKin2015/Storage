/**
* 文 件 名: strace_example.c
* 文件描述: 如何使用strace对程序进行跟踪，如何查看相应的输出
* 作    者: HanKin
* 创建日期: 2023.02.23
* 修改日期：2023.02.23
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd = open("/tmp/foo", O_RDONLY );

    int i = -1;
    if (fd < 0) {
        i = 5;
    } else {
        i = 2;
    }
    return i;
}