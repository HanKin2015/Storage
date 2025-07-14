/*******************************************************************************
* 文 件 名: 变参模板.cpp
* 文件描述: 使用变参模板实现一个简单的 printf
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string_view>

// 递归终止函数
void my_printf(std::string_view fmt) {
    std::cout << fmt;
}

// 变参实现
template<typename T, typename... Args>
void my_printf(std::string_view fmt, T value, Args... args) {
    for (size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] == '%' && i + 1 < fmt.size() && fmt[i + 1] != '%') {
            std::cout << value;
            my_printf(fmt.substr(i + 2), args...);
            return;
        }
        std::cout << fmt[i];
    }
}

// 使用示例
int main() {
    my_printf("Hello, %! You have % messages.\n", "Alice", 42);
    // 输出：Hello, Alice! You have 42 messages.
    return 0;
}