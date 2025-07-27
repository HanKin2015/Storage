/*******************************************************************************
* 文 件 名: make_unique_example.cpp
* 文件描述: 智能指针不能像普通指针那样直接输出地址
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.21
* 修改日期：2025.03.21
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <memory>

template <typename T>
using sp = std::shared_ptr<T>;

template <typename T>
using up = std::unique_ptr<T>;

// 智能指针不能像普通指针那样直接输出地址
void test(up<int> &p)
{
    printf("%p\n", p.get());
    return;
}

/**
 * @brief Bitmap
 */
enum custom_platform {
    CUSTOM_PLATFORM_NONE = 0,
    CUSTOM_PLATFORM_ANDROID_BOX = 0x1,
    CUSTOM_PLATFORM_WINDOWS = 0x2,
    CUSTOM_PLATFORM_DEBIAN_BOX = 0x4,
};
void test_enum_type(unsigned int platform)
{
    printf("hello platform %d\n", platform);
    return;
}

int main()
{
    //up<int> p = std::make_unique<int>(42);  // std::make_unique 是在 C++14 中引入的
    up<int> p(new int(42)); // 手动创建 unique_ptr
    test(p);
    
    int platform_ = 2;
    unsigned int platform = 2;
    if (!(platform_ & platform)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
    
    test_enum_type(CUSTOM_PLATFORM_WINDOWS);
    return 0;
}
