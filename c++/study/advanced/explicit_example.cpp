/*******************************************************************************
* 文 件 名: explicit_example.cpp
* 文件描述: 只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的, 跟它相对应的另一个关键字是implicit
* 备    注: https://blog.csdn.net/guoyunfei123/article/details/89003369
* 作    者: HanKin
* 创建日期: 2024.01.04
* 修改日期：2024.01.04
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <array>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <malloc.h>
using namespace std;

class CxString  // 使用explicit关键字的类声明, 显式声明  
{  
public:  
    char *_pstr;  
    int _size;  
    explicit CxString(int size) {  
        _size = size;                // string的预设大小  
        _pstr = (char *)malloc(size + 1);    // 分配string的内存  
        memset(_pstr, 0, size + 1);  
    }  
    CxString(const char *p) {  
        int size = strlen(p);  
        _pstr = (char *)malloc(size + 1);    // 分配string的内存  
        strcpy(_pstr, p);            // 复制字符串  
        _size = strlen(_pstr);  
    }  
    // 析构函数这里不讨论, 省略...
};  
  
int main()
{
    // 下面是调用:
    CxString string1(24);     // 这样是OK的  
    CxString string2 = 10;    // 这样是不行的, 因为explicit关键字取消了隐式转换  
    CxString string3;         // 这样是不行的, 因为没有默认构造函数  
    CxString string4("aaaa"); // 这样是OK的  
    CxString string5 = "bbb"; // 这样也是OK的, 调用的是CxString(const char *p)  
    CxString string6 = 'c';   // 这样是不行的, 其实调用的是CxString(int size), 且size等于'c'的ascii码, 但explicit关键字取消了隐式转换  
    string1 = 2;              // 这样也是不行的, 因为取消了隐式转换  
    string2 = 3;              // 这样也是不行的, 因为取消了隐式转换  
    string3 = string1;        // 这样也是不行的, 因为取消了隐式转换, 除非类实现操作符"="的重载
    return 0;
}