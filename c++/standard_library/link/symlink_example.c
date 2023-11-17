/*******************************************************************************
* 文 件 名: symlink_example.c
* 文件描述: 建立文件符号连接
* 备    注: int symlink(const char * oldpath, const char * newpath);
* 作    者: HanKin
* 创建日期: 2023.11.16
* 修改日期：2023.11.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    int ret;

    ret = symlink("/etc/passwd", "./pass1");
    if (ret != 0) {
        printf("ret:%d (%s)\n", ret, strerror(errno));
    }

    symlink("/etc/passwd", "pass2");
    if (ret != 0) {
        printf("ret:%d (%s)\n", ret, strerror(errno));
    }

    const int buf_size = 100;
    char buf[buf_size] = {0};
    ret = readlink("./pass1", buf, buf_size);
    if (ret == -1) {
        printf("ret:%d (%s)\n", ret, strerror(errno));
    } else {
        printf("pass1 -> %s\n", buf);
    }
    return 0;
}

