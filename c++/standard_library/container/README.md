# 容器

[一万五千字C++STL【容器】详解](https://mp.weixin.qq.com/s/3eXNv6XMAdvc-ChGLtLPGw)

## 1、emplace_back和push_back区别
emplace_back和push_back都是向C++容器中添加元素的方法，但它们的实现方式略有不同。

push_back方法接受一个元素作为参数，并将该元素的副本添加到容器的末尾。如果容器存储的是对象类型，那么该元素将被复制一次，这可能会导致额外的开销。

emplace_back方法接受与容器中存储的元素类型相对应的构造函数参数，并在容器的末尾直接构造一个新元素。这意味着不需要进行额外的复制操作，因此可以更高效地添加元素。

总的来说，如果你需要向容器中添加一个已经存在的对象，那么使用push_back方法；如果你需要构造一个新的对象并将其添加到容器中，那么使用emplace_back方法。

## 2、c++中map、multimap、unordered_map、unordered_multimap的区别
https://blog.csdn.net/lyn631579741/article/details/122052598

