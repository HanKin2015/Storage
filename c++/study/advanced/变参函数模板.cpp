/*******************************************************************************
* 文 件 名: 变参函数模板.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
// 递归终止函数
template<typename T>
T sum(T value) {
    return value;
}

// 变参函数模板
template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);  // 展开参数包
}

// 使用示例
int result = sum(1, 2, 3, 4);  // 结果：10