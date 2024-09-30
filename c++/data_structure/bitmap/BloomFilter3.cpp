/**
* 文 件 名: BloomFilter3.cpp
* 文件描述: 布隆过滤器
* 备    注：g++ BloomFilter3.cpp -std=c++11
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
	bool contains(size_t pos) const
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

//哈希函数
struct BKDRHash
{
	size_t operator()(const string& s)
	{
		// BKDR
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};
struct APHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (long i = 0; i < s.size(); i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ s[i] ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ s[i] ^ (hash >> 5)));
			}
		}
		return hash;
	}
};
struct DJBHash
{ 
	size_t operator()(const string& s)
	{
		size_t hash = 5381;
		for (auto ch : s)
		{
			hash += (hash << 5) + ch;
		}
		return hash;
	}
};

template<size_t N,
	size_t K = 3,
	class V = string,
	class HashFunc1 = BKDRHash,
	class HashFunc2 = APHash,
	class HashFunc3 = DJBHash>
class BloomFilter
{
public:
	//置为1
	void set(const V& s)
	{
		//求出哈希值
		int hash1 = HashFunc1()(s) % (N * K);
		int hash2 = HashFunc2()(s) % (N * K);
		int hash3 = HashFunc3()(s) % (N * K);

		//将哈希值的映射位置置为1
		_set.set(hash1);
		_set.set(hash2);
		_set.set(hash3);
	}

	//是否存在
	bool contains(const  V& s)
	{
		//求出哈希值
		int hash1 = HashFunc1()(s) % (N * K);
		int hash2 = HashFunc2()(s) % (N * K);
		int hash3 = HashFunc3()(s) % (N * K);

		//只要有一个不存在就判断为不存在  -- 可能存在误判
		return _set.contains(hash1) && _set.contains(hash2) && _set.contains(hash3);
	}

private:
	//位图
	bitset<N* K> _set;
};

int main(int argc, char *argv[])
{
    BloomFilter<1000000000, 3> filter;
    filter.set("123456");
    filter.set("234567");
    filter.set("345678");

    cout << filter.contains("123456") << endl; // true
    cout << filter.contains("234567") << endl; // true
    cout << filter.contains("345678") << endl; // true
    cout << filter.contains("456789") << endl; // false
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ a.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
1
1
1
0
*/