/*******************************************************************************
* 文 件 名: quirk_sort_by_myself.cpp
* 文件描述: 快速排序
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.15
* 修改日期：2025.07.15
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>

// 分区函数：选择最后一个元素为基准
int partition(std::vector<int>& arr, int low, int high)
{
	// 初始化为非法索引
	int index = low - 1;
	// 以最后一个元素为基准
	int pivot = arr[high];
	
	for (int i = low; i < high; i++) {
		// 设置排序方向，来个从小到大的
		if (arr[i] <= pivot) {
			index++;
			std::swap(arr[i], arr[index]);
		}
	}
	std::swap(arr[index + 1], arr[high]);
	return index + 1;
}

// 快速排序递归函数
void quirk_sort(std::vector<int>& arr, int low, int high)
{
	if (low < high) {
		// 核心、支点、基准
		int pivot_index = partition(arr, low, high);
		
		quirk_sort(arr, low, pivot_index - 1);
		quirk_sort(arr, pivot_index + 1, high);
	}
	return;
}

// 封装接口
void quirk_sort(std::vector<int>& arr)
{
	if (arr.empty()) return;
	quirk_sort(arr, 0, (int)(arr.size() - 1));
	return;
}

int main()
{
	std::vector<int> arr = {3, 6, 8, 10, 1, 2, 1};
    
    // 使用递归版本排序
    quirk_sort(arr);
    for (int num : arr) {
        std::cout << num << " ";  // 输出: 1 1 2 3 6 8 10
    }
    std::cout << std::endl;
	return 0;
}