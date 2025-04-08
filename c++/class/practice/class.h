/*******************************************************************************
* 文 件 名: class.h
* 文件描述: 多态继承重写
* 备    注: 需要指定--std=c++11
* 作    者: HanKin
* 创建日期: 2025.04.07
* 修改日期：2025.04.07
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#ifndef __CLASS_H__
#define __CLASS_H__

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <stdlib.h>

// 父类
class Student {

public:
    Student(){ printf("%s\n", __FUNCTION__); };
    ~Student(){ printf("%s\n", __FUNCTION__); };

    virtual void init() = 0;
    void set_school_name();
    void print_info();
    virtual void print_extra_info() = 0;

protected:  // 私有成员无法完成继承
    std::string m_name;
    int m_age;
    int m_height;
    int m_sex;
    std::string m_school_name;
};

// 子类1
class Underachiever: public Student {

public:
    Underachiever(){ printf("%s\n", __FUNCTION__); };
    ~Underachiever(){ printf("%s\n", __FUNCTION__); };
    virtual void init() override;
    virtual void print_extra_info() override;

private:
    std::string m_talent;
};

// 子类2
class Overachiever: public Student {

public:
    /*
     * 实例化一个对象，这个无法在父类中实现，error: cannot declare variable ‘instance_’ to be of abstract type ‘Student’
     */
    static Overachiever* instance()
    {
        static Overachiever instance_;
        return &instance_;
    }

    Overachiever(){ printf("%s\n", __FUNCTION__); };
    ~Overachiever(){ printf("%s\n", __FUNCTION__); };
    virtual void init() override;
    virtual void print_extra_info() override;

private:
    int m_birthday;
};

#endif /* __CLASS_H__ */