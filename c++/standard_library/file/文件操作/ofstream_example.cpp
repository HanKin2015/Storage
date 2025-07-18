/*******************************************************************************
* 文 件 名: ofstream_example.cpp
* 文件描述: 写文件
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.18
* 修改日期：2025.07.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <fstream>

int main()
{
    // 创建并打开文件（自动调用 open()）
    std::ofstream file("example.txt");  // 默认模式：ios::out | ios::trunc
    
    if (file.is_open()) {  // 检查文件是否成功打开
        file << "Hello, World!" << std::endl;  // 写入文本
        file << 42 << std::endl;               // 写入数字
        file.close();  // 可选：自动析构时关闭
    }
    return 0;
}