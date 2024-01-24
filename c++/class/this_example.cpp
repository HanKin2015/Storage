/*******************************************************************************
* 文 件 名: this_example.cpp
* 文件描述: this指针作用
* 作    者: HanKin
* 创建日期: 2023.06.30
* 修改日期：2023.06.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

class Person {
public:
    void setName(const std::string& name) {
        this->name = name;  // 使用this指针访问成员变量（可以重名）
    }
    
    std::string getName() const {
        return this->name;  // 使用this指针访问成员变量
    }
    
private:
    std::string name;
};

class Person2 {
public:
    void setName(const std::string& name2) {
        name = name2;    // 可以省去this指针，但是不能重名
    }
    
    std::string getName() const {
        return name;
    }
    
private:
    std::string name;
};

int main(int argc, char *argv[])
{
    Person obj;
    obj.setName("wangzhe");
    cout << obj.getName() << endl;
    
    Person obj2;
    obj2.setName("rongyao");
    cout << obj2.getName() << endl;
    return 0;
}