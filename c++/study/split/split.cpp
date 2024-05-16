/*******************************************************************************
* 文 件 名: split.cpp
* 文件描述: split函数实现
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.05.15
* 修改日期：2024.05.15
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    std::string str = "Hello,World,!";
    std::vector<std::string> result = split(str, ',');
    for (const auto& token : result) {
        std::cout << token << std::endl;
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ a.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
Hello
World
!
*/