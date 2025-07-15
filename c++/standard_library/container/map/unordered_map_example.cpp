/*******************************************************************************
* 文 件 名: unordered_map_example.cpp
* 文件描述: std::unordered_map 需要一个哈希函数来计算键的哈希值，而标准库并未为 std::pair 提供默认的哈希函数
* 备    注: 但是std::map是支持的
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <unordered_map>
#include <iostream>

// 自定义哈希函数
struct PairHash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        // 使用异或和位移组合两个哈希值
        return hash1 ^ (hash2 << 1);
    }
};

int main()
{
    // 指定自定义哈希函数
    std::unordered_map<std::pair<int, int>, int, PairHash> chess_board;
    chess_board[std::make_pair(1, 1)] = 1;
    
    // 验证插入结果
    auto it = chess_board.find({1, 1});
    if (it != chess_board.end()) {
        std::cout << "Value at (1,1): " << it->second << std::endl;
    }
    
    return 0;
}