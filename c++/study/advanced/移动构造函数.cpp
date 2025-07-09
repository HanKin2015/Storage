/*******************************************************************************
* 文 件 名: 移动构造函数.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.09
* 修改日期：2025.07.09
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstring>

class MyString {
private:
    char* data;
    size_t length;
public:
    // 深拷贝构造函数（传统方式）
    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);  // 深拷贝，开销大
    }

    // 移动构造函数（C++11）
    MyString(MyString&& other) noexcept {
        length = other.length;
        data = other.data;         // 直接接管资源
        other.data = nullptr;      // 防止析构时释放资源
        other.length = 0;
    }
};

// 使用右值引用接收临时对象
std::string getString() {
    return "temp";
}

int main()
{
	std::string&& rref = getString();  // 绑定到返回的临时对象
	return 0;
}