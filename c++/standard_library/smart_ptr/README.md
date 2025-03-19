# 智能指针

[unique_ptr的使用](https://zhuanlan.zhihu.com/p/359964081)

智能指针不支持new分配赋值，否则和普通指针有啥区别。

## 1、 error: ‘make_unique’ is not a member of ‘std’
std::make_unique 是在 C++14 中引入的，因此编译器需要支持 C++14 或更高版本。
```
std::unique_ptr<int> p = std::make_unique<int>(42); // 初始化 unique_ptr
std::unique_ptr<int> p(new int(42)); // 手动创建 unique_ptr
```

