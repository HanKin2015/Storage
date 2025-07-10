/*******************************************************************************
* 文 件 名: TMP_example.cpp
* 文件描述: 模板递归展开：GenerateArray<5> 展开为 GenerateArray<4, 4> → GenerateArray<3, 3, 4> → ... → GenerateArray<0, 0, 1, 2, 3, 4>
* 备    注: 模板实例化发生在编译期，而 std::cout 是运行时操作。因此无法添加std::cout语句
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// 编译期生成数组初始化
template <int... Values>
struct Array {
    static constexpr int data[] = {Values...};
};

// 在类外定义静态成员数组
//template <int... Values>
//constexpr int Array<Values...>::data[];

// 递归生成数组（移除 std::cout）
template <int N, int... Values>
struct GenerateArray : GenerateArray<N-1, N-1, Values...> {
	// 触发编译期错误，显示当前实例化的模板参数
    // 注意：取消注释会导致编译失败，仅用于调试
    // static_assert(N == -1, "Debugging template instantiation");
};

// 终止条件
template <int... Values>
struct GenerateArray<0, Values...> {
    using type = Array<Values...>;
};

// 模板函数获取数组大小
template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept {
    return N;
}

int main()
{
    // 使用
    using MyArray = GenerateArray<5>::type;  // 生成数组 {0, 1, 2, 3, 4}
    
    for (int i = 0; i < array_size(MyArray::data); i++) {
        std::cout << MyArray::data[i] << std::endl;  // 仅在运行时打印
    }
	
	for (int i = 0; i < ARRAY_SIZE(MyArray::data); i++) {
        std::cout << MyArray::data[i] << std::endl;  // 仅在运行时打印
    }
    return 0;
}
/*
0
1
2
3
4
0
1
2
3
4
*/