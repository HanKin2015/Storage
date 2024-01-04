/*******************************************************************************
* 文 件 名: no_explicit_example.cpp
* 文件描述: 只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的, 跟它相对应的另一个关键字是implicit
* 备    注: https://blog.csdn.net/guoyunfei123/article/details/89003369
* 作    者: HanKin
* 创建日期: 2024.01.04
* 修改日期：2024.01.04
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <malloc.h>
using namespace std;

class CxString  // 没有使用explicit关键字的类声明, 即默认为隐式声明  
{  
public:  
    char *_pstr;  
    int _size;  
    CxString(int size) {  
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
    CxString string1(24);     // 这样是OK的, 为CxString预分配24字节的大小的内存  
    CxString string2 = 10;    // 这样是OK的, 为CxString预分配10字节的大小的内存  
    CxString string3;         // 这样是不行的, 因为没有默认构造函数, 错误为: “CxString”: 没有合适的默认构造函数可用  
    CxString string4("aaaa"); // 这样是OK的  
    CxString string5 = "bbb"; // 这样也是OK的, 调用的是CxString(const char *p)  
    CxString string6 = 'c';   // 这样也是OK的, 其实调用的是CxString(int size), 且size等于'c'的ascii码  
    string1 = 2;              // 这样也是OK的, 为CxString预分配2字节的大小的内存  
    string2 = 3;              // 这样也是OK的, 为CxString预分配3字节的大小的内存  
    string3 = string1;        // 这样也是OK的, 至少编译是没问题的, 但是如果析构函数里用free释放_pstr内存指针的时候可能会报错, 完整的代码必须重载运算符"=", 并在其中处理内存释放  
    return 0;
}

