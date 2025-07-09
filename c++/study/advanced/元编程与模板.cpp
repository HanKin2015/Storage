/*******************************************************************************
* 文 件 名: 元编程与模板.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.09
* 修改日期：2025.07.09
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <queue>

template<typename Container>
void print_size(const Container& c) {
    decltype(c.size()) size = c.size();  // 无需知道 Container 的具体类型
    std::cout << "Size: " << size << std::endl;
}

int main()
{
	std::priority_queue<int> pq;
	pq.push(10);
	print_size(pq);
	return 0;
}