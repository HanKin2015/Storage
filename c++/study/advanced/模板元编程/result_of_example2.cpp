/*******************************************************************************
* 文 件 名: result_of_example2.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.13
* 修改日期：2025.07.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
auto multiply = [](int a, int b) { return a * b; };

// 使用std::result_of推导返回类型
using ReturnType = typename std::result_of<decltype(multiply)(int, int)>::type;
static_assert(std::is_same<ReturnType, int>::value, "Must be int");