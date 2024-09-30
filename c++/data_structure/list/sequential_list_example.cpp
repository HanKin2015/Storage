/*******************************************************************************
* 文 件 名: sequential_list_example.cpp
* 文件描述: 顺序表
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.09.29
* 修改日期：2024.09.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> seqList = {1, 2, 3, 4, 5};
    // 访问元素
    std::cout << "Element at index 2: " << seqList[2] << std::endl;
    // 插入元素
    seqList.insert(seqList.begin() + 2, 10);
    // 删除元素
    seqList.erase(seqList.begin() + 3);
    return 0;
}
