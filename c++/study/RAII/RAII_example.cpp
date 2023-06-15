/**
* 文 件 名: RAII_example.cpp
* 文件描述: 使用C++的RAII（资源获取即初始化）技术来确保资源在作用域退出时被正确释放
* 备    注：感觉跟一般的类没有什么区别
* 作    者: HanKin
* 创建日期: 2023.06.14
* 修改日期：2023.06.14
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <fstream>
#include <string>

class File
{
public:
    File(const std::string& filename) : m_file(filename)
    {
        if (!m_file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
    }

    ~File()
    {
        if (m_file.is_open()) {
            m_file.close();
        }
    }

    std::string readLine()
    {
        std::string line;
        std::getline(m_file, line);
        return line;
    }

private:
    std::ifstream m_file;
};

int main()
{
    try {
        File file("example.txt");
        std::string line = file.readLine();
        std::cout << line << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake/hj] #g++ RAII_example.cpp -std=c++11
[root@ubuntu0006:~/cmake/hj] #./a.out
Error: Failed to open file
[root@ubuntu0006:~/cmake/hj] #echo "1234" > example.txt
[root@ubuntu0006:~/cmake/hj] #./a.out
1234
*/
