/**
* 文 件 名: struct_address.cpp
* 文件描述: 获取结构体地址，获取成员地址，内容拷贝
* 作    者: HanKin
* 创建日期: 2022.12.13
* 修改日期：2022.12.13
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
//typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef struct _NODE {
    uint32_t next;
    uint32_t epchar;
#define EHCI_QH_EPS_FULL              0
#define EHCI_QH_EPS_LOW               1
#define EHCI_QH_EPS_HIGH              2
#define EHCI_QH_EPS_RESERVED          3
    uint32_t epcap;
#define QH_EPCAP_PORTNUM_MASK         0x3f800000
#define QH_EPCAP_PORTNUM_SH           23
    uint32_t current_qtd;
    uint32_t next_qtd;
    uint32_t altnext_qtd;
    uint32_t token;
    uint32_t bufptr[5];
} NODE;

#define NLPTR_GET(x)             ((x) & 0xffffffe0)

int main(int argc, char *argv[])
{
    printf("sizeof(long) %ld sizeof(long int) %ld sizeof(long long) %ld\n", sizeof(long), sizeof(long int), sizeof(long long));
    NODE q = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    printf("sizeof(NODE) %ld sizeof(q) %ld\n", sizeof(NODE), sizeof(q));
    
    printf("addr %p, token %d\n", &q, q.token);
    
    NODE qh;
    memset(&qh, 0, sizeof(qh)); 
    printf("qh.token %d\n", qh.token);
    // 一定需要强转成char类型，否则就会以NODE这个结构体为1个单位进行偏移，飘了
    memcpy((char *)&qh+4, (char *)&q+4, 44);
    printf("q.epchar %d q.epcap %d\n", q.epchar, q.epcap);
    printf("qh.epchar %d qh.epcap %d\n", qh.epchar, qh.epcap);
    printf("qh.token %d\n", qh.token);
    
    uint32_t next = *(uint32_t *)&q;
    printf("next = %d\n", next);

    uint64_t calc1 = ((11LL << 32) | 2);
    uint64_t calc2 = ((2LL << 32) | 11);    // 这个才是正确的，可能跟大小端有关吧
    uint64_t other = *(uint64_t *)&q;
    printf("other = %lld, calc1 = %lld, calc2 = %lld\n", other, calc1, calc2);
    
    void *addr = &q;
    memcpy(&qh, addr, sizeof(NODE));    // 虽然指针打印出来是一个十六进制值，但是肯定不能直接传一个十六进制值就当做地址
    //uint32_t addr = &qh;
    //memcpy(NLPTR_GET(addr)+4, NLPTR_GET(&q)+4, 44);
    printf("qh.next = %d\n", qh.next);
    return 0;
}
/*
sizeof(long) 8 sizeof(long int) 8 sizeof(long long) 8
sizeof(NODE) 48 sizeof(q) 48
addr 0x7fffe2217020, token 7
qh.token 0
q.epchar 2 q.epcap 3
qh.epchar 2 qh.epcap 3
qh.token 7
next = 11
other = 8589934603, calc1 = 47244640258, calc2 = 8589934603
qh.next = 11
*/
