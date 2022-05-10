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
 * date  : 2021.07.29
 * author: hejian
 *
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#include "handle_udev_info.h"
#include "cmdline.h"


/*
* todo: 参数配置解析
*/
int config_cmdline(int argc, char* argv[])
{
    cmdline::parser a;
    a.add<string>("log",  'l', "log path",  false, "");
    a.add<string>("data", 'd', "data path", false, "");

    a.parse_check(argc, argv);

    auto log_path  = a.get<string>("log");
    auto data_path = a.get<string>("data");

    return 0;
}

int main(int argc, char* argv[])
{
    clock_t start_time = clock();

    // todo: 参数配置解析
    //config_cmdline(argc, argv);

    // 处理数据
    handle_udev_main();

    clock_t spent_time = clock() - start_time;
    LOGI("exec spent time %lf s.\n", (double)spent_time / CLOCKS_PER_SEC);
    return 0;
}
