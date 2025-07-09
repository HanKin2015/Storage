/*******************************************************************************
* 文 件 名: 移动构造函数2.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.09
* 修改日期：2025.07.09
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class MyVector {
private:
    int* data;
    size_t size;  // 新增成员变量，记录元素数量

public:
    // 默认构造函数
    MyVector() : data(nullptr), size(0) { std::cout << "default" << std::endl; }

    // 移动构造函数
    MyVector(MyVector&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;  // 确保源对象状态合法
		std::cout << "move" << std::endl;
    }

    // 析构函数（如果需要管理动态内存）
    ~MyVector() {
        delete[] data;  // 安全释放 nullptr
    }
};

MyVector createVector() {
    return MyVector();
}

int main() {
    MyVector v = createVector();
	std::cout << "separator" << std::endl;
	MyVector vv = MyVector(v);
    return 0;
}