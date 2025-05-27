/*******************************************************************************
* 文 件 名: list_copy.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.22
* 修改日期：2025.05.22
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <list>
#include <algorithm> // for std::find

std::list<int> bind_info_list_compat_;
std::list<int> bind_info_list_high_;
std::list<int> bind_info_list_super_;
std::list<int> bind_info_list_;

void selectBindInfoListByChannelId(int channel_id)
{
    if (channel_id == 1) {
       bind_info_list_ = bind_info_list_compat_;
    } else if (channel_id == 2) {
       bind_info_list_ = bind_info_list_high_;
    } else {
        bind_info_list_ = bind_info_list_super_;
    }
}

int main()
{
    bind_info_list_compat_.push_back(1);
    bind_info_list_compat_.push_back(2);

    // 遍历并打印元素
    std::cout << "List elements: ";
    for (const auto& value : bind_info_list_compat_) {
        std::cout << value << " ";
    }
    std::cout << std::endl; // List elements: 1 5 1 2 3 4 5 10
    
    selectBindInfoListByChannelId(1);
    bind_info_list_.push_back(200);

    // 遍历并打印元素
    std::cout << "List elements: ";
    for (const auto& value : bind_info_list_compat_) {
        std::cout << value << " ";
    }
    std::cout << std::endl; // List elements: 1 5 1 2 3 4 5 10
    return 0;
}