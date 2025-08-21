/*******************************************************************************
* 文 件 名: syntactic_sugar.cpp
* 文件描述: Modern C++ 大大提高了开发效率，说下提升开发效率的一些语法糖
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.21
* 修改日期：2025.08.21
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <tuple>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

// 1. if/switch 初始化语句
void if_switch()
{
    std::cout << __LINE__ << __func__ << std::endl;
    // before
    auto *tmp1 = new int();
    if (tmp1 != nullptr) {
        std::cout << "before" << std::endl;
    }
    // after
    if (auto *tmp2 = new int(); tmp2 != nullptr) {
        std::cout << "after" << std::endl;
    }
}

// 2. 结构化绑定
std::tuple<int, std::string> nextToken()
{
    return {4, "fallthrough"};
}
void structured_binding()
{
    std::cout << __LINE__ << __func__ << std::endl;
    //before
    auto token = nextToken();
    std::cout<<std::get<int>(token) << ", " << std::get<std::string>(token) << std::endl;

    //after
    auto[tokenType, lexeme] = nextToken();
    std::cout << tokenType << ", " << lexeme << std::endl;
}

// 3. std::string_view
//before
void isKeyword1(const std::string & lit)
{
    std::cout << __LINE__ << __func__ << std::endl;
}
//after
void isKeyword2(std::string_view lit)
{
    std::cout << __LINE__ << __func__ << std::endl;
}
void string_view_example()
{
    std::cout << __LINE__ << __func__ << std::endl;
    isKeyword1("hello");
    isKeyword2("world");
}

// 4. 内联变量
// inline关键字不能用于块作用域（如函数内部、代码块内）声明的变量。
// inline用于修饰全局或命名空间作用域的变量，或类的成员变量，目的是允许变量在多个翻译单元中定义而不引发重定义错误。
inline int k = 10; // 不需要为一个简单的变量分一个.cpp写定义了
void inline_variable()
{
    std::cout << "k = " << k << std::endl;
}

// 5. 折叠表达式和泛型lambda
void folding_expression()
{
    const char x = 'E';
    //before
    if (x == 'x' || x == 'X' || x == 'e' || x == 'E' || x == '.' ) {
        std::cout << "yes1" << std::endl;
    }

    //after
    static auto anyone = [](auto&& k, auto&&... args) ->bool { return ((args == k) || ...); };
    if (anyone(x, 'x', 'X', 'e', 'E', '.')) {
        std::cout << "yes2" << std::endl;
    }
}

// 6. 继承构造函数
struct Base {
    Base(int a,char b,double c, std::string d,float f)
    :a(a),b(b),c(c),d(std::move(d)),f(f){}

    int a;
    char b;
    double c;
    std::string d;
    float f;
};

//before
struct Derive1 : public Base
{
    Derive1(int a, char b, double c, std::string d, float f): Base(a, b, c, d, f) {}
};

//after
struct Derive2 : public Base
{
    using Base::Base;
};

void sequent_structure()
{
    Base obj1 = Derive1{1, '2', 3, "4", 5};
    std::cout << obj1.a << obj1.b << obj1.c << obj1.d << obj1.f << std::endl;

    Base obj2 = Derive2{1, '2', 3, "4", 5};
    std::cout << obj2.a << obj2.b << obj2.c << obj2.d << obj2.f << std::endl;
}

// 7. +lambda转换对lambda使用一元+表达式可以将它转换为普通函数指针
void advanced_lambda()
{
    // before 
    int8_t (*CreateLonglink1)(const std::string& name, const std::string& host,
    const std::vector<uint16_t> ports, const std::string& debugip)
    = +[](const std::string& name,
                            const std::string& host,
                            const std::vector<uint16_t> ports,
                            const std::string& debugip) ->int8_t {
    
        std::cout << "hello1" << std::endl;
        return 0;
    };
    // after
    auto CreateLonglink2 = +[](const std::string& name,
                            const std::string& host,
                            const std::vector<uint16_t> ports,
                            const std::string& debugip) ->int8_t {
    
        std::cout << "hello2" << std::endl;
        return 0;
    };
}

int main()
{
    if_switch();
    structured_binding();
    string_view_example();
    inline_variable();
    sequent_structure();
    advanced_lambda();
    return 0;
}