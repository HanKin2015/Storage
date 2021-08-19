/*
derived：派生的，衍生的
*/

#include <iostream>
#include <typeinfo>
#include <string>
#include <cxxabi.h>
using namespace std;

class base
{
public: 
    base()
    {
        //cout << "base~~~" << endl;
    }
    
    virtual ~base()
    {

    }
    virtual void print()
    {
        cout << "we are in base" << endl;
    }
    
protected:
private:
};

class derived : public base
{
public:
    void print()
    {
        cout << "we are in derived" << endl;
    }
protected:
private:
};

/*
学习typeid函数
*/
static void study_typeid()
{
    int    a;
    char   b;
    short  c;
    string d;
    
    // 只输出一个字符
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;
    
    // 解决只输出一个字符问题
    cout << abi::__cxa_demangle(typeid(a).name(), 0, 0, 0) << endl;
    cout << abi::__cxa_demangle(typeid(b).name(), 0, 0, 0) << endl;
    cout << abi::__cxa_demangle(typeid(c).name(), 0, 0, 0) << endl;
    cout << abi::__cxa_demangle(typeid(d).name(), 0, 0, 0) << endl;
    return;
}

/*
dynamic_cast转换操作符在执行类型转换时首先将检查能否成功转换，如果能成功转换则转换之，如果转换失败，如果是指针则反回NULL，如果是转换的是引用，则抛出一个bad_cast异常。
*/
static void quote_transfer()
{
    // 1.引用的向上转换总是安全的
    derived c;
    derived &der2 = c;
    base &base2 = dynamic_cast<base &>(der2);   // 向上转换，安全
    base2.print();  // 特别有意思，转换后居然输出是we are in derived
    
    // 2.安全的向下转型
    // 第一种情况，转换成功
    derived b;
    base &base1 = b;
    derived &der1 = dynamic_cast<derived &>(base1);
    cout<<"第一种情况：";
    der1.print();

    // 第二种情况
    base a ;
    base &base = a;
    cout << "第二种情况：";
    try {
        derived & der = dynamic_cast<derived &>(base);
    } catch (bad_cast) {
        cout << "转化失败,抛出bad_cast异常" << endl;
    }
    return;
}

/*
指针转换抛出异常情况

0x615030
wrong
0x615050
success
0x615070
success

Program received signal SIGSEGV, Segmentation fault.
0x00007ffff7ae0f93 in __dynamic_cast () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
(gdb) bt
#0  0x00007ffff7ae0f93 in __dynamic_cast () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
#1  0x0000000000400fd3 in gdb (arg1=0x615030, arg2=0x615050) at study_dynamic_cast.cpp:83
#2  0x000000000040125e in main () at study_dynamic_cast.cpp:130
(gdb) f 1
#1  0x0000000000400fd3 in gdb (arg1=0x615030, arg2=0x615050) at study_dynamic_cast.cpp:83
83          derived *tmp = dynamic_cast<derived *>(arg1);
(gdb) p arg1
$1 = (base *) 0x615030
(gdb) p arg2
$2 = (base *) 0x615050
(gdb) p *arg2
$3 = {_vptr.base = 0x4017a0 <vtable for derived+16>}
(gdb) p *arg1
$4 = {_vptr.base = 0x0}
(gdb)
*/
static void gdb(base *arg1, base *arg2)
{
    if (arg1 == NULL || arg2 == NULL) {
        cout << "arg is NULL" << endl;
        return;
    }
    
    derived *tmp = dynamic_cast<derived *>(arg1);
    if (tmp == NULL) {
        cout << "wrong" << endl;
    } else {
        cout << "success" << endl;
    }
    return;
}

/*
指针转换
*/
static void pointer_transfer(base *base_ptr)
{
    derived *derived_ptr = dynamic_cast<derived *>(base_ptr);
    
    if (derived_ptr == NULL) {
        cout << typeid(*base_ptr).name() << " to base can be dynamic_cast to derived pointer is failed" << endl;
    } else {
        cout << typeid(*base_ptr).name() << " to base can be dynamic_cast to derived pointer is success" << endl;
    }
}

int main()
{
    study_typeid();
    
    cout << endl;
    base *base_ptr1 = new base;
    cout << typeid(*base_ptr1).name() << endl;                  // 注意这里需要添加*
    derived *derived_ptr1 =  dynamic_cast<derived*>(base_ptr1); //base_ptr1实际指向base，不能转化为derived
    
    base *base_ptr2 = new derived;
    cout << typeid(*base_ptr2).name() << endl;
    derived *derived_ptr2 = dynamic_cast<derived*>(base_ptr2);  //base_ptr1实际指向derived，能转化为derived
    
    derived *derived_ptr3 = new derived;
    base *base_ptr3 = dynamic_cast<base*>(derived_ptr3);
    
    if (derived_ptr1 == NULL) {
        cout << "base pointer pointed to base can be dynamic_cast to derived pointer is failed" << endl;
    } else {
        cout << "pointer to base can be dynamic_cast to derived pointer  is success" << endl;
    }

    if (derived_ptr2 == NULL) {
        cout << "base pointer pointed to derived can be dynamic_cast to derived pointer is failed" << endl;
    } else {
        cout << "base pointer pointed to derived can be dynamic_cast to derived pointer is success" << endl;
    }
    
    if (derived_ptr3 == NULL) {
        cout << "base pointer pointed to base can be dynamic_cast to base pointer is failed" << endl;
    } else {
        cout << "base pointer pointed to base can be dynamic_cast to base pointer is success" << endl;
    }
    
    cout << endl;
    pointer_transfer(base_ptr1);
    pointer_transfer(base_ptr2);
    pointer_transfer(base_ptr3);
    
    delete base_ptr1;   // 释放内存后不置为NULL则变成野指针，不使用没有啥影响，使用就会出现问题，无法对其进行判断
    //gdb(base_ptr1, base_ptr2);
    
    cout << endl;
    quote_transfer();
    return 0;
}

/*
运行结果：

i
c
s
NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
int
char
short
std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >

4base
7derived
base pointer pointed to base can be dynamic_cast to derived pointer is failed
base pointer pointed to derived can be dynamic_cast to derived pointer is success
base pointer pointed to base can be dynamic_cast to base pointer is success

4base to base can be dynamic_cast to derived pointer is failed
7derived to base can be dynamic_cast to derived pointer is success
7derived to base can be dynamic_cast to derived pointer is success

we are in derived
第一种情况：we are in derived
第二种情况：转化失败,抛出bad_cast异常
*/