/**
* 文 件 名: unique_ptr_error_eaxmple.cpp
* 文件描述: error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(...
* 编    译: g++ unique_ptr_error_eaxmple.cpp -std=c++11
* 备    注: https://zhuanlan.zhihu.com/p/359964081
* 作    者: HanKin
* 创建日期: 2022.07.11
* 修改日期：2022.07.11
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <memory>
#include <iostream>

//用于测试错误的类
class TestClass
{
public:
    int value_ = 0;
};

//用来测试传入unique_ptr的函数
void testPtrFunction(std::unique_ptr<TestClass> ptrHandle)
{
    //输出指针里面的内容
    std::cout << ptrHandle->value_ << std::endl;
    return;
}

int main()
{
    //新建一个智能指针
    std::unique_ptr<TestClass> testPtr(new TestClass());
    //设置里面的数值
    testPtr->value_ = 10;
    testPtrFunction(testPtr);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ k.cpp -std=c++11
k.cpp: In function ‘int main()’:
k.cpp:37:28: error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = TestClass; _Dp = std::default_delete<TestClass>]’
     testPtrFunction(testPtr);
                            ^
In file included from /usr/include/c++/5/memory:81:0,
                 from k.cpp:13:
/usr/include/c++/5/bits/unique_ptr.h:356:7: note: declared here
       unique_ptr(const unique_ptr&) = delete;
       ^
k.cpp:24:6: note:   initializing argument 1 of ‘void testPtrFunction(std::unique_ptr<TestClass>)’
 void testPtrFunction(std::unique_ptr<TestClass> ptrHandle)
      ^
*/