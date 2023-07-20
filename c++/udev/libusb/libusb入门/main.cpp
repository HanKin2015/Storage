/**
* 文 件 名: main.cpp
* 文件描述: libusb入门
* 作    者: HanKin
* 创建日期: 2023.07.20
* 修改日期：2023.07.20
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include "libusb_introduction.h"
using namespace std;

int main(int argc, char *argv[])
{
    LibusbIntroduction obj;
    obj.set_vid_pid(0x090c, 0x2000);
    obj.init();
    return 0;
}
