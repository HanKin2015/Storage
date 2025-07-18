/*******************************************************************************
* 文 件 名: 策略模式.cpp
* 文件描述: 定义一系列算法，将每个算法封装起来，并使它们可以互换。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.18
* 修改日期：2025.07.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class Strategy {
public:
    virtual int execute(int a, int b) = 0;
    virtual ~Strategy() = default;
};

class AddStrategy : public Strategy {
public:
    int execute(int a, int b) override { return a + b; }
};

class SubtractStrategy : public Strategy {
public:
    int execute(int a, int b) override { return a - b; }
};

class Context {
private:
    Strategy* strategy;
public:
    Context(Strategy* s) : strategy(s) {}
    int executeStrategy(int a, int b) { return strategy->execute(a, b); }
};

int main(int argc, char *argv[])
{
    return 0;
}