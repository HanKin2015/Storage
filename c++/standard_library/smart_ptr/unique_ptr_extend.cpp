/**
* 文 件 名: unique_ptr_extend.cpp
* 文件描述: unique_ptr指针的扩展，扩展 auto_ptr 不能完成的功能
* 备    注: unique_ptr是独占所有权的智能指针，无法进行复制，因此不能简单的for循环遍历
* 作    者: HanKin
* 创建日期: 2023.09.01
* 修改日期：2023.09.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <memory>
using namespace std;

// 资源清理函数
//void end_connection(connection *p) { disconnect(*p); }

int main()
{
    // 方式一（这行编译不通过）
    //vector<unique_ptr<string> > vs{ new string("Doug"), new string("Adams") };  

    // 方式二
    vector<unique_ptr<string> > v;  
    unique_ptr<string> p1(new string("abc"));
    v.push_back(std::move(p1));    // 在c++11当中有了移动语义,使用move()给unique_ptr传入函数
    
    //for(unique_ptr<string>& up : vs) {
    //    printf("vs %s\n", (*up).c_str());
    //}
    for(unique_ptr<string>& up : v) {
        printf("v %s\n", (*up).c_str());
    }
    
    unique_ptr<int[]> p (new int[3]{1, 2, 3});  
    p[0] = 100;// 重载了operator[]
    for(int i = 0; i < 3; i++) {
        printf("p %d\n", p[i]);
    }
    
    // 资源清理器的类型
    //unique_ptr<connection, decltype(end_connection)*> p(&c, end_connection);// 传入函数名，会自动转换为函数指针
    return 0;
}
/*
v abc
p 100
p 2
p 3
*/
