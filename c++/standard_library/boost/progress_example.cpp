/*******************************************************************************
* 文 件 名: progress_example.cpp
* 文件描述: 使用 Boost 的日期时间库和进度条功能
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.29
* 修改日期：2025.07.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

int main()
{
    boost::timer t;
    boost::progress_display pd(100);

    for (int i = 0; i < 100; ++i) {
        ++pd; // 更新进度条
    }

    boost::gregorian::date dt(2023, 10, 1);
    std::cout << "日期: " << boost::gregorian::to_iso_extended_string(dt) << std::endl;
    std::cout << "程序运行时间: " << t.elapsed() << " 秒" << std::endl;

    return 0;
}