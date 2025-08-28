/*******************************************************************************
* 文 件 名: filesystem_example.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.25
* 修改日期：2025.08.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem; // 简化命名空间

int main()
{
    fs::path dirPath = "/root/opencv"; // 路径对象，自动处理跨平台分隔符（/或\）
    
    if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
        // 遍历目录
        for (const auto& entry : fs::directory_iterator(dirPath)) {
            if (fs::is_regular_file(entry)) { // 判断是否为普通文件
                std::cout << "File: " << entry.path().filename() << "\n";
            } else if (fs::is_directory(entry)) {
                std::cout << "Dir: " << entry.path().filename() << "\n";
            }
        }
    }
    return 0;
}