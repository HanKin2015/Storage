/*******************************************************************************
* 文 件 名: popen_example4.cpp
* 文件描述: popen函数
* 备    注: 可以读取所有输出内容
* 作    者: HanKin
* 创建日期: 2025.05.21
* 修改日期：2025.05.21
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <memory>
#include <array>

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;

    // 使用 popen 执行命令并打开管道
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // 读取命令输出
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

int main()
{
    // 执行 shell 命令
    std::string command = "ls -l"; // 你可以替换为任何你想执行的命令
    std::string output = exec(command.c_str());

    // 输出命令的返回结果
    std::cout << "Command output:\n" << output << std::endl;

    return 0;
}

