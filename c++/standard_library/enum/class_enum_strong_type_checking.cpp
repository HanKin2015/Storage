/*******************************************************************************
* 文 件 名: class_enum_strong_type_checking.cpp
* 文件描述: 类枚举强类型检查
* 备    注: 普通枚举的值本质是整数，可与整数类型隐式转换，容易导致逻辑错误；类枚举是独立类型，禁止与整数或其他枚举类型隐式转换，类型安全性更高
* 作    者: HanKin
* 创建日期: 2025.09.10
* 修改日期：2025.09.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

enum Status { SUCCESS, ERROR };
void general_enum()
{
    Status s = ERROR;
    int x = s;  // 隐式转换为整数（SUCCESS → 1），合法但可能意外改变类型
    std::cout << x << std::endl;
    
    if (s == 0) {  // 枚举值与整数直接比较，逻辑模糊
        // ...
    }
    
    // error: invalid conversion from ‘int’ to ‘Status’ [-fpermissive]
    //Status s2 = 1;  // 部分编译器允许（隐式转换），但语义错误（整数直接赋值给枚举）
}

enum class Flags { SUCCESS, ERROR };
void class_enum()
{
    Flags s = Flags::SUCCESS;
    // int x = s;  // 编译错误：禁止隐式转换为整数
    
    // if (s == 0) {  // 编译错误：禁止枚举值与整数直接比较
    //     ...
    // }
    
    // Flags s2 = 1;  // 编译错误：禁止整数隐式转换为枚举
    
    // 显式转换是允许的（需手动确认）
    int x = static_cast<int>(s);  // 需显式转换，明确表达意图
    std::cout << x << std::endl;
}

int main()
{
    general_enum();
    class_enum();
    return 0;
}