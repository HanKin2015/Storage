/*
 * trie.hpp
 * 字典树算法
 *
 * 优点是：利用字符串的公共前缀来减少查询时间，最大限度地减少无谓的字符串比较，查询效率比哈希树高。
 * 对于字典树，有三个重要性质：
 *     1：根节点不包含字符，除了根节点，每个节点都只包含一个字符。root 节点不包含字符，这样做的目的是为了能够包括所有字符串。
 *     2：从根节点到某一个节点，路过字符串起来就是该节点对应的字符串。
 *     3：每个节点的子节点字符不同，也就是找到对应单词、字符是唯一的。
 *
 * date  : 2021.07.08
 * author: hejian
 *
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#pragma once

#include "json_interface.h"
#include <map>
#include "log.h"

typedef udev_info TRIE_DATA_STRUCT;

class Trie {
    struct trie_node {
        bool is_end;                // 结束标志(树高固定9可以不使用)
        TRIE_DATA_STRUCT data;      // 节点数据
        map<char, trie_node> next;   // pvid含有a-z,0-9两段字符不连续
        trie_node()
        {
            is_end = false;
        }
    };


public:
    // 根节点
    trie_node root;

    // 构造函数
    Trie()
    {

    }

    // 插入pvid
    void insert(string pvid, TRIE_DATA_STRUCT data)
    {
        trie_node* p = &root;
        for (int i = 0; i < pvid.size(); i++) {
            char c = pvid[i];
            if (p->next.find(c) == p->next.end()) {
                trie_node tmp;
                p->next.insert(pair<char, trie_node>(c, tmp));
            }
            p = &p->next[c];
        }
        p->data = data;
        p->is_end = true;
        return;
    }

    // 搜索pvid是否存在
    bool search(string pvid)
    {
        trie_node* p = &root;
        for (int i = 0; i < pvid.size(); i++) {
            char c = pvid[i];
            if (p->next.find(c) == p->next.end()) {
                return false;
            }
            p = &p->next[c];
        }
        return true;
    }

    // 输出所有树枝，即pvid
    void output(trie_node r, vector<JSON_DATA_STRUCT> &json_data)
    {
        if (!r.next.empty()) {
            if (r.is_end) {
                LOGD("pvid = %s:%s", r.data.vid.c_str(), r.data.pid.c_str());
                json_data.push_back(r.data);
            }
            for (auto& it : r.next) {
                output(it.second, json_data);
            }
        } else {
            LOGD("pvid = %s:%s", r.data.vid.c_str(), r.data.pid.c_str());
            json_data.push_back(r.data);
        }
        return;
    }
};