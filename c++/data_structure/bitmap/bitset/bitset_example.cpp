/**
* 文 件 名: bitset_example.cpp
* 文件描述: 学习bitset
* 备    注：g++ bitset_example.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2022.06.05
* 修改日期：2023.06.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <iostream>
#include <bitset>
using namespace std;

void bitset_example1()
{
    // 创建一个大小为8的bitset，初始值为0
    std::bitset<8> b1;
    std::cout << "b1: " << b1 << std::endl; // 输出: 00000000

    // 使用整数初始化bitset
    std::bitset<8> b2(42);
    std::cout << "b2: " << b2 << std::endl; // 输出: 00101010

    // 使用字符串初始化bitset
    std::bitset<8> b3("1100");
    std::cout << "b3: " << b3 << std::endl; // 输出: 00001100

    return 0;
}

void bitset_example2()
{
    std::bitset<8> b(42); // 00101010

    // 访问位
    std::cout << "Bit 1: " << b[1] << std::endl; // 输出: 1
    std::cout << "Bit 3: " << b[3] << std::endl; // 输出: 0

    // 修改位
    b.set(3); // 将第3位置为1
    std::cout << "After set(3): " << b << std::endl; // 输出: 00111010

    b.reset(1); // 将第1位置为0
    std::cout << "After reset(1): " << b << std::endl; // 输出: 00111000

    b.flip(0); // 翻转第0位
    std::cout << "After flip(0): " << b << std::endl; // 输出: 00111001
    
    return 0;
}

void bitset_example3()
{
    std::bitset<8> b1(42); // 00101010
    std::bitset<8> b2(15); // 00001111

    // 按位与
    std::bitset<8> b_and = b1 & b2;
    std::cout << "b1 & b2: " << b_and << std::endl; // 输出: 00001010

    // 按位或
    std::bitset<8> b_or = b1 | b2;
    std::cout << "b1 | b2: " << b_or << std::endl; // 输出: 00101111

    // 按位异或
    std::bitset<8> b_xor = b1 ^ b2;
    std::cout << "b1 ^ b2: " << b_xor << std::endl; // 输出: 00100101

    // 按位取反
    std::bitset<8> b_not = ~b1;
    std::cout << "b1 ~: " << b_not << std::endl; // 输出: 11010101

    return 0;
}

void bitset_example4()
{
    std::bitset<8> b(42); // 00101010

    // 转换为字符串
    std::string str = b.to_string();
    std::cout << "String: " << str << std::endl; // 输出: 00101010

    // 转换为整数
    unsigned long num = b.to_ulong();
    std::cout << "Number: " << num << std::endl; // 输出: 42

    return 0;
}

int main()
{
    // 创建一个二进制位集合，初始值为1010
    bitset<4> bits("1010");

    // 输出二进制位集合
    cout << "bits: " << bits << endl;

    // 将第0位和第2位设置为1
    bits.set(0);
    bits.set(2);

    // 输出修改后的二进制位集合
    cout << "bits: " << bits << endl;

    // 将第1位和第3位取反
    bits.flip(1);
    bits.flip(3);

    // 输出修改后的二进制位集合
    cout << "bits: " << bits << endl;

    // 输出二进制位集合中1的个数
    cout << "count: " << bits.count() << endl;

    // 输出二进制位集合的大小
    cout << "size: " << bits.size() << endl;

    // 输出第3位的值
    cout << "bit 3: " << bits[3] << endl;

    return 0;
}
/*
bits: 1010
bits: 1111
bits: 0101
count: 2
size: 4
bit 3: 0
*/
