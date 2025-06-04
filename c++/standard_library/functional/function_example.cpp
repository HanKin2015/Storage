/**
* 文 件 名: function_example.cpp
* 文件描述: 学习functional库
* 备    注：g++ function_example.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.27
* 修改日期：2025.06.04
*
* Copyright (c) 2025 HanKin. All rights reserved.
*/
#include <iostream>
#include <functional>

void freeFunction(int x)
{
    std::cout << "Free function called with " << x << std::endl;
    return;
}

void common(std::function<int(void)> to_json, std::function<void(int)> from_json)
{
    int json = to_json();
    from_json(json);
    return;
}
class Test
{
    Test()
    {
        (void)common([this]() { return this->to_json(); }, [this](int json) { this->from_json(json); });
    }

private:
    int to_json();
    void from_json(int json);
};

int main()
{
    // 使用 std::function 包装自由函数
    std::function<void(int)> func = freeFunction;
    func(10);

    // 使用 std::function 包装 lambda 表达式
    std::function<void(int)> lambda = [](int x) {
        std::cout << "Lambda called with " << x << std::endl;
    };
    lambda(20);

    return 0;
}
