[虚函数与纯虚函数的部分说明](https://zhuanlan.zhihu.com/p/506896264)

静态成员函数和非静态成员函数的主要区别在于它们是否拥有`this`指针。

静态成员函数：
不包含`this`指针，因此不能直接访问对象的成员函数。
通常用于操作类的静态数据成员，如常量、计数器等，这些数据成员对所有对象来说是共享的，不会占用每个对象的空间。
可以被类名 `::` 或对象名调用，不需要指定具体的对象实例。

非静态成员函数：
包含`this`指针，允许访问对象的成员函数。
对于每个单独的对象，该函数都有一个与之对应的副本，即函数调用时会传递当前对象的指针作为参数。
可以在代码中使用`this`指针来间接访问到对象的私有数据和方法。
总结来说，静态成员函数主要用于访问类和对象的公共数据成员，而非静态成员函数则是为了访问特定对象的私有数据和方法

这其中一点就可以看看虚表指针。




