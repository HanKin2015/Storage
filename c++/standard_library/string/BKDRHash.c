/**
* 文 件 名: BKDRHash.c
* 文件描述: 将字符串中每个字符的ASCII值乘以一个常数因子，然后将所有乘积相加，最后取结果的模
* 作    者: HanKin
* 备    注: BKDRHash是一种常用的字符串哈希函数，由Brian Kernighan和Dennis Ritchie于1977年提出
* 创建日期: 2025.03.06
* 修改日期：2025.03.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*/
#include <stdio.h>

unsigned int BKDRHash(const char* str) {
    unsigned int seed = 131; // 常用的种子值包括31、131、1313、13131等或更大的质数
    unsigned int hash = 0;
    while (*str) {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF); // 取低31位以防止溢出
}

int main()
{
    // 由SetupDiGetDeviceInterfaceDetailA函数获取的DevicePath
    const char *str = "\\\\?\\USB#VID_2109&PID_2813#5&275C60B&0&4#{F18A0E88-C30C-11D0-8815-00A0C906BED8}";
    printf("%d\n", BKDRHash(str));  // 1556444124
    return 0;
}