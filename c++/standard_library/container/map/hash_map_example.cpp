/*******************************************************************************
* 文 件 名: hash_map_example.cpp
* 文件描述: 在 C++ 标准正式引入 std::unordered_map 之前，一些编译器（如 GCC、MSVC）曾提供过非标准的 hash_map 实现（通常位于 <hash_map> 头文件，属于编译器扩展）
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.27
* 修改日期：2025.07.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <hash_map>

int main()
{
    __gnu_cxx::hash_map<int, int> m;
    m[4] = 100;
    std::cout << m[4] << std::endl;

    // 查找元素
    auto it = m.find(4);
    if (it != m.end()) {
        std::cout << "elem: " << it->second << std::endl; // 输出 elem: 100
    }
    return 0;
}
