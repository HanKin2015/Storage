/**
* 文 件 名: libusb_introduction.cpp
* 文件描述: libusb入门
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数
* 创建日期: 2023.07.04
* 修改日期：2023.07.04
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // 获取版本
    const struct libusb_version *version = libusb_get_version();
    printf("libusb version = %d.%d.%d.%d %s %s\n",
        version->major, version->minor, version->micro, version->nano, version->rc, version->describe);
    
    // 获取错误名称，即错误码变量名
    const char *error_name = libusb_error_name(LIBUSB_ERROR_OVERFLOW);
    printf("LIBUSB_ERROR_OVERFLOW error name = %s\n", error_name);
    
    // 转换成错误日志（支持不同语言）
    const char *strerror = libusb_strerror(LIBUSB_ERROR_OVERFLOW);
    printf("LIBUSB_ERROR_OVERFLOW strerror = %s\n", strerror);
    return 0;
}