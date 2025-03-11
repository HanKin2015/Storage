/**
* 文 件 名: vector_sort.cpp
* 文件描述: vector容器排序
* 作    者: HanKin
* 创建日期: 2025.03.08
* 修改日期：2025.03.08
*
* Copyright (c) 2025 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm> // 需要包含这个头文件以使用 std::sort
using namespace std;

struct Node {
    bool x;
    int y;

    // 构造函数
    Node(bool x_val, int y_val) : x(x_val), y(y_val) {}
};

void vector_is_empty()
{
    vector<Node> vec;
    std::sort(vec.begin()+1, vec.end());
    return;
}

int main(int argc, char *argv[])
{
    vector<Node> vec;
    vec.push_back(Node(false, 0));
    vec.push_back(Node(false, 9));
    vec.push_back(Node(true, 8));
    vec.push_back(Node(true, 10)); // 添加更多节点以测试排序

    // 降序排列
    /*错误演示
    std::sort(vec.begin()+1, vec.end(), [](const Node& a, const Node& b) {
        if (a.x > b.x) {
            return true;
        } else if (a.y > b.y) {
            return true;
        }
        return false;
    });
    */

    // 第一个元素不参与排序
    std::sort(vec.begin()+1, vec.end(), [](const Node& a, const Node& b) {
        if (a.x != b.x) {
            return a.x > b.x; // 先比较 x
        }
        return a.y > b.y; // 如果 x 相等，则比较 y
    });
    
    for (Node elem : vec) {
        printf("x = %d y = %d\n", elem.x, elem.y);
    }

    vector_is_empty();
    return 0;
}