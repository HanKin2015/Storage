/*******************************************************************************
* 文 件 名: 成员遍历与批量操作.cpp
* 文件描述: 更多例子见https://mp.weixin.qq.com/s/_Po9KyWBGCb3BKKOHLti4g
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.09.17
* 修改日期：2025.09.17
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <variant>

class Person {
public:
    int age;
    std::string name;
    double height;
};

int main()
{
    Person p{25, "Diana", 1.70};

    // 定义成员指针数组：存储需要遍历的成员（用variant兼容不同类型）
    using MemberPtr = std::variant<int Person::*, std::string Person::*, double Person::*>;
    std::vector<MemberPtr> member_ptrs = {
        &Person::age,
        &Person::name,
        &Person::height
    };

    // 批量遍历并打印成员（用visit处理variant类型）
    for (const auto& ptr : member_ptrs) {
        std::visit([&p](auto&& arg) {
            std::cout << p.*arg << " "; // 通用访问逻辑，无需区分成员类型
        }, ptr);
    }
    std::cout << std::endl;
    // 输出：25 Diana 1.70

    return 0;
}