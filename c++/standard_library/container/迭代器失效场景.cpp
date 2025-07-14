/*******************************************************************************
* 文 件 名: 迭代器失效场景.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <vector>
#include <iostream>
#include <algorithm>

// 遍历删除
void traversal_delete()
{
	std::vector<int> v{1, 2, 3, 4, 5, 6};
	for (auto it = v.begin(); it != v.end();) {
		if (*it % 2 == 0) {
			it = v.erase(it);  // erase 返回下一个有效迭代器
		} else {
			++it;
		}
	}
	for_each(v.begin(), v.end(), [](int elem) {
		std::cout << elem << std::endl;
	});
	return;
}

int main()
{
	std::vector<int> v = {1, 2, 3};
	auto it = v.begin() + 1;  // it 指向 2
	std::cout << *it << std::endl;  // 2
	auto iter = v.insert(it, 10);   // 插入后，it 失效！
	std::cout << *it << ' ' << *iter << std::endl;  // 0 10
	for (const auto& elem : v) {
	    std::cout << elem << std::endl; // 1 10 2 3
	}
	
	traversal_delete();
	return 0;
}