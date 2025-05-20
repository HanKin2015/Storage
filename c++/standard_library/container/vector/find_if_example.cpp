/*******************************************************************************
* 文 件 名: find_if_example.cpp
* 文件描述: 使用 std::find_if 函数来查找满足特定条件的元素
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.20
* 修改日期：2025.05.20
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

int main()
{
    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };

    // 查找名字为 "Bob" 的人
    auto it = std::find_if(people.begin(), people.end(), [](const Person& p) {
        return p.name == "Bob";
    });

    if (it != people.end()) {
        std::cout << "Found: " << it->name << ", Age: " << it->age << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ find_if_example.cpp
[root@ubuntu0006:~/cmake] #./a.out
Found: Bob, Age: 25
*/