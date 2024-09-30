/**
* 文 件 名: BloomFilter2.cpp
* 文件描述: 布隆过滤器，之前那个由于调用hash库函数导致越界错误
* 作    者: HanKin
* 创建日期: 2023.06.05
* 修改日期：2023.06.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <bitset>
#include <string>
using namespace std;

class BloomFilter
{
public:
    BloomFilter(int size, int hash_count) : bitset_(size), hash_count_(hash_count) {}

    void add(const string& str)
    {
        for (int i = 0; i < hash_count_; i++) {
            int hash_value = hash(str, i);
            bitset_.set(hash_value);
        }
    }

    bool contains(const string& str) const
    {
        for (int i = 0; i < hash_count_; i++) {
            int hash_value = hash(str, i);
            if (!bitset_.test(hash_value)) {
                return false;
            }
        }
        return true;
    }

private:
    bitset<1000000> bitset_;
    int hash_count_;

    int hash(const string& str, int index) const
    {
        int hash_value = 0;
        for (char c : str) {
            hash_value = hash_value * 31 + c;
        }
        return (hash_value + index) % bitset_.size();
    }
};

int main() {
    BloomFilter filter(1000000, 5);

    filter.add("hello");
    filter.add("world");
    filter.add("foo");
    filter.add("bar");

    cout << filter.contains("hello") << endl;  // 输出1
    cout << filter.contains("world") << endl;  // 输出1
    cout << filter.contains("foo") << endl;    // 输出1
    cout << filter.contains("bar") << endl;    // 输出1
    cout << filter.contains("baz") << endl;    // 输出0
    return 0;
}
