/**
* 文 件 名: unique_ptr_extend2.cpp
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

struct StringDeleter {
    void operator()(std::string* p) const {
        delete p;
    }
};

int main()
{
    // 编译不通过
    //std::vector<std::unique_ptr<std::string, StringDeleter>> vs{
    //    std::unique_ptr<std::string, StringDeleter>{new std::string{"Doug"}},
    //    std::unique_ptr<std::string, StringDeleter>{new std::string{"Adams"}}
    //};
    
    //std::vector<std::unique_ptr<std::string>> vs{
    //    std::make_unique<std::string>("Doug"),
    //    std::make_unique<std::string>("Adams")
    //};
    
    std::vector<std::shared_ptr<std::string>> vs1{
        std::make_shared<std::string>("Doug"),
        std::make_shared<std::string>("Adams")
    };
    
    vector<unique_ptr<string>> vs;
    vs.emplace_back(std::make_unique<string>("Doug"));
    vs.emplace_back(std::make_unique<string>("Adams"));

     std::vector<std::unique_ptr<int>> vec1{};
    //向vec1中添加3个指针元素
    vec1.emplace_back(std::unique_ptr<int>(new int(1)));
    vec1.emplace_back(std::unique_ptr<int>(new int(2)));
    
    /*
    vector<unique_ptr<string> > vs{ new string("Doug"), new string("Adams") }; 
    明白为何这种失败了，这种写法跟unique_ptr<string> p = new string("Doug")有什么区别
    然而都编译不通过
    */
    //vector<unique_ptr<string>> vs2{ unique_ptr<string>(new string("Doug")), unique_ptr<string>(new string("Adams")) };
    //vector<unique_ptr<string>> vs2{ make_unique<string>("Doug"), make_unique<string>("Adams") };
    //vector<unique_ptr<string>> vs2{ move(make_unique<string>("Doug")), move(make_unique<string>("Adams")) }; 
    return 0;
}
