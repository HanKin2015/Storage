/**
* 文 件 名: htole32_example.c
* 文件描述: htole32函数学习
* 备    注: lscpu命令也可以查看大小端
* 作    者: HanKin
* 创建日期: 2023.08.18
* 修改日期：2023.08.21
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <arpa/inet.h>

int checkCPU()
{
    union w {
        int  a;
        char b;
    }c;

    c.a = 1;
    return (c.b == 1);
}

int main()
{
    printf("This CPU is %s endian\n", checkCPU() ? "little" : "big");
    
    unsigned long a = 0x12345678;
    unsigned char *p = (unsigned char *)(&a);

    printf("主机字节序:%0x    %0x   %0x   %0x\n",  p[0], p[1], p[2], p[3]);

    unsigned long b = htonl(a);  //将主机字节序转化成了网络字节序
    p = (unsigned char *)(&b);
    printf("网络字节序:%0x    %0x   %0x   %0x (大端字节序)\n",  p[0], p[1], p[2], p[3]);

    unsigned long c = htole32(a);
    p = (unsigned char *)(&c);
    printf("小端字节序:%0x    %0x   %0x   %0x\n",  p[0], p[1], p[2], p[3]);
    return 0;
}
/*
This CPU is little endian
主机字节序:78    56   34   12
网络字节序:12    34   56   78 (大端字节序)
小端字节序:78    56   34   12
*/