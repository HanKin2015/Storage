/**
* 文 件 名: shared_ptr.cpp
* 文件描述: 实现shared_ptr指针
* 作    者: HanKin
* 创建日期: 2023.08.21
* 修改日期：2023.08.21
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
using namespace std;

//模板类作为友元时要先有声明
template <typename T> class SmartPtr;
   
//辅助类
template <typename T> class RefPtr {
private:
    //该类成员访问权限全部为private，因为不想让用户直接使用该类
    friend class SmartPtr<T>;      //定义智能指针类为友元，因为智能指针类需要直接操纵辅助类
    
    //构造函数的参数为基础对象的指针
    RefPtr(T *ptr):p(ptr), count(1){}
    
    //析构函数
    ~RefPtr() {
    	delete p;
    }
    
    //引用计数
    int count;   
    
    //基础对象指针
    T *p;                                                      
};

// 智能指针类
template<typename T> class SmartPtr {
public:
	// 构造函数
    SmartPtr(T *ptr):rp(new RefPtr<T>(ptr)){}
    // 拷贝构造函数
    SmartPtr(const SmartPtr<T> &sp):rp(sp.rp) {
    	++rp->count;
    }
    // 重载赋值操作符
    SmartPtr& operator=(const SmartPtr<T>& rhs) {
        ++rhs.rp->count;        //首先将右操作数引用计数加1，
        if (--rp->count == 0)   //然后将引用计数减1，可以应对自赋值
            delete rp;
        rp = rhs.rp;
        return *this;
    }
    // 重载*操作符
    T & operator *() {
        return *(rp->p);
    }
    // 重载->操作符
    T* operator ->() {
        return rp->p;
    }
    // 析构函数
    ~SmartPtr() {
        if (--rp->count == 0) { // 当引用计数减为 0 时，删除辅助类对象指针，从而删除基础对象
        	delete rp;
        } else {
	        cout << "还有" << rp->count << "个指针指向基础对象" << endl;
	    }
    }
private:
    RefPtr<T> *rp;  //辅助类对象指针
};

int main() {
	// 定义一个基础对象类指针
    int* ia = new int(10);
    {
        SmartPtr<int> sptr1(ia);
        cout <<"sptr1:"<<*sptr1<<endl;
        {
            SmartPtr<int> sptr2(sptr1); 
            cout <<"sptr2:"<<*sptr2<<endl;
			*sptr2=5;
            {
                SmartPtr<int> sptr3=sptr1; 
                cout <<"sptr3:"<<*sptr3<<endl;
            }
        }
    }
    // 此时count=0，pa 对象被 delete 掉
    cout << *ia << endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ k.cpp -std=c++14
[root@ubuntu0006:~/cmake] #./a.out
sptr1:10
sptr2:10
sptr3:5
还有2个指针指向基础对象
还有1个指针指向基础对象
0
*/