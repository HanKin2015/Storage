/*******************************************************************************
* 文 件 名: json_is_null.cpp
* 文件描述: 判空
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.06.06
* 修改日期：2025.06.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <nlohmann/json.hpp>

int main()
{
    // 创建一个空的 JSON 对象
    nlohmann::json empty_json_object = nlohmann::json::object();

    // 判空
    if (empty_json_object.empty()) {
        std::cout << "The JSON object is empty." << std::endl;
    } else {
        std::cout << "The JSON object is not empty." << std::endl;
    }

    // 也可以使用 size() 方法
    if (empty_json_object.size() == 0) {
        std::cout << "The JSON object has size 0." << std::endl;
    }

    if (empty_json_object.is_null()) {
        std::cout << "The JSON object is null." << std::endl;
    } else {
        std::cout << "The JSON object is not null." << std::endl;
    }

    nlohmann::json null_json_object1;
    if (null_json_object1.is_null()) {
        std::cout << "The JSON object is null." << std::endl;
    } else {
        std::cout << "The JSON object is not null." << std::endl;
    }

    nlohmann::json null_json_object2;
    if (null_json_object2.is_null()) {
        std::cout << "The JSON object is null." << std::endl;
    } else {
        std::cout << "The JSON object is not null." << std::endl;
    }
    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
The JSON object is empty.
The JSON object has size 0.
The JSON object is not null.
The JSON object is null.
The JSON object is null.
*/