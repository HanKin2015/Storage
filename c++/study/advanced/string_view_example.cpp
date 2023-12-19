/*******************************************************************************
* 文 件 名: string_view_example.cpp
* 文件描述: 未调试
* 备    注: https://mp.weixin.qq.com/s/ZVYl_J7bk9PH8CRxNtBvEA
* 作    者: HanKin
* 创建日期: 2023.12.18
* 修改日期：2023.12.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <string>
#include <iostream>
#include <string_view>

std::string_view getBar() {
  std::string b{"it is bar."};
  return b;
}

std::string_view getFoo() {
  return "It is foo.";
}

using namespace std::string_literals;
using namespace std::string_view_literals;

int main()
{
    std::cout << getFoo() << std::endl;   // 1
    std::cout << getBar() << std::endl;   // 2
    std::string_view svf{"Hello foo"s};  
    std::cout << svf << std::endl;     // 3
    std::string_view svff{"Hello foo"sv}; 
    std::cout << svff << std::endl;    // 4
    return 0;
}