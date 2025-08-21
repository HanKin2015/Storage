/*******************************************************************************
* 文 件 名: string_view_example.cpp
* 文件描述:  C++17 引入的一个轻量级字符串视图类，主要用于高效地访问字符串数据而不拥有其所有权，旨在解决传统 const std::string& 传递时可能产生的性能开销问题
* 备    注: https://mp.weixin.qq.com/s/ZVYl_J7bk9PH8CRxNtBvEA
* 作    者: HanKin
* 创建日期: 2023.12.18
* 修改日期：2025.08.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <string>
#include <iostream>
#include <string_view>

std::string_view getBar()
{
  std::string b{"it is bar"};   // b 在函数结束后销毁
  return b; // 返回悬垂视图，危险！
}

std::string_view getFoo()
{
  return "It is foo";
}

using namespace std::string_literals;       // 必须包含此命名空间才能使用`s`
using namespace std::string_view_literals;  // 必须包含此命名空间才能使用`sv`

int main()
{
    std::cout << getFoo() << std::endl;
    std::cout << getBar() << std::endl; // 局部变量被销毁，因此输出乱码

    // 末尾的s和sv是C++ 标准库提供的字符串字面量运算符，用于便捷地创建 std::string 和 std::string_view 对象
    // 等价于：std::string str = std::string("Hello foo");
    std::string_view svf{"Hello foo"s};  
    std::cout << svf << std::endl;
    std::string_view svff{"Hello foo"sv}; 
    std::cout << svff << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# ./a.out 
It is foo
��fV��
Hello foo
Hello foo
*/