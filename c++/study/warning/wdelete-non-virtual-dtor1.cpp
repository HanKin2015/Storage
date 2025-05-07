/*******************************************************************************
* 文 件 名: wdelete-non-virtual-dtor.cpp
* 文件描述: 未使用的类成员是否存在警告
* 备    注: 函数可能在不同的上下文中被调用，或者通过指针、引用等间接方式被调用。编译器在静态分析时，
可能难以准确判断某个私有成员函数是否会在未来的某个地方被使用。编译器在分析代码时，通常会关注变量的使用情况，
因为变量的未使用可能会导致资源浪费或逻辑错误。相比之下，未使用的成员函数可能不会直接影响程序的运行，
尤其是在大型代码库中，未使用的函数可能是为了未来的扩展或维护而保留的。
* 作    者: HanKin
* 创建日期: 2025.04.29
* 修改日期：2025.04.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/

#include <cstdio>
#include <iostream>

class Student {
public:
    Student() {};
    ~Student() {};

    virtual void test()
    {
        printf("hello\n");
        return;
    }
};

int main()
{
    Student* obj = new Student();
    delete obj; // 这一步很重要
    return 0;
}
/*
root@ubuntu0006:~/cmake/advanced/build# g++ k.cpp -Wall -Wextra -Werror
k.cpp:9:20: error: unused parameter ‘_’ [-Werror=unused-parameter]
     void test1(int _)
                    ^
k.cpp: In member function ‘void Student::test2(int)’:
k.cpp:14:20: error: parameter ‘_’ set but not used [-Werror=unused-but-set-parameter]
     void test2(int _)
                    ^
k.cpp: In member function ‘void Student::test3(int)’:
k.cpp:28:20: error: parameter ‘_’ set but not used [-Werror=unused-but-set-parameter]
     void test3(int _)
                    ^
k.cpp: In function ‘int main()’:
k.cpp:38:14: error: unused variable ‘obj’ [-Werror=unused-variable]
     Student* obj = new Student(1, 2, 3);
              ^
cc1plus: all warnings being treated as errors
root@ubuntu0006:~/cmake/advanced/build# clang++ k.cpp -Wall -Wextra -Werror
k.cpp:9:20: error: unused parameter '_' [-Werror,-Wunused-parameter]
    void test1(int _)
                   ^
k.cpp:38:14: error: unused variable 'obj' [-Werror,-Wunused-variable]
    Student* obj = new Student(1, 2, 3);
             ^
k.cpp:25:9: error: private field 'm_y' is not used [-Werror,-Wunused-private-field]
    int m_y;
        ^
3 errors generated.
*/
