/*******************************************************************************
* 文 件 名: hash_table_by_myself.cpp
* 文件描述: 手搓实现哈希表
* 备    注: 使用vector<list<Node>>作为底层存储，即数组 + 链表的组合（链地址法）
            每个链表（桶）存储哈希值相同的元素，解决哈希冲突
* 作    者: HanKin
* 创建日期: 2025.09.02
* 修改日期：2025.09.02
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

// 哈希表类模板
template <typename K, typename V>
class HashTable {
private:
    // 哈希表节点结构
    struct Node {
        K key;
        V value;
        Node(K k, V v) : key(k), value(v) {}
    };

    std::vector<std::list<Node>> table;  // 哈希表主体，数组+链表
    int capacity;                        // 哈希表容量
    int size;                            // 当前元素数量
    const double loadFactorThreshold;    // 负载因子阈值，超过则扩容

    // 哈希函数：将键映射到索引
    int hash(const K& key) const {
        // 使用std::hash进行哈希计算，然后取模
        return std::hash<K>()(key) % capacity;
    }

    // 扩容操作
    void resize() {
        int oldCapacity = capacity;
        capacity *= 2;  // 容量翻倍
        
        // 创建新的哈希表
        std::vector<std::list<Node>> newTable(capacity);
        
        // 将旧表中的元素重新哈希到新表
        for (int i = 0; i < oldCapacity; ++i) {
            for (const Node& node : table[i]) {
                int newIndex = hash(node.key);
                newTable[newIndex].push_back(node);
            }
        }
        
        // 替换旧表
        table.swap(newTable);
    }

public:
    // 构造函数
    HashTable(int initialCapacity = 16, double threshold = 0.75) 
        : capacity(initialCapacity), size(0), loadFactorThreshold(threshold) {
        table.resize(capacity);
    }

    // 插入键值对
    void insert(const K& key, const V& value) {
        // 检查是否需要扩容
        if (loadFactor() >= loadFactorThreshold) {
            resize();
        }

        int index = hash(key);
        
        // 检查键是否已存在，如果存在则更新值
        for (Node& node : table[index]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        
        // 键不存在，插入新节点
        table[index].emplace_back(key, value);
        size++;
    }

    // 查找键对应的值
    bool find(const K& key, V& value) const {
        int index = hash(key);
        
        for (const Node& node : table[index]) {
            if (node.key == key) {
                value = node.value;
                return true;
            }
        }
        
        return false;  // 未找到
    }

    // 删除键值对
    bool erase(const K& key) {
        int index = hash(key);
        
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                size--;
                return true;
            }
        }
        
        return false;  // 未找到要删除的键
    }

    // 获取当前元素数量
    int getSize() const {
        return size;
    }

    // 获取哈希表容量
    int getCapacity() const {
        return capacity;
    }

    // 计算当前负载因子
    double loadFactor() const {
        return static_cast<double>(size) / capacity;
    }

    // 打印哈希表内容（用于调试）
    void print() const {
        for (int i = 0; i < capacity; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const Node& node : table[i]) {
                std::cout << "[" << node.key << " => " << node.value << "] ";
            }
            std::cout << std::endl;
        }
    }
};

// 测试函数
int main() {
    // 创建一个字符串到整数的哈希表
    HashTable<std::string, int> ht;

    // 插入数据
    ht.insert("apple", 5);
    ht.insert("banana", 3);
    ht.insert("cherry", 7);
    ht.insert("date", 2);
    ht.insert("elderberry", 9);

    std::cout << "哈希表初始状态:" << std::endl;
    ht.print();
    std::cout << "当前大小: " << ht.getSize() << ", 容量: " << ht.getCapacity() << std::endl;
    std::cout << "负载因子: " << ht.loadFactor() << std::endl << std::endl;

    // 查找数据
    int value;
    if (ht.find("banana", value)) {
        std::cout << "找到 banana: " << value << std::endl;
    } else {
        std::cout << "未找到 banana" << std::endl;
    }

    // 更新数据
    ht.insert("banana", 10);
    if (ht.find("banana", value)) {
        std::cout << "更新后 banana 的值: " << value << std::endl << std::endl;
    }

    // 删除数据
    ht.erase("date");
    std::cout << "删除 date 后:" << std::endl;
    ht.print();
    std::cout << "当前大小: " << ht.getSize() << std::endl << std::endl;

    // 插入更多数据，触发扩容
    ht.insert("fig", 4);
    ht.insert("grape", 6);
    ht.insert("kiwi", 8);
    ht.insert("lemon", 1);
    
    std::cout << "插入更多数据后（可能已扩容）:" << std::endl;
    ht.print();
    std::cout << "当前大小: " << ht.getSize() << ", 容量: " << ht.getCapacity() << std::endl;
    std::cout << "负载因子: " << ht.loadFactor() << std::endl;

    return 0;
}
