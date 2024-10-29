/*******************************************************************************
* 文 件 名: sequential_list_example.cpp
* 文件描述: 顺序表
* 备    注: g++ sequential_list_example.cpp --std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.29
* 修改日期：2024.09.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> seq_list = {1, 2, 3, 4, 5};
    // 访问元素
    std::cout << "Element at index 2: " << seq_list[2] << std::endl;
    // 插入元素
    seq_list.insert(seq_list.begin() + 2, 10);
    for_each(seq_list.cbegin(), seq_list.cend(), [](int elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;

    // 删除元素
    seq_list.erase(seq_list.begin() + 3);
    for(auto elem : seq_list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
Element at index 2: 3
1 2 10 3 4 5
1 2 10 4 5
*/