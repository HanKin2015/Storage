/*******************************************************************************
* 文 件 名: gdb_print_map.cpp
* 文件描述: gdb调试打印map变量
* 备    注: https://www.cnblogs.com/silentNight/p/5466418.html
* 作    者: HanKin
* 创建日期: 2024.05.10
* 修改日期：2024.05.10
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <map>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
using namespace std;

int main()
{
    map<string, int*> map_;
    for (int i = 0; i < 28; i++) {
        int *value = new int(2024+i);
        string key = "key" + to_string(i);
        map_.insert(make_pair(key, value));
    }
    // 这里可以打断点
    map<string, int*>::iterator it;
    for (it = map_.begin(); it != map_.end(); it++) {
        printf("%s %d\n", it->first.data(), *(it->second));
    }
    return 0;
}