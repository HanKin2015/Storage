/**
* 文 件 名: usb_read_file.cpp
* 文件描述: 读取文件判断
* 作    者: HanKin
* 创建日期: 2023.05.18
* 修改日期：2023.05.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>

#define linfo printf
#define bool int
#define true 1
#define false 0

static void test1()
{
    FILE *fp = fopen("/sf/data/local/bytes_per_transfer", "r");
    if (fp != NULL) {
        int bytes_per_transfer = 0;
        while (fscanf(fp, "%d\n", &bytes_per_transfer) == 1) {
            linfo("custom bytes_per_transfer %d\n", bytes_per_transfer);
        }
        fclose(fp);
        fp = NULL;
        linfo("set udev bytes_per_transfer is %d\n", bytes_per_transfer);
    } else {
        linfo("open file failed\n");
    }
    return;
}

static bool test2()
{
    FILE *fp = fopen("/other/custom", "r");
    if (fp) {
        int vid = 0, pid = 0;
        while (fscanf(fp, "%x:%x\n", &vid, &pid) == 2) {
            printf("custom udev %04x:%04x\n", vid, pid);
            if (0x1234 == vid && 0x4321 == pid) {
                printf("/other/custom file found 1234:4321 device\n");
                return true;
           }
        }
        fclose(fp);
        fp = NULL;
    } else {
        printf("open file[/other/custom] failed\n");
        return false;
    }
    printf("/other/custom file not found 1234:4321 device\n");
    return false;
}

int main()
{
    test2();
    return 0;
}