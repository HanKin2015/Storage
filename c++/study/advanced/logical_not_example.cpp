logical_not_example.cpp

在 C++ 中，std::logical_not<T> 是标准库提供的一个函数对象（仿函数），用于执行逻辑非（NOT）运算。它定义在 <functional> 头文件中，是一个模板结构体，通过重载 operator() 实现对单个参数的逻辑取反操作。

#include <vector>
#include <algorithm>
#include <functional>

// 移除所有为false的元素
std::vector<bool> flags = {true, false, true, false};
flags.erase(
    std::remove_if(flags.begin(), flags.end(), std::logical_not<bool>()),
    flags.end()
);
// flags 现在只包含 {true, true}

struct IsEven {
    bool operator()(int x) const { return x % 2 == 0; }
};

// 使用 std::logical_not 包装 IsEven，创建 IsOdd 功能
std::logical_not<IsEven> isOdd;
bool result = isOdd(5); // true

#include <iostream>
#include <functional>

int main() {
    std::logical_not<int> not_op;
    std::cout << std::boolalpha;
    std::cout << not_op(0) << std::endl;  // true（!0 为 true）
    std::cout << not_op(42) << std::endl; // false（!42 为 false）
    return 0;
}

// 使用 std::logical_not
std::remove_if(v.begin(), v.end(), std::logical_not<bool>());

// 使用 Lambda 替代
std::remove_if(v.begin(), v.end(), [](bool b) { return !b; });
