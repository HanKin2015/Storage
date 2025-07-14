/*******************************************************************************
* 文 件 名: result_of_example.cpp
* 文件描述: 用于在编译时推导可调用对象返回类型的模板元编程工具
* 备    注: 在 C++20 中被 std::invoke_result 取代，但在旧代码或需要兼容 C++11/14/17 的场景中仍有使用
* 作    者: HanKin
* 创建日期: 2025.07.13
* 修改日期：2025.07.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <type_traits>

int add(int a, int b) { return a + b; }

template<typename Func, typename... Args>
typename std::result_of<Func(Args...)>::type
compute(Func func, Args... args)
{
    return func(args...);
}

int main()
{
    auto result = compute(add, 3, 4);  // 返回类型为int
    static_assert(std::is_same<decltype(result), int>::value, "Must be int");
    std::cout << result << std::endl;  // 输出: 7
    return 0;
}