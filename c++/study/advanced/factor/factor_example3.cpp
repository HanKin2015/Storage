/*******************************************************************************
* 文 件 名: factor_example3.cpp
* 文件描述: 仿函数
* 备    注: 无法运行
* 作    者: HanKin
* 创建日期: 2024.02.02
* 修改日期：2024.02.02
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class Object;
class MyClosure
{
public:
    MyClosure(const std::string& ss, Object obj)
        : str(ss), object(obj) {}

    void operator() ()
    {
        std::cout << str << " " << obj;
    }

private:
    const std::string& str;
    Object object;
};

int main()
{
    std::string str = "1234";
    Object obj;
    MyClosure closure(str, obj);
    // 调用仿函数
    closure();
}