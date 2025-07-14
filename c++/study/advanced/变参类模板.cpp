/*******************************************************************************
* 文 件 名: 变参类模板.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/

// 递归定义
template<typename... Args>
struct Tuple;

// 终止条件：空参数包
template<>
struct Tuple<> {};

// 递归展开
template<typename T, typename... Args>
struct Tuple<T, Args...> {
    T value;
    Tuple<Args...> tail;

    Tuple(T v, Args... args) : value(v), tail(args...) {}
};

// 使用示例
Tuple<int, double, char> t(1, 3.14, 'A');