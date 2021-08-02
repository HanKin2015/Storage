/*
 * main.cpp
 * 程序入口
 *
 * 设计:
 * 1.日志文件设计
 * 2.使用多线程
 * 3.单元测试
 * 4.使用7x.exe和unzip库解压缩
 * 
 * 注意:
 * 1.日志中尽量少出现中文
 * 2.变量不要写死,使用输入参数动态使用
 * 3.日志级别尽量可以通过文件配置来配置显示级别
 * 
 * date  : 2021.07.29
 * author: hejian
 *
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#include "handle_udev_info.hpp"
#include "unit_test.hpp"

int main(int argc, char* argv[])
{
    clock_t start_time = clock();

    // 单元测试
    //unit_test(argc, argv);

    // 处理数据
    handle_udev_main();

    clock_t spent_time = clock() - start_time;
    LOGI("exec spent time %lf s.\n", (double)spent_time / CLOCKS_PER_SEC);
    return 0;
}
