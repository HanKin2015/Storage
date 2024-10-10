#include <iostream>
#include <cstring>

struct MyStruct {
    int a;
    double b;
    char* c;

    // 构造函数
    MyStruct(int a, double b, const char* str) : a(a), b(b)
    {
        c = new char[strlen(str) + 1];
        strcpy(c, str);
    }

    // 拷贝构造函数（深拷贝）
    MyStruct(const MyStruct& other) : a(other.a), b(other.b)
    {
        c = new char[strlen(other.c) + 1];
        strcpy(c, other.c);
    }

    // 赋值运算符（深拷贝）
    MyStruct& operator=(const MyStruct& other)
    {
        if (this == &other) {
            return *this; // 防止自我赋值
        }

        // 释放已有的内存
        delete[] c;

        // 复制数据
        a = other.a;
        b = other.b;
        c = new char[strlen(other.c) + 1];
        strcpy(c, other.c);

        return *this;
    }

    // 析构函数
    ~MyStruct()
    {
        delete[] c;
    }
};

int main()
{
    MyStruct s1(1, 2.5, "Hello");
    MyStruct s2 = s1; // 深拷贝

    std::cout << "s1: " << s1.a << ", " << s1.b << ", " << s1.c << std::endl;
    std::cout << "s2: " << s2.a << ", " << s2.b << ", " << s2.c << std::endl;

    // 修改 s2 的内容，验证深拷贝
    s2.c[0] = 'h';
    std::cout << "After modification:" << std::endl;
    std::cout << "s1: " << s1.a << ", " << s1.b << ", " << s1.c << std::endl;
    std::cout << "s2: " << s2.a << ", " << s2.b << ", " << s2.c << std::endl;

    return 0;
}
