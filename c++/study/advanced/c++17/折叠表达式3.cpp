/*******************************************************************************
* 文 件 名: 折叠表达式3.cpp
* 文件描述: 折叠方向的重要性
* 备    注: 若要逆序打印参数，需显式反转参数包的顺序，而不是依赖折叠方向
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <utility>

// 递归终止函数
void print_reverse() {
    std::cout << std::endl;
}

// 递归处理参数包
template<typename T, typename... Args>
void print_reverse(T first, Args... args) {
    print_reverse(args...);  // 先处理后续参数
    std::cout << first << " ";  // 最后打印当前参数
}

int main() {
    print_reverse(1, 2, 3);  // 输出：3 2 1
    return 0;
}