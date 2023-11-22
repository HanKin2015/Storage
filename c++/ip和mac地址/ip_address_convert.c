/*******************************************************************************
* 文 件 名: ip_address_convert.c
* 文件描述: ip地址转换
* 备    注: https://blog.csdn.net/qq_39852676/article/details/129542798
            https://baike.baidu.com/item/inet_pton/9555884?fr=ge_ala
* 作    者: HanKin
* 创建日期: 2023.11.21
* 修改日期：2023.11.21
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define dump_mem(str, mem, len){ \
    if ((mem) && (len)) { \
        int i; \
        unsigned char *p = (unsigned char*)mem; \
        int c; \
        printf("[%s, %s@%d addr = %p len = 0x%x]: %s\n", __FILE__, __func__, __LINE__, (p), (len), str); \
        for (i = 0; i < (len); i++) {   \
            if (i % 16 == 0 && i != 0) { \
                printf("\n"); \
            }\
            c = p[i]; \
            printf("0x%02x ", c); \
        } \
        printf("\n"); \
    }\
}

int main(int argc, char *argv[])
{
    int ip_addr;
    ip_addr = inet_addr("192.168.2.125");       // 设置ip点分十进制地址的地址
    printf("0x%02x  %d\n", ip_addr, ip_addr);   // 打印转换后的网络字节序  
    dump_mem("sss", &ip_addr, sizeof(int));
    
    struct in_addr inet_ip_addr;
    // 返回非0表示cp主机有地有效，返回0表示主机地址无效
    int ret = inet_aton("192.168.2.125", &inet_ip_addr);
    printf("%d, ret = %d\n", inet_ip_addr.s_addr, ret);
    
    struct in_addr network;
    network.s_addr = 2097326272;    // 为s_addr赋值--网络字节序
    printf("IP : %s\n", inet_ntoa(network));
    
    // AF_INET（ipv4）也可以是AF_INET6（ipv6）
    ret = inet_pton(AF_INET, "192.168.2.125", (void *)&inet_ip_addr);
    printf("%d, ret = %d\n", inet_ip_addr.s_addr, ret);
    
    struct in_addr network2;
    network2.s_addr = 2097326272;
    char IPdotdec[20] = { 0 };
    printf("IP : %s\n", inet_ntop(AF_INET, (void *)&network2, IPdotdec, 20));
    printf("IPdotdec: %s\n", IPdotdec);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
0x7d02a8c0  2097326272
[l.c, main@38 addr = 0x7ffc4bdfad78 len = 0x4]: sss
0xc0 0xa8 0x02 0x7d
2097326272, ret = 1
IP : 192.168.2.125
2097326272, ret = 1
IP : 192.168.2.125
IPdotdec: 192.168.2.125
*/
