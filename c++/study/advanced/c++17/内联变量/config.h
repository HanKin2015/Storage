#pragma once

#include <string>

// Config.h（头文件，C++17前需在Config.cpp中定义kMaxSize）
// 在 C++ 中，文件作用域的 const 变量默认具有内部链接（internal linkage），即它的可见性仅限于当前编译单元（.cpp 文件）。
// 当你在头文件中定义 const int kMaxSize = 1024; 时，每个包含该头文件的 .cpp 会单独生成一个 kMaxSize 实例，且彼此独立（因为内部链接）。
// 由于这些实例的值相同，且 const 变量通常会被编译器优化为「编译期常量」（直接替换为值），因此链接器不会检测到冲突，编译时可能不报错。
// 去掉inline后能正常编译，但是再去掉const后就会出现重复定义问题
// 增加inline后地址只有一个，但是去掉inline后则变成2个地址
inline const int kMaxSize = 10241; // 内联变量，直接在头文件声明+定义

class MyClass {
public:
    inline static const std::string kClassName = "MyClass"; // 静态内联成员变量
};

// 多个.cpp文件包含Config.h，无需担心kMaxSize重复定义

void config1_print();
void config2_print();