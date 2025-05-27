/*******************************************************************************
* 文 件 名: shared_ptr_copy.cpp
* 文件描述: 拷贝引用
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.23
* 修改日期：2025.05.23
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>

int main()
{
    std::shared_ptr<std::string> ps(new std::string("I reigned lonely as a cloud."));
    std::shared_ptr<std::string> vocation;
    vocation = ps;
    
    printf("%p %p\n", ps, vocation);
    printf("%p %p\n", ps.get(), vocation.get());
    
    std::cout << *vocation << std::endl;
    std::cout << *ps << std::endl;
    
    *vocation = "hahah";
    std::cout << *vocation << std::endl;
    std::cout << *ps << std::endl;

    
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
0x7ffdb666f9b0 0x7ffdb666f9a0
0x1ce5c20 0x1ce5c20
I reigned lonely as a cloud.
I reigned lonely as a cloud.
hahah
hahah
*/