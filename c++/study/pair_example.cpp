/*******************************************************************************
* 文 件 名: pair_example.cpp
* 文件描述: 学习pair
* 备    注: 
* 作    者: HanKin
* 创建日期: 2021.09.17
* 修改日期：2025.06.03
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdint>

void example()
{
    std::vector<std::pair<char, int> > v;   // error: ‘>>’ should be ‘> >’ within a nested template argument list
    std::pair<char, int> p = std::make_pair('c', 123);
    v.push_back(p);
    for (std::pair<char, int> elem : v) {   // g++ study_pair.cpp -std=c++11
        std::cout << elem.first << ' ' << elem.second << std::endl;
    }
}

// 自定义哈希函数
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ hash2; // Combine the two hash values
    }
    
    template <class T1, class T2>
    bool operator () (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

int main()
{
    using UsbChannelId = int;

    // std::unordered_set 需要其元素类型支持哈希和相等比较。std::pair 默认没有提供哈希函数，因此你需要为 std::pair 提供一个自定义的哈希函数和相等比较函数
    std::unordered_set<std::pair<UsbChannelId, uint32_t>, pair_hash> usbredir_channel_ids_free_;

    uint32_t speed_support = 12;
    UsbChannelId channel_id = 12;
    usbredir_channel_ids_free_.insert(std::make_pair(channel_id, speed_support));
    // 打印插入的元素
    for (const auto& id : usbredir_channel_ids_free_) {
        std::cout << "Channel ID: " << id.first << ", Speed Support: " << id.second << std::endl;
    }
    return 0;
}
