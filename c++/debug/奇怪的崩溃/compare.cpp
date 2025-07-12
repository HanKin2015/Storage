
/*******************************************************************************
* 文 件 名: compare.cpp
* 文件描述: 在特定情形下，比较函数里的非严格弱序关系（使用<=而非<）可能会让排序算法进入无限循环或者导致内存损坏，最终间接造成溢出错误。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.13
* 修改日期：2025.07.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <algorithm>
#include <vector>

bool invalid_comp(int a, int b)
{
    return a <= b; // 错误：非严格弱序
}

int main()
{
    std::vector<int> nums = {1, 1, 1};
	// 虽然此测试无问题，但是在比赛刷题中发现比较函数中是等号时会出现堆栈溢出错误
    std::sort(nums.begin(), nums.end(), invalid_comp); // 可能崩溃
    return 0;
}