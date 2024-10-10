/*******************************************************************************
* 文 件 名: sequential_list_example.cpp
* 文件描述: 顺序表
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.09.29
* 修改日期：2024.09.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <cassert>

#pragma pack(push)
#pragma pack(1)

struct uvc_streaming_control {
    uint16_t bmHint;
    uint8_t  bFormatIndex;
    uint8_t  bFrameIndex;
    uint32_t dwFrameInterval;
    uint16_t wKeyFrameRate;
    uint16_t wPFrameRate;
    uint16_t wCompQuality;
    uint16_t wCompWindowSize;
    uint16_t wDelay;
    uint32_t dwMaxVideoFrameSize;
    uint32_t dwMaxPayloadTransferSize;
    uint32_t dwClockFrequency; // UVC 1.1 and later
    uint8_t  bmFramingInfo;    // UVC 1.5 and later
    uint8_t  bPreferedVersion; // UVC 1.5 and later
    uint8_t  bMinVersion;      // UVC 1.5 and later
    uint8_t  bMaxVersion;      // UVC 1.5 and later
};

#define DATA_LEN 26
int main()
{
    uint8_t data[DATA_LEN] = { 0 };
    for (int i = 0; i < DATA_LEN; i++) {
        data[i] = i;
    }
    for (int i = 0; i < DATA_LEN; i++) {
        printf("0x%02x\n", data[i]);
    }
    
    struct uvc_streaming_control *probe_rsp = (struct uvc_streaming_control *)data;
    if (probe_rsp == nullptr) {
        std::cerr << "dynamic_cast failed" << std::endl;
        return -1;
    }
    printf("sizeof(struct uvc_streaming_control): %ld\n", sizeof(struct uvc_streaming_control));
    
    struct uvc_streaming_control *p = (struct uvc_streaming_control *)calloc(1, sizeof(struct uvc_streaming_control));
    if (p == nullptr) {
        std::cerr << "malloc failed" << std::endl;
        return -1;
    }
    memset(p, 0, sizeof(struct uvc_streaming_control));

    // 如果通过这种方式直接复制的话，会访问不存在的内存地址
    *p = *probe_rsp;
    
    // 对于字符串操作，通常使用 strncpy，而对于二进制数据或需要精确控制字节数的操作，使用 memcpy
    //strncpy(p, prober_rsp, DATA_LEN);
    //memcpy(p, probe_rsp, DATA_LEN);
    
    printf("%d %d\n", p->bMaxVersion, probe_rsp->bMaxVersion);  // 分别输出最后一个成员变量
    
    free(p);
    p = NULL;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
0x00
0x01
0x02
0x03
0x04
0x05
0x06
0x07
0x08
0x09
0x0a
0x0b
0x0c
0x0d
0x0e
0x0f
0x10
0x11
0x12
0x13
0x14
0x15
0x16
0x17
0x18
0x19
sizeof(struct uvc_streaming_control): 34
144 144
*/