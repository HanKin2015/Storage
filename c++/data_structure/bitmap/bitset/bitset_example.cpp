/**
* 文 件 名: bitset_example.cpp
* 文件描述: 学习functional库
* 备    注：g++ functional_example1.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2022.06.05
* 修改日期：2023.06.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <iostream>
#include <bitset>

using namespace std;

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
