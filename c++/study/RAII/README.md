## 1、RAII简介
在这段代码中，ON_SCOPE_EXIT是一个宏，它定义了一个匿名的类，并在该类的析构函数中执行一些代码。在这种情况下，该类的析构函数会检查config指针是否为非空，如果是，则释放它所指向的内存，并将config指针设置为NULL。因此，当InitClasses函数结束时，无论是通过正常返回还是通过异常，都会自动调用该类的析构函数，从而释放config指向的内存。这种技术被称为“作用域退出”，可以确保在离开当前作用域时执行某些代码，从而避免内存泄漏等问题。

RAII是一种C++编程技术，全称为Resource Acquisition Is Initialization，中文翻译为“资源获取即初始化”。它的核心思想是：在对象的构造函数中获取资源，在对象的析构函数中释放资源。这种技术可以确保资源的正确获取和释放，避免了资源泄漏和错误使用的问题。RAII技术在C++中广泛应用，可以用于管理各种资源，如内存、文件、锁等。

更多详情见：D:\Github\GitBook\gitbook\C++\RAII.md

## 2、深入理解RAII
demo见：D:\Github\Storage\c++\study\RAII\scope_guard2.cpp
```
g++ a.cpp -std=c++11 -fsanitize=address
valgrind --leak-check=full --show-leak-kinds=all ./a.out
```





