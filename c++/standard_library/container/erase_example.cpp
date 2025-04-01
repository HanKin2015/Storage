/*******************************************************************************
* 文 件 名: erase_example.cpp
* 文件描述: 删除不存在的元素会有异常吗
* 备    注: 答案是均无异常，erase方法会安全地处理这种情况
* 作    者: HanKin
* 创建日期: 2025.03.27
* 修改日期：2025.03.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdio>
#include <algorithm>    // 使用remove函数一定需要这个头文件

int main()
{
    std::vector<int> vector_ = {1, 2, 3};
    std::set<int> set_ = {1, 2, 3};
    std::map<int, int> map_ = {{1, 1}, {2, 1}, {3, 1}};

    vector_.erase(remove_if(vector_.begin(), vector_.end(), [](int elem){ if (elem == 1) return true; return false; }), vector_.end());
    vector_.erase(remove_if(vector_.begin(), vector_.end(), [](int elem){ if (elem == 11) return true; return false; }), vector_.end());
    std::remove(vector_.begin(), vector_.end(), 1); // 删除1后剩余元素前移2 3 3
    std::remove(vector_.begin(), vector_.end(), 11);
    set_.erase(1);
    set_.erase(11);
    map_.erase(1);
    map_.erase(11);

    for (auto &elem : vector_) {
        printf("vector_: %d\n", elem);
    }
    for (auto &elem : set_) {
        printf("set_: %d\n", elem);
    }
    for (auto &elem : map_) {
        printf("map_: %d %d\n", elem.first, elem.second);
    }
    return 0;
}
/*
[root@ubuntu0006:~] #g++ erase_example.cpp --std=c++11
[root@ubuntu0006:~] #./a.out
vector_: 2
vector_: 3
set_: 2
set_: 3
map_: 2 1
map_: 3 1
*/