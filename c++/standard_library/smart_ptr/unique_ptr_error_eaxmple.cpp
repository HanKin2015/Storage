/**
* 文 件 名: unique_ptr_error_eaxmple.cpp
* 文件描述: error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(...
* 编    译: g++ unique_ptr_error_eaxmple.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2022.07.11
* 修改日期：2022.07.11
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include<memory>
#include<iostream>

//用于测试错误的类
class TestClass
{
public:
    int value_=0;
};

//用来测试传入unique_ptr的函数
void testPtrFunction(std::unique_ptr<TestClass> ptrHandle)
{
    //输出指针里面的内容
    std::cout<<ptrHandle->value_<<std::endl;
}

int main()
{
    //新建一个智能指针
    std::unique_ptr<TestClass> testPtr(new TestClass());
    //设置里面的数值
    testPtr->value_=10;
    testPtrFunction(testPtr);
    return 0;
}