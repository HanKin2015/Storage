/*******************************************************************************
* 文 件 名: constructor.cpp
* 文件描述: 构造函数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.27
* 修改日期：2025.07.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <memory>

// RAII的基本示例：文件管理
class FileManager {
private:
    std::ofstream file;
    std::string filename;

public:
    // 构造时获取资源
    FileManager(const std::string& fname) : filename(fname) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("无法打开文件: " + filename);
        }
        std::cout << "✅ 文件 " << filename << " 已打开\n";
    }

    // 析构时自动释放资源
    ~FileManager() {
        if (file.is_open()) {
            file.close();
            std::cout << "✅ 文件 " << filename << " 已关闭\n";
        }
    }

    // 删除拷贝构造和赋值（确保唯一所有权）
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    // 提供移动语义
    FileManager(FileManager&& other) noexcept
        : file(std::move(other.file)), filename(std::move(other.filename)) {
        std::cout << "📦 文件管理器已移动\n";
    }

    void write(const std::string& content) {
        if (file.is_open()) {
            file << content << std::endl;
        }
    }
};

// 使用示例
int main()
{
    try {
        FileManager fm("output.txt");
        fm.write("Hello, RAII!");
        fm.write("资源管理变得如此简单");
        // 函数结束时，FileManager的析构函数自动调用
        // 文件自动关闭，无需手动管理
    } catch (const std::exception& e) {
        std::cout << "❌ 错误: " << e.what() << std::endl;
    }
    return 0;
}