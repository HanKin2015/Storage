/*******************************************************************************
* 文 件 名: libusb_tutorial.cpp
* 文件描述: libusb教程（待完善）
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且编译的时候需要增加-lusb-1.0参数
* 创建日期: 2023.07.04
* 修改日期: 2025.08.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <libusb-1.0/libusb.h>
#include <cstdio>
#include <iostream>

/**
* @brief  获取usb设备列表
* @note   
* @param  无
* @return 无
*/
void get_usb_device_list()
{
    
}

/**
* @brief  获取usb设备列表
* @note   
* @param  无
* @return 无
*/
void get_usb_device_handle()
{
    return;
}

/**
* @brief  libusb库信息
* @note   
* @param  无
* @return 无
*/
void libusb_info()
{
    // 获取版本
    const struct libusb_version *version = libusb_get_version();
    // libusb version = 1.0.27.11882  https://libusb.info
    printf("libusb version = %d.%d.%d.%d %s %s\n",
        version->major, version->minor, version->micro, version->nano, version->rc, version->describe);
    
    // 获取错误名称，即错误码变量名
    const char *error_name = libusb_error_name(LIBUSB_ERROR_OVERFLOW);
    // LIBUSB_ERROR_OVERFLOW error name = LIBUSB_ERROR_OVERFLOW
    printf("LIBUSB_ERROR_OVERFLOW error name = %s\n", error_name);
    
    // 转换成错误日志（支持不同语言）
    const char *strerror = libusb_strerror(LIBUSB_ERROR_OVERFLOW);
    // LIBUSB_ERROR_OVERFLOW strerror = Overflow
    printf("LIBUSB_ERROR_OVERFLOW strerror = %s\n", strerror);
    return;
}

int main(int argc, char *argv[])
{
    libusb_info();
    get_usb_device_list();
    get_usb_device_handle();
    return 0;
}