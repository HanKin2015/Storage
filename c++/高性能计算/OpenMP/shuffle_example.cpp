/*******************************************************************************
* 文 件 名: shuffle_example.cpp
* 文件描述: 
* 备    注: Mersenne Twister 引擎：
            名称mt19937中的 19937 表示其周期长度为 2¹⁹⁹³⁷-1（极其巨大）。
            生成高质量的伪随机数，速度快，且统计特性优良。
            为什么不用rand()？：
            rand()的随机性较差（如周期短、分布不均匀）。
            rand()依赖全局状态，线程不安全。
            C++11 后推荐使用<random>库替代rand()。
* 作    者: HanKin
* 创建日期: 2025.07.23
* 修改日期：2025.07.23
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <numeric>
#include <algorithm>
#include <vector>
#include <iostream>
#include <random>
#include <array>

// 更高质量的随机性（如密码学场景）
void test()
{
    std::array<unsigned int, 624> seed_data;  // mt19937需要624个uint作为种子
    std::random_device rd;
    std::generate_n(seed_data.data(), seed_data.size(), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 g(seq);  // 使用seed_seq聚合多个随机数作为种子
}

int main()
{
    std::vector<int> indices(5);
    std::iota(indices.begin(), indices.end(), 0);  // 生成 {0, 1, 2, 3, 4}
    
    // 随机打乱顺序
    std::random_device rd;  // 创建随机设备（std::random_device）获取真随机种子
    std::mt19937 g(rd());   // 初始化伪随机数生成器（std::mt19937）并使用种子
    std::shuffle(indices.begin(), indices.end(), g);    // 应用洗牌算法（std::shuffle）打乱序列
    
    for (int idx : indices) {
        std::cout << idx << " ";  // 可能输出: 3 1 4 0 2
    }
    std::cout << std::endl;
    return 0;
}