#include <iostream>
#include <cstring>

struct MyStruct {
    int a;
    double b;
    char c[20];
};

int main()
{
    MyStruct s1 = {1, 2.5, "Hello"};
    MyStruct s2 = s1; // 浅拷贝

    std::cout << "s1: " << s1.a << ", " << s1.b << ", " << s1.c << std::endl;
    std::cout << "s2: " << s2.a << ", " << s2.b << ", " << s2.c << std::endl;

    return 0;
}
