/*******************************************************************************
* 文 件 名: perror_example.c
* 文件描述: 自带换行符，并且会给出上一次运行结果
* 作    者: HanKin
* 备    注: 
* 创建日期: 2023.09.19
* 修改日期：2025.09.19
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    perror("are you ok");
    
    int x = 0;
    if (x != 1) {
        perror("x is invalid");
    }
    
    int fd = open("x.x", O_RDWR);
    if (fd == -1) {
        perror("open failed");
    }
    return 0;
}
/*
root@hankin:~/opencv# ./a.out 
are you ok: Success
x is invalid: Success
open failed: No such file or directory
*/