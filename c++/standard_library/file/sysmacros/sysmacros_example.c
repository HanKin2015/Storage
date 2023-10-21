/*******************************************************************************
* 文 件 名: sysmacros_example.c
* 文件描述: 学习sysmacros.h头文件
* 作    者: HanKin
* 创建日期: 2023.10.19
* 修改日期：2023.10.19
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

int main() {
    struct stat file_stat;
    dev_t device_number;

    // 获取文件的状态信息
    if (stat("Makefile", &file_stat) == -1) {
        perror("stat");
        return 1;
    }

    // 获取文件的设备号
    device_number = file_stat.st_dev;

    // 获取设备号的主设备号和次设备号
    int major_number = major(device_number);
    int minor_number = minor(device_number);

    // 打印设备号及其主次设备号
    printf("设备号: %lu\n", device_number);
    printf("主设备号: %u\n", major_number);
    printf("次设备号: %u\n", minor_number);

    return 0;
}
