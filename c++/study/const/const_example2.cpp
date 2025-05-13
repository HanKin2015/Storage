/*******************************************************************************
* 文 件 名: const_example2.cpp
* 文件描述: 学习const
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.12
* 修改日期：2025.05.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <list>
#include <cstring>
#include <cstdio>
#include <memory>

class Manager {
public:
    static Manager& get_instance()
    {
        static Manager instance;
        return instance;
    }

    // 第一个const表示返回的 std::list<std::unique_ptr<std::string>> 对象是常量，调用者不能修改这个列表的内容
    // 第二个const表示这个成员函数不会修改类的任何成员变量。换句话说，GetPolicies() 是一个常量成员函数，调用这个函数不会改变对象的状态
    const std::list<std::unique_ptr<std::string> >& GetPolicies() const 
    {
        return m_policies;
    }

private:
    std::list<std::unique_ptr<std::string> > m_policies;
};

int main()
{
    // 错误
    //Manager mgr = Manager::get_instance();
    //auto& policies = mgr.GetPolicies();

    auto& policies = Manager::get_instance().GetPolicies();
    for (const auto& item : policies) {
        printf("%s\n", item->c_str());
    }
    return 0;
}