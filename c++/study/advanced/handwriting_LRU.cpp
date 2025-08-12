/*******************************************************************************
* 文 件 名: handwriting_LRU.cpp
* 文件描述: LRU（Least Recently Used）是一种常见的缓存淘汰算法，用于解决缓存空间有限时的数据替换问题。
* 备    注: 其原理是将最近最少使用的数据从缓存中淘汰掉。
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <unordered_map>
#include <list>

class LRUCache {
private:
    int capacity;
    std::unordered_map<int, std::pair<int, std::list<int>::iterator>> cache;    // 存储链表的索引，快速查找定位更新
    std::list<int> lruList; // 时间排序的链表（巧妙的地方是不存储时间额）

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            updateLRU(key);
            return cache[key].first;
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) == cache.end()) {
            // 判断缓存是否已满
            if (cache.size() >= capacity) {
                // 删除最久未使用的键
                int oldestKey = lruList.back();
                lruList.pop_back();
                cache.erase(oldestKey);
            }
            // 插入新键
            lruList.push_front(key);
        } else {
            // 更新已存在的键的值
            updateLRU(key);
        }
        cache[key] = {value, lruList.begin()};
    }

private:
    void updateLRU(int key) {
        auto it = cache[key].second;
        lruList.erase(it);
        lruList.push_front(key);
        cache[key].second = lruList.begin();
    }
};

int main()
{
    LRUCache cache(2);

    // 测试例子
    cache.put(1, 10);
    cache.put(2, 20);

    std::cout << "Value of key 1: " << cache.get(1) << std::endl;  // 输出: 10

    cache.put(3, 30);  // 缓存容量已满，移除最久未使用的键 2
    std::cout << "Value of key 2: " << cache.get(2) << std::endl;  // 输出: -1

    cache.put(4, 40);  // 缓存容量已满，移除最久未使用的键 1
    std::cout << "Value of key 1: " << cache.get(1) << std::endl;  // 输出: -1
    std::cout << "Value of key 3: " << cache.get(3) << std::endl;  // 输出: 30
    std::cout << "Value of key 4: " << cache.get(4) << std::endl;  // 输出: 40

    return 0;
}