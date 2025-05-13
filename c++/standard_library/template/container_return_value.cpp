/*******************************************************************************
* 文 件 名: container_return_value.cpp
* 文件描述: 容器返回值处理
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

    // 限制 T 必须是 std::unique_ptr 的派生类型（可能需要更复杂的 SFINAE 或概念）
    template <typename T>
    void Add(T&& policy) // 使用万能引用
    {
        if (!policy.get()) {
            printf("invalid param. policy %p\n", policy.get());
            return;
        }
        m_policies.push_back(std::forward<T>(policy)); // 正确移动或复制
    }

    const std::list<std::unique_ptr<std::string>>& GetPolicies() const 
    {
        return m_policies;
    }

private:
    std::list<std::unique_ptr<std::string>> m_policies;
};

int main()
{
    //Manager mgr = Manager::get_instance();
    auto& mgr = Manager::get_instance(); // 正确获取单例引用
    mgr.Add(std::make_unique<std::string>("hello"));
    mgr.Add(std::make_unique<std::string>("world"));

    auto& policies = mgr.GetPolicies();
    for (const auto& item : policies) {
        printf("%s\n", item->c_str());
    }
    return 0;
}