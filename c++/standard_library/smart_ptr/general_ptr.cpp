/**
* 文 件 名: general_ptr.cpp
* 文件描述: 普通指针存在的问题
* 作    者: HanKin
* 创建日期: 2022.07.15
* 修改日期：2023.08.21
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
 
int main(int argc, char *argv[])
{
    std::string *p1 = new std::string("I reigned lonely as a cloud.");
    std::cout << *p1 << std::endl;
    
    std::shared_ptr<std::string> ps(new std::string ("I reigned lonely as a cloud."));
    std::cout << *ps << std::endl;

    int *null_up1;
    null_up1 = new int(3);
    printf("null_up1 = %d\n", *null_up1);
    
    std::shared_ptr<int> null_up2;
    //null_up2 = new int(3);    // 编译不通过，不支持这种赋值
    printf("null_up2 = %d\n", *null_up2);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ k.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
I reigned lonely as a cloud.
I reigned lonely as a cloud.
[root@ubuntu0006:~/cmake] #cppcheck k.cpp
Checking k.cpp...
[k.cpp:23]: (error) Memory leak: p1
*/
