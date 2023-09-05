/**
* 文 件 名: ref_example.cpp
* 文件描述: ref函数的使用
* 作    者: HanKin
* 创建日期: 2023.09.01
* 修改日期：2023.09.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <mutex>
#include <iostream>
#include <thread>

void increment(int& value)
{
    value++;
    return;
}

int main()
{
    int num = 10;

    std::thread t1(increment, std::ref(num));
    std::thread t2(increment, std::ref(num));
    std::thread t3(increment, num); // 编译不通过

    t1.join();
    t2.join();

    std::cout << "Final num: " << num << std::endl;

    increment(num);
    std::cout << "Final num: " << num << std::endl;
    
    increment(&num);    // 错误，这将会是一个指针
    std::cout << "Final num: " << num << std::endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
Final num: 12
Final num: 13
*/