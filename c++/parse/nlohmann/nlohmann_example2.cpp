/*******************************************************************************
* 文 件 名: nlohmann_example2.cpp
* 文件描述: nlohmann::json的简单应用
* 备    注: 读写文件内容转换成json
* 作    者: HanKin
* 创建日期: 2025.06.04
* 修改日期：2025.06.04
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    // 创建 JSON 对象
    json j;
    j["default:debian"] = {
        {"starting_automap", 1},
        {"running_automap", 1}
    };
    j["default:linux"] = {
        {"starting_automap", 1},
        {"running_automap", 1}
    };

    // 将 JSON 写入文件
    std::ofstream outFile("config.json");
    if (outFile.is_open()) {
        outFile << j.dump(4); // 使用 4 个空格缩进格式化输出
        outFile.close();
        std::cout << "JSON 写入文件成功！" << std::endl;
    } else {
        std::cerr << "无法打开文件进行写入！" << std::endl;
    }

    // 从文件读取 JSON
    std::ifstream inFile("config.json");
    if (inFile.is_open()) {
        json jRead;
        inFile >> jRead; // 读取 JSON 数据
        inFile.close();

        // 输出读取的 JSON
        std::cout << "读取的 JSON 内容：" << std::endl;
        std::cout << jRead.dump(4) << std::endl; // 使用 4 个空格缩进格式化输出
    } else {
        std::cerr << "无法打开文件进行读取！" << std::endl;
    }

    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
JSON 写入文件成功！
读取的 JSON 内容：
{
    "default:debian": {
        "running_automap": 1,
        "starting_automap": 1
    },
    "default:linux": {
        "running_automap": 1,
        "starting_automap": 1
    }
}
[root@ubuntu0006:~] #cat config.json
{
    "default:debian": {
        "running_automap": 1,
        "starting_automap": 1
    },
    "default:linux": {
        "running_automap": 1,
        "starting_automap": 1
    }
}[root@ubuntu0006:~] #
*/