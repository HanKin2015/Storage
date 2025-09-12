/*******************************************************************************
* 文 件 名: class_enum_type_control.cpp
* 文件描述: 类枚举底层类型控制
* 备    注: 普通枚举的底层整数类型由编译器决定（通常是 int），无法显式指定；类枚举可以显式指定底层类型（如 uint8_t、int32_t），便于控制内存占用和跨平台兼容性。
* 作    者: HanKin
* 创建日期: 2025.09.10
* 修改日期：2025.09.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdint>

// 底层类型为 uint8_t（1字节），适用于存储紧凑性要求高的场景
enum class SmallEnum : uint8_t {
    A, B, C
};

// 底层类型为 int64_t（8字节），适用于需要大值的场景
enum class LargeEnum : int64_t {
    X = 1000000000000,
    Y = 2000000000000
};

void class_enum()
{
    SmallEnum s = SmallEnum::B;
    int x = static_cast<int>(s);  // 需显式转换，明确表达意图
    std::cout << x << std::endl;
}

int main()
{
    class_enum();
    return 0;
}