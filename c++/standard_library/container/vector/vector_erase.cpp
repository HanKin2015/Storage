/**
* 文 件 名: vector_erase.cpp
* 文件描述: 删除元素
* 备    注：https://blog.csdn.net/hhq123_/article/details/128476810
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

// remove和remove_if函数
static void practice1(vector<int> v)
{
    printf("%d: %s\n", __LINE__, __FUNCTION__);
    int count = v.size();
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
    return;
}

// 直接删除法
#define VECTOR_ERASE_ELEMENT(vec, idx) \
    free(vec[idx]); \
    vec[idx] = NULL; \
    vec.erase(vec.begin() + idx); \
    idx--;
static void practice2()
{
    printf("%d: %s\n", __LINE__, __FUNCTION__);
    vector<int *> vec;
    for (int i = 1; i < 7; i++) {
        int *j = (int *)calloc(1, sizeof(int));
        *j = i;
        vec.push_back(j);
    }

    int count = vec.size();
    printf("count = %d\n", count);
    for (int i = 0; i < vec.size(); i++) {  // 这里一定要注意上限
        if (*vec[i] > 5) {
            VECTOR_ERASE_ELEMENT(vec, i);
            //free(vec[i]);
            //vec[i] = NULL;
            //vec.erase(vec.begin() + i);
            //i--;
        }
    }
    
    count = vec.size();
    printf("count = %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d%c", *vec[i], i == count - 1 ? '\n' : ' ');
        free(vec[i]);
        vec[i] = NULL;
    }
    return;
}

// 遍历覆盖法
static void practice3()
{
    printf("%d: %s\n", __LINE__, __FUNCTION__);
    vector<int *> vec;
    for (int i = 1; i < 7; i++) {
        int *j = (int *)calloc(1, sizeof(int));
        *j = i;
        vec.push_back(j);
    }

    int count = vec.size();
    printf("count = %d\n", count);
    
    int idx = 0;
    for (int i = 0; i < count; i++) {
        if (*vec[i] % 2 == 0) {
            vec[idx++] = vec[i];
        } else {
            free(vec[i]);
            vec[i] = NULL;
        }
    }
    for (int i = count - 1; i >= idx; i--) {
        vec.erase(vec.begin() + i);
    }
    count = vec.size();
    printf("count = %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d%c", *vec[i], i == count - 1 ? '\n' : ' ');
        free(vec[i]);
        vec[i] = NULL;
    }
    return;
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
    
    practice1(v);
    practice2();
    practice3();
    return 0;
}