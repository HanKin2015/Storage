/*******************************************************************************
* 文 件 名: sort_example.cpp
* 文件描述: std::less和std::greater
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.28
* 修改日期：2025.07.28
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdio>
#include <algorithm>

int main()
{
    std::vector<int> vec = {1, 2, 3};
    //sort(vec.begin(), vec.end(), std::greater<int>());
    sort(vec.begin(), vec.end(), std::less<int>()); // 默认是升序
    for (const auto& elem : vec) {
        std::cout << elem << std::endl;
    }
    
    // 自带排序的容器则是在初始化的时候指定排序函数，并且函数不需要小括号（默认都是升序额）
    std::set<int, std::greater<int>> s = {1, 2, 3};
    //sort(s.begin(), s.end());
    for (const auto& elem : s) {
        std::cout << elem << std::endl;
    }

    // 同理
    std::map<int, int, std::greater<int>> m = {{1, 5}, {2, 3}, {3, 4}};
    for (const auto& elem : m) {
        std::cout << elem.first << std::endl;
    }

    // map按值排序
    std::vector<std::pair<int, int>> v(m.begin(), m.end());
    sort(v.begin(), v.end(), [](const auto& x, const auto& y) {
        return x.second < y.second;
    });
    for (const auto& elem : v) {
        std::cout << elem.first << std::endl;
    }
    return 0;
}