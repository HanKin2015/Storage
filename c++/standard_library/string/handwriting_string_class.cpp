/*******************************************************************************
* 文 件 名: handwriting_string_class.cpp
* 文件描述: 包含了基本的字符串操作功能，如构造、析构、拷贝、赋值、拼接、比较等
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <cstring>
#include <iostream>

class String {
private:
    char* data;  // 存储字符串数据
    size_t length;  // 字符串长度（不包含'\0'）

public:
    // 1. 默认构造函数
    String() : data(new char[1]), length(0) {
        data[0] = '\0';  // 空字符串以'\0'结尾
    }

    // 2. 从C风格字符串构造
    String(const char* str) {
        if (str == nullptr) {  // 处理空指针
            length = 0;
            data = new char[1];
            data[0] = '\0';
        } else {
            length = std::strlen(str);
            data = new char[length + 1];  // 预留'\0'位置
            std::strcpy(data, str);
        }
    }

    // 3. 拷贝构造函数（深拷贝）
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

    // 4. 移动构造函数（C++11）
    String(String&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;  // 原对象不再持有资源
        other.length = 0;
    }

    // 5. 析构函数
    ~String() {
        delete[] data;  // 释放动态分配的内存
    }

    // 6. 拷贝赋值运算符（深拷贝）
    String& operator=(const String& other) {
        if (this != &other) {  // 避免自赋值
            delete[] data;  // 释放当前资源
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    // 7. 移动赋值运算符（C++11）
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;  // 释放当前资源
            data = other.data;
            length = other.length;
            other.data = nullptr;  // 原对象不再持有资源
            other.length = 0;
        }
        return *this;
    }

    // 8. 获取字符串长度
    size_t size() const {
        return length;
    }

    // 9. 获取C风格字符串
    const char* c_str() const {
        return data;
    }

    // 10. 字符串拼接（成员函数版）
    String& operator+=(const String& other) {
        char* new_data = new char[length + other.length + 1];
        std::strcpy(new_data, data);
        std::strcat(new_data, other.data);
        delete[] data;
        data = new_data;
        length += other.length;
        return *this;
    }

    // 11. 字符串比较
    bool operator==(const String& other) const {
        if (length != other.length) return false;
        return std::strcmp(data, other.data) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    // 12. 下标访问（读写）
    char& operator[](size_t index) {
        if (index >= length) {
            throw std::out_of_range("String index out of range");
        }
        return data[index];
    }

    // 13. 下标访问（只读）
    const char& operator[](size_t index) const {
        if (index >= length) {
            throw std::out_of_range("String index out of range");
        }
        return data[index];
    }

    // 14. 输出运算符重载（友元函数）
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    }

    // 15. 输入运算符重载（友元函数）
    friend std::istream& operator>>(std::istream& is, String& str) {
        char buffer[1024];  // 临时缓冲区
        is >> buffer;  // 读取到空格或换行停止
        str = String(buffer);  // 利用赋值运算符
        return is;
    }
};

// 16. 字符串拼接（非成员函数版）
String operator+(const String& lhs, const String& rhs) {
    String result = lhs;  // 利用拷贝构造
    result += rhs;  // 调用成员函数版+=
    return result;
}

int main()
{
    String s1("Hello");
    String s2 = "World";  // 隐式转换（从const char*构造）
    String s3 = s1 + " " + s2;  // 字符串拼接

    std::cout << s3 << " (length: " << s3.size() << ")" << std::endl;  // 输出：Hello World (length: 11)

    if (s1 != s2) {
        std::cout << s1 << " is not equal to " << s2 << std::endl;
    }

    String s4;
    std::cout << "Enter a string: ";
    std::cin >> s4;  // 输入字符串
    std::cout << "You entered: " << s4 << std::endl;

    return 0;
}