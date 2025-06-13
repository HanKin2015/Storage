/*******************************************************************************
* 文 件 名: init_struct2.cpp
* 文件描述: 结构体中含有指针是否能初始化为nullptr
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.06.07
* 修改日期：2025.06.07
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>

typedef struct ctrl_callbacks {
    void *priv;
    void (*on_device_info_change)(void *priv, int event_type, const char *info, int length);
} ctrl_callbacks;

int main()
{
    ctrl_callbacks callbacks{};
    if (callbacks.on_device_info_change) {
        printf("on_device_info_change is not null\n");
    } else {
        printf("on_device_info_change is null\n");
    }
    if (callbacks.priv) {
        printf("priv is not null\n");
    } else {
        printf("priv is null\n");
    }
    return 0;
}