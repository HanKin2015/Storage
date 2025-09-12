/*******************************************************************************
* 文 件 名: fmt_example.cpp
* 文件描述: https://github.com/fmtlib/fmt
* 备    注: g++ format_example.cpp -std=c++20
* 作    者: HanKin
* 创建日期: 2025.09.12
* 修改日期：2025.09.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <fmt/base.h>
#include <fmt/chrono.h>
#include <vector>
#include <fmt/ranges.h>
#include <iostream>

int main()
{
    fmt::print("Hello, world!\n");

    std::string s = fmt::format("The answer is {}.", 42);
    // s == "The answer is 42."
    std::cout << s << std::endl;

    std::string ss = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
    // ss == "I'd rather be happy than right."
    std::cout << ss << std::endl;

    auto now = std::chrono::system_clock::now();
    fmt::print("Date and time: {}\n", now);
    fmt::print("Time: {:%H:%M}\n", now);

    std::vector<int> v = {1, 2, 3};
    fmt::print("{}\n", v);
    return 0;
}