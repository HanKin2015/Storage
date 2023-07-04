/**
* 文 件 名: heap_example.cpp
* 文件描述: 堆的使用
* 作    者: HanKin
* 创建日期: 2023.06.30
* 修改日期：2023.06.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

int main()
{
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    
    for (elem : v) {
        printf("%d ", elem);
    }
    printf("\n");
    
    // 将序列转换为堆(默认为大顶堆)
    std::make_heap(v.begin(), v.end());
    
    /*
           9
       6      4
     5   5  3   2
    1 1 3 5
    
    9 6 4 5 5 3 2 1 1 3 5
    */
    for (elem : v) {
        printf("%d ", elem);
    }
    printf("\n");
    
    // 添加一个元素到堆中
    v.push_back(8);
    std::push_heap(v.begin(), v.end());
    
    /*
           9
       6       8
     5   5   4   2
    1 1 3 5 3
    
    9 6 8 5 5 4 2 1 1 3 5 3
    */
    for (elem : v) {
        printf("%d ", elem);
    }
    printf("\n");
    
    // 移除堆中的最大元素(不输出最后一个元素)
    std::pop_heap(v.begin(), v.end());
    v.pop_back();
    
    /*
           8
       6       4
     5   5   3   2
    1 1 3 5 9
    
    8 6 4 5 5 3 2 1 1 3 5
    */
    for (elem : v) {
        printf("%d ", elem);
    }
    printf("\n");
    
    // 将堆排序为升序序列
    std::sort_heap(v.begin(), v.end());
    
    /*
           8
       6       4
     5   5   3   2
    1 1 3 5 9
    
    1 1 2 3 3 4 5 5 5 6 8
    */
    
    // 输出堆中的元素
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
