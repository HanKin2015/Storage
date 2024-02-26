/*******************************************************************************
* 文 件 名: factor_example.cpp
* 文件描述: 仿函数
* 备    注: https://baike.baidu.com/item/%E4%BB%BF%E5%87%BD%E6%95%B0?fromModule=lemma_search-box
* 作    者: HanKin
* 创建日期: 2024.01.31
* 修改日期：2024.01.31
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

// 定义一个简单的仿函数
class MultiplyBy
{
public:
    MultiplyBy(int factor) : factor_(factor) {}

    // 重载括号运算符
    int operator()(int x) const {
        return x * factor_;
    }

private:
    int factor_;
};

int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    MultiplyBy multiplyByTwo(2);

    // 使用仿函数在std::transform中对容器中的元素进行操作
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), multiplyByTwo);

    // 输出结果
    for (int num : numbers) {
        std::cout << num << " ";    // 2 4 6 8 10
    }
    std::cout << std::endl;

    return 0;
}
