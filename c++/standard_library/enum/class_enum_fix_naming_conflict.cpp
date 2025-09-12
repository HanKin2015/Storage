/*******************************************************************************
* 文 件 名: class_enum_fix_naming_conflict.cpp
* 文件描述: 类枚举解决命名冲突
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.09.10
* 修改日期：2025.09.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

enum Color { RED, GREEN, BLUE };
//enum Fruit { APPLE, BANANA, RED };  // 编译错误：'RED' 重定义（与 Color 的 RED 冲突）
void general_enum()
{
    int x = RED;  // 直接访问，无法区分是 Color::RED 还是其他枚举的 RED

    // 是否可以通过枚举名访问呢(答案是可以)
    Color y = Color::BLUE;
    std::cout << y << std::endl;
}

enum class Status { SUCCESS, ERROR };
enum class Flags { FLAG_NONE, FLAG_READ, SUCCESS }; // 合法：SUCCESS 被各自的枚举作用域隔离
void class_enum()
{
    // 必须通过枚举名访问，无歧义
    Status s = Status::SUCCESS;
    Flags f = Flags::SUCCESS;  // 与 Status::SUCCESS 不冲突
    
    // int x = RED;  // 编译错误：未限定作用域的 RED 未定义
}

int main()
{
    general_enum();
    class_enum();
    return 0;
}