/*******************************************************************************
* 文 件 名: basic_usage.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <map>

/**
 * @struct Point
 * @brief 一个简单的用户定义聚合类型。
 */
struct Point {
    int x;
    int y;
};

int main()
{
    /**
     * @brief 初始化内置类型。
     * @description 使用花括号为int和double变量提供初始值。
     */
    int a{10};
    double b{3.14};
    std::cout << "int a: " << a << ", double b: " << b << std::endl;

    /**
     * @brief 初始化普通数组。
     * @description 语法与C风格数组初始化类似，但更统一。
     */
    int arr[3]{1, 2, 3};
    std::cout << "arr: " << arr[0] << ", " << arr[1] << ", " << arr[2] << std::endl;

    /**
     * @brief 初始化STL容器std::vector。
     * @description 这是统一初始化最受欢迎的应用之一，代码极其简洁。
     */
    std::vector<std::string> cities{"New York", "London", "Tokyo"};
    std::cout << "Cities: ";
    for(const auto& city : cities) {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    /**
     * @brief 初始化STL容器std::map。
     * @description 对于键值对容器，每一对元素也用花括号包围。
     */
    std::map<std::string, int> city_population{
        {"Beijing", 21540000},
        {"Shanghai", 24280000}
    };
    std::cout << "Population of Beijing: " << city_population["Beijing"] << std::endl;

    /**
     * @brief 初始化用户定义的聚合类型。
     * @description 直接在花括号内按成员顺序提供值。
     */
    Point p{100, 200};
    std::cout << "Point p: (" << p.x << ", " << p.y << ")" << std::endl;

    /**
     * @brief 默认初始化，创建一个空vector和一个零值Point。
     * @description 空花括号{}表示进行默认初始化。
     */
    std::vector<int> empty_vec{};
    Point origin{};
    std::cout << "Empty vector size: " << empty_vec.size() << std::endl;
    std::cout << "Point origin: (" << origin.x << ", " << origin.y << ")" << std::endl;

    return 0;
}