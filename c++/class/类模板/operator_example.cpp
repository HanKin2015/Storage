/*******************************************************************************
* 文 件 名: operator_example.cpp
* 文件描述: 不一样的operator重写
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

template <typename T, size_t N>
class Array {
private:
    T data[N];  // 固定大小数组
public:
    T& operator[](size_t index) { return data[index]; }
};

int main()
{
	Array<int, 5> arr;  // 创建包含 5 个 int 的数组
	arr[3] = 100;
	std::cout << arr[3] << std::endl;
	return 0;
}