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

struct uvc_streaming_control {
    int some_field;
    // 其他字段...
};

struct ProbeResponse {
    uvc_streaming_control* rsp_;
};

int main()
{
    uvc_streaming_control* p = new uvc_streaming_control;
    ProbeResponse* probe_rsp = new ProbeResponse;
    probe_rsp->rsp_ = new uvc_streaming_control;

    // 正确的赋值方式
    *p = *(probe_rsp->rsp_);

    // 清理内存
    delete p;
    delete probe_rsp->rsp_;
    delete probe_rsp;

    return 0;
}
