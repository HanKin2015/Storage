/*******************************************************************************
* 文 件 名: operator_example2.cpp
* 文件描述: C++11 新特性之operator "" xxx
* 备    注: https://www.cnblogs.com/moodlxs/p/10148026.html
* 作    者: HanKin
* 创建日期: 2024.01.03
* 修改日期：2024.01.03
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <chrono>
using namespace std;

class Person
{
public:
    Person(const std::string& name): _name(name){}
    std::string name() const {
        return _name;
    }
private:
    std::string _name;
};

// 写成这样也正确inline Person operator "" _psn (const char *name, size_t n)
inline Person operator""_psn(const char *name, size_t n)
{
    return Person(std::string(name, n));
}
 
int main()
{
    auto person = "Xiao Ming"_psn;
    std::cout<< "The person' name is " << person.name() << std::endl;
    
    // 在std::literals::chrono_literals的实现用，也用了类似的手段
    using namespace std::chrono_literals;
    auto d1 = 250ms;
    std::chrono::milliseconds d2 = 1s;
    std::cout << "250ms = " << d1.count() << " milliseconds\n"
              << "1s = " << d2.count() << " milliseconds\n";
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ operator_example2.cpp -std=c++17
[root@ubuntu0006:~/cmake] #./a.out
The person' name is Xiao Ming
250ms = 250 milliseconds
1s = 1000 milliseconds
*/