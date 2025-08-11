/*******************************************************************************
* 文 件 名: weak_ptr_lock_importance.cpp
* 文件描述: weak_ptr使用lock()的重要性
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int id) : id_(id) {
        std::cout << "MyClass " << id_ << " 构造" << std::endl;
    }
    
    ~MyClass() {
        std::cout << "MyClass " << id_ << " 析构" << std::endl;
    }
    
    void doSomething() {
        std::cout << "MyClass " << id_ << " 执行操作" << std::endl;
    }
    
private:
    int id_;
};

// 正确使用weak_ptr的示例
void correctUsage() {
    std::cout << "\n=== 正确使用weak_ptr ===" << std::endl;
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(1);
    std::weak_ptr<MyClass> weakPtr = sharedPtr;
    
    // 正确做法：检查lock()的返回值
    if (auto tempShared = weakPtr.lock()) {
        tempShared->doSomething();
    } else {
        std::cout << "对象已被销毁，无法访问" << std::endl;
    }
    
    // 释放shared_ptr
    sharedPtr.reset();
    
    // 再次尝试访问
    if (auto tempShared = weakPtr.lock()) {
        tempShared->doSomething();
    } else {
        std::cout << "对象已被销毁，无法访问" << std::endl;
    }
}

// 错误使用weak_ptr的示例
void incorrectUsage() {
    std::cout << "\n=== 错误使用weak_ptr ===" << std::endl;
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(2);
    std::weak_ptr<MyClass> weakPtr = sharedPtr;
    
    // 释放shared_ptr，此时对象应该被销毁
    sharedPtr.reset();
    
    // 错误做法：未检查lock()的返回值
    std::shared_ptr<MyClass> tempShared = weakPtr.lock();
    // 这里tempShared是空的，但如果直接使用会导致未定义行为
    if (tempShared) {
        tempShared->doSomething();
    } else {
        std::cout << "对象已被销毁，无法访问" << std::endl;
    }
    
    // 更严重的错误：假设lock()总是返回有效指针
    try {
        // 这行代码在tempShared为空时会导致未定义行为，可能崩溃
        weakPtr.lock()->doSomething();  // 危险！未检查返回值
    } catch (...) {
        std::cout << "访问已销毁对象导致异常" << std::endl;
    }
}

int main() {
    correctUsage();
    incorrectUsage();
    
    return 0;
}
