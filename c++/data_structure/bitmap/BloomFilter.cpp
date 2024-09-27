/**
* 文 件 名: BloomFilter.cpp
* 文件描述: 布隆过滤器
* 作    者: HanKin
* 创建日期: 2023.06.05
* 修改日期：2023.06.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <bitset>
#include <functional>

using namespace std;

class BloomFilter {
public:
    BloomFilter(int size, int hash_count) {
        bitset_size = size;
        bitset = new std::bitset<1000000000>();
        hash_func_count = hash_count;
    }

    void add(string key) {
        for (int i = 0; i < hash_func_count; i++) {
            int hash_value = hash_func(key, i);
            //cout << hash_value << ' ' << bitset_size << endl;
            bitset->set(hash_value, true);
        }
    }

    bool contains(string key) {
        for (int i = 0; i < hash_func_count; i++) {
            int hash_value = hash_func(key, i);
            if (!bitset->test(hash_value)) {
                return false;
            }
        }
        return true;
    }

private:
    int bitset_size;
    std::bitset<1000000000> *bitset;
    int hash_func_count;

    int hash_func(string key, int index) {
        std::hash<std::string> str_hash;
        size_t hash_value = hash<string>{}(key);
        //cout << "hash value: " << hash_value << endl;
        //cout << sizeof(size_t) << endl;
        // hash函数返回size_t类型，是一个64位数，不能使用int类型存储，会越界
        // terminate called after throwing an instance of 'std::out_of_range'
        // 可以通过%取余转换为int类型范围内
        return str_hash(key + to_string(index)) % bitset_size;
    }
};

int main() {
    BloomFilter filter(1000000000, 5);
    filter.add("123456");
    filter.add("234567");
    filter.add("345678");

    cout << filter.contains("123456") << endl; // true
    cout << filter.contains("234567") << endl; // true
    cout << filter.contains("345678") << endl; // true
    cout << filter.contains("456789") << endl; // false

    return 0;
}
/*
1
1
1
0
*/
