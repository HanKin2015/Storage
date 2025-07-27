# 容器

[一万五千字C++STL【容器】详解](https://mp.weixin.qq.com/s/3eXNv6XMAdvc-ChGLtLPGw)

## 1、emplace_back和push_back区别
emplace_back和push_back都是向C++容器中添加元素的方法，但它们的实现方式略有不同。

push_back方法接受一个元素作为参数，并将该元素的副本添加到容器的末尾。如果容器存储的是对象类型，那么该元素将被复制一次，这可能会导致额外的开销。

emplace_back方法接受与容器中存储的元素类型相对应的构造函数参数，并在容器的末尾直接构造一个新元素。这意味着不需要进行额外的复制操作，因此可以更高效地添加元素。

总的来说，如果你需要向容器中添加一个已经存在的对象，那么使用push_back方法；如果你需要构造一个新的对象并将其添加到容器中，那么使用emplace_back方法。

## 2、c++中map、multimap、unordered_map、unordered_multimap的区别
https://blog.csdn.net/lyn631579741/article/details/122052598

## 3、rbegin\cbegin\begin 的区别
begin()返回一个指向容器第一个元素的迭代器（iterator）
cbegin()返回一个指向容器第一个元素的常量迭代器（const_iterator）不允许修改容器中的元素，只能用于读取
rbegin()返回一个反向指向容器第一个元素的迭代器（iterator）

## 4、vec.at(1) 和 vec[1] 的区别
vec.at(1):
- 是一个成员函数，提供边界检查。
- 如果索引超出范围，会抛出 std::out_of_range 异常。
- 适合在需要安全访问元素的情况下使用。

vec[1]:
- 是一个运算符重载，直接访问元素。
- 不进行边界检查，如果索引超出范围，行为是未定义的（可能导致程序崩溃或访问非法内存）。
- 适合在你确定索引有效的情况下使用。

## 5、vector容器没法进行查找成员变量是否存在吗
它并不直接支持查找成员变量是否存在的功能。要在 std::vector 中查找特定的成员变量，通常需要使用标准库算法或手动遍历。
```
auto it = std::find_if(people.begin(), people.end(), [](const Person& p) {
    return p.name == "Bob";
});

if (it != people.end()) {
    std::cout << "Found: " << it->name << ", Age: " << it->age << std::endl;
}
```
考虑使用 std::unordered_set 或 std::set 来存储该成员变量的值。这些容器提供了更快的查找性能。

## 6、erase删除不存在的元素会有异常吗
使用 erase 方法删除一个不存在的元素不会引发异常。std::set 的 erase 方法会安全地处理这种情况。

erase 方法的行为
- 删除存在的元素：如果指定的元素存在于 std::set 中，erase 方法将删除该元素，并返回 1（表示成功删除）。
- 删除不存在的元素：如果指定的元素不存在于 std::set 中，erase 方法将不会做任何操作，并返回 0（表示没有元素被删除）。

## 7、如果一个类成员是set类型，需要在构造函数中初始化为空吗
通常不需要在构造函数中显式地将其初始化为空。std::set 会在默认构造时自动初始化为空集合。

```
#include <iostream>
#include <set>

class MyClass {
public:
    std::set<int> mySet; // 默认初始化为空

    MyClass() : mySet() { // 显式初始化为空
        // 也可以在这里进行其他初始化
    }
};
```
如果你需要使用 std::set 的特定构造函数（例如，指定比较器或初始元素），则需要显式初始化。

## 8、不同容器的迭代器类型
随机访问迭代器：vector、deque 容器的迭代器属于此类，支持随机访问，能直接通过下标快速访问任意元素位置。
无迭代器：stack、queue、priority_queue 这几种容器没有迭代器，它们主要通过特定的接口（如 push、pop 等）来操作元素，不支持迭代器遍历。
双向迭代器：list、(multi)set、(multi)map 的迭代器为双向迭代器，只能进行双向移动（++、--），无法直接随机访问元素。
前向迭代器：unordered_(multi)set、unordered_(multi)map 以及 forward_list 的迭代器属于前向迭代器，只能单向向前移动来遍历元素。
