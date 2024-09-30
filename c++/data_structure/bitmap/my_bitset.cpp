/**
* 文 件 名: my_bitset.cpp
* 文件描述: 自定义bitset
* 备    注：g++ my_bitset.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.29
* 修改日期：2024.09.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <cstdio>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

template <size_t N = 10>
class bitset
{
public:
	bitset()
	{
		_set.resize((N/32+1), 0);
	}

	//pos位置的值是否存在
	bool test(size_t pos) const
	{
		int x = pos / 32;
		int y = pos % 32;

		return (_set[x] & (1 << y));
	}
	
	//将pos位置置1
	bitset& set(size_t pos)
	{
		int x = pos / 32;
		int y = pos % 32;

		_set[x] |= (1 << y);

		return *this;
	}

	//将pos位置置0
	bitset& reset(size_t pos)
	{
		int x = pos / 32;
		int y = pos % 32;

		_set[x] &= (~(1 << y));

		return *this;
	}

private:
	vector<int> _set;
};

void test_bitste()
{
	bitset<100000> bs;
	
	//储存一万个元素
	int arr[10000] = { 0 };
	for (int i = 1; i < 10000; i++) {
		arr[i] = rand() % 10000 + i;
	}

	//将一万个元素置为1
	for (auto& e : arr) {
		bs.set(e);
	}

	//判断这些元素是否都存在
	for (auto& e : arr) {
		if (bs.test(e))	cout << "OK" << endl;
		//出错直接终止程序
		else assert(false);
	}

	//将元素全部删除
	for (auto& e : arr) {
		bs.reset(e);

		//如果还存在直接终止程序
		if (!bs.test(e))	cout << "OK" << endl;
		else	assert(false);
	}
}

int main(int argc, char *argv[])
{
    test_bitste();
    return 0;
}