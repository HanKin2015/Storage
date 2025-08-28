/*******************************************************************************
* 文 件 名: delete_memory_leak.cpp
* 文件描述: 当我们使用delete[]来释放通过new[]分配的数组内存时，它会从内存块的起始位置向前偏移 4 个字节（因为之前new[]分配内存时，在实际数据内存块前多分配了 4 个字节来记录数组元素个数） 。通过读取这 4 个字节中的内容，delete[]就能准确得知数组中元素的个数。知道了元素个数，delete[]就可以按照正确的次数调用数组中每个元素的析构函数，将每个元素占用的资源都清理干净。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.25
* 修改日期：2025.08.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructor" << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destructor" << std::endl;
    }
};
int main()
{
    MyClass* arr = new MyClass[3];// 使用new[]分配包含3个MyClass对象的数组
    // 这里可以对arr数组进行操作
    delete arr; // 使用delete[]释放数组内存
    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp 
root@hankin:~/opencv# ./a.out 
MyClass constructor
MyClass constructor
MyClass constructor
MyClass destructor
MyClass destructor
MyClass destructor
root@hankin:~/opencv# g++ main.cpp 
root@hankin:~/opencv# ./a.out 
MyClass constructor
MyClass constructor
MyClass constructor
MyClass destructor
munmap_chunk(): invalid pointer
已中止 (核心已转储)
*/