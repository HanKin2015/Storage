/*******************************************************************************
* 文 件 名: factory_pattern.cpp
* 文件描述: 完美的工厂函数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.12
* 修改日期：2025.08.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <utility> // For std::forward
#include <iostream>

struct MyClass {
    /**
     * @brief Default constructor.
     */
    MyClass() { std::cout << "Default constructor\n"; }
    /**
     * @brief Copy constructor.
     * @param other The object to be copied.
     */
    MyClass(const MyClass&) { std::cout << "Copy constructor\n"; }
    /**
     * @brief Move constructor.
     * @param other The object to be moved.
     */
    MyClass(MyClass&&) noexcept { std::cout << "Move constructor\n"; }
};

/**
 * @brief A factory function that perfectly forwards arguments to a constructor.
 * @tparam T The type of object to create.
 * @tparam Args The types of arguments for the constructor.
 * @param args The arguments to forward.
 * @return A pointer to the newly created object.
 */
template<typename T, typename... Args>
T* factory(Args&&... args) {
    // std::forward is used here to preserve the value category of each argument.
    return new T(std::forward<Args>(args)...);
}

int main()
{
    std::cout << "Creating with rvalue:\n";
    MyClass* p1 = factory<MyClass>(MyClass()); // Calls Move constructor

    std::cout << "\nCreating with lvalue:\n";
    MyClass obj;
    MyClass* p2 = factory<MyClass>(obj); // Calls Copy constructor
    
    delete p1;
    delete p2;
    return 0;
}