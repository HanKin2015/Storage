/*******************************************************************************
* 文 件 名: vector_example.cpp
* 文件描述: 都是深拷贝
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.21
* 修改日期：2025.03.21
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

class Node {
public:
    Node() {}
    ~Node() {}

    std::vector<int> getX() { return x; }
    void setX(const std::vector<int>& y) { x = y; } // 直接赋值

private:
    std::vector<int> x;
};

int main()
{
    std::vector<int> original = {1, 4, 3, 2, 5};
    Node data;
    data.setX(original);
    std::vector<int> tmp = data.getX();
    
    for (auto& elem : tmp) { // 使用引用
        elem = 23213;
    }
    for (const auto& elem : tmp) {
        printf("%d ", elem);
    }
    printf("tmp\n");

    std::vector<int> hj(tmp);
    for (auto& elem : hj) { // 使用引用
        elem = 1; // 这不会影响原始的 tmp
    }
    for (const auto& elem : hj) {
        printf("%d ", elem);
    }
    printf("hj\n");

    std::sort(tmp.begin(), tmp.end(), [](const int& a, const int& b) {
        return a < b;
    });
    for (const auto& elem : tmp) {
        printf("%d ", elem);
    }
    printf("tmp\n");
    
    for (const auto& elem : original) {
        printf("%d ", elem);
    }
    printf("original\n");
    return 0;
}
/*
[root@ubuntu0006:/media/vdb/TransferStation] #./a.out
23213 23213 23213 23213 23213 tmp
1 1 1 1 1 hj
23213 23213 23213 23213 23213 tmp
1 4 3 2 5 original
*/