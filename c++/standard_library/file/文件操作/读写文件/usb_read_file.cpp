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

int main()
{
   FILE *fp = fopen("/other/custom", "r");
   int vid = 0, pid = 0;
    while (fscanf(fp, "%x:%x\n", &vid, &pid) == 2) {
        printf("custom udev %04x:%04x\n", vid, pid);
        if (desc.idVendor == vid && desc.idProduct == pid) {
            return true;
       }
    }
   fclose(fp);
   fp = NULL;
   return 0;
}