/*
 * main.cpp
 * 程序入口
 *
 * 1.日志文件设计
 * 2.使用多线程
 * 3.单元测试
 * 4.使用7x.exe和unzip库解压缩
 * 
 * date  : 2021.07.29
 * author: hejian
 *
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#include "handle_udevice_info.hpp"
#include "unit_test.hpp"

int main(int argc, char* argv[])
{
    clock_t start_time = clock();

    // 单元测试
    //unit_test(argc, argv);

    // 处理数据
    handle_udev_main();

    clock_t spent_time = clock() - start_time;
    printf("exec time is %lf s.\n", (double)spent_time / CLOCKS_PER_SEC);
    return 0;
}
