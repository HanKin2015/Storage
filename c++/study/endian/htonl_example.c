/*******************************************************************************
* 文 件 名: htonl_example.c
* 文件描述: 网络和主机字节序之间转换
* 备    注: 两次调用函数后又会变回原样，但不推荐这样使用
* 作    者: HanKin
* 创建日期: 2023.11.16
* 修改日期：2023.11.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    union {
        int i;
        char c[sizeof(int)];
    } u;

    u.i = 1;

    if (u.c[0] == 1) {
        printf("小端字节序\n");
    } else {
        printf("大端字节序\n");
    }
    
    unsigned long a = 0x12345678;
    unsigned char *p = (unsigned char *)(&a);

    printf("主机字节序:%0x    %0x   %0x   %0x\n",  p[0], p[1], p[2], p[3]);

    unsigned long b = htonl(a);  //将主机字节序转化成了网络字节序
    p = (unsigned char *)(&b);
    printf("网络字节序:%0x    %0x   %0x   %0x (大端字节序)\n",  p[0], p[1], p[2], p[3]);

    unsigned long c = htole32(a);
    p = (unsigned char *)(&c);
    printf("小端字节序:%0x    %0x   %0x   %0x\n",  p[0], p[1], p[2], p[3]);
    
    unsigned long d = htonl(b);
    p = (unsigned char *)(&d);
    printf("把网络字节序再次调用htonl函数:%0x    %0x   %0x   %0x\n",  p[0], p[1], p[2], p[3]);
    
    unsigned long e = ntohl(b);
    p = (unsigned char *)(&e);
    printf("ntohl函数:%0x    %0x   %0x   %0x\n",  p[0], p[1], p[2], p[3]);
    return 0;
}

