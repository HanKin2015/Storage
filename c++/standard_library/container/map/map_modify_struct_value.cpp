/*******************************************************************************
* 文 件 名: map_modify_struct_value.cpp
* 文件描述: 修改map容器内部结构体变量值
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.19
* 修改日期：2025.03.19
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <cstdio>
#include <iostream>
#include <map>

// 在使用 Node 时没有提供参数，编译器会尝试调用默认构造函数，但由于我们定义了一个带参数的构造函数，默认构造函数就不再自动生成。
// 因此如果定义了一个带参数的构造函数，那么一定得需要定义默认构造函数。
struct Node {
    int x;
    int y;
    Node(int _x, int _y): x(_x), y(_y) {}

    // 默认构造函数
    Node() : x(0), y(0) {} // 初始化 x 和 y 为 0
};

int main()
{
    std::map<int, Node> mymap;
    Node a(1, 2);
    Node b(3, 4);
    mymap[1] = a;
    mymap[2] = b;

    Node &m = mymap[2];
    m.x = 100;
    printf("%d %d\n", mymap[2].x, mymap[2].y);  // 100 4

    Node n = mymap[1];
    n.x = 100;
    printf("%d %d\n", mymap[1].x, mymap[1].y);  // 1 2
    return 0;
}