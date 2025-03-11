/**
* 文 件 名: vector_cbegin_cend.cpp
* 文件描述: vector容器中的cbegin函数和cend函数(常量迭代器（const_iterator）,允许修改容器中的元素，只能用于读取)
* 备    注: g++ vector_cbegin_cend.cpp --std=c++11
* 作    者: HanKin
* 创建日期: 2025.03.10
* 修改日期：2025.03.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用 begin()
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        *it += 1; // 可以修改元素
    }

    // 使用 cbegin()
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        //*it += 1; // error: assignment of read-only location 
                    // ‘it.__gnu_cxx::__normal_iterator<_Iterator, _Container>::operator*<const int*, std::vector<int> >()’
        std::cout << *it << " "; // 只能读取元素2 3 4 5 6
    }
    return 0;
}