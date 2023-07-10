/**
* 文 件 名: vector_erase.cpp
* 文件描述: 删除元素
* 作    者: HanKin
* 创建日期: 2023.07.06
* 修改日期：2023.07.06
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <algorithm>    // 使用remove函数一定需要这个头文件
using namespace std;

static bool check_bulk_cache_list(int x)
{
    if (x % 2 == 0) {
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    
    int count = v.size();
    printf("count = %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d%c", v[i], i == count - 1 ? '\n' : ' ');
    }
    
    for (int i = 0; i < count; i++) {
        if (v[i] == 3) {
            printf("%d%c", v[i], i == count - 1 ? '\n' : ' ');
            //v.erase(v.begin() + i);
        }
    }
    
    remove(v.begin(), v.end(), 3);  // 1 2 4 5 6 6（虽然没有删除，但是也改变了里面的内容）
    v.erase(remove_if(v.begin(), v.end(), check_bulk_cache_list), v.end());
    
    count = v.size();
    printf("count = %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d%c", v[i], i == count - 1 ? '\n' : ' ');
    }
    return 0;
}