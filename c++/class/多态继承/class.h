/*******************************************************************************
* 文 件 名: read_write.cpp
* 文件描述: 多态继承重写
* 备    注: 
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

class Student {

public:
    /*
     * 实例化一个管理对象
     */
    static Student* instance()
    {
        static Student instance_;
        return &instance_;
    }

    Student(){ printf("%s\n", __FUNCTION__); };
    ~Student(){ printf("%s\n", __FUNCTION__); };

    virtual void init() = 0;
    void set_school_name();
    void print_info();
    virtual void print_extra_info() = 0;

private:
    std::string m_name;
    int m_age;
    int m_height;
    int m_sex;
    std::string m_school_name;
};

class Underachiever: public Student {

public:
    Underachiever(){ printf("%s\n", __FUNCTION__); };
    ~Underachiever(){ printf("%s\n", __FUNCTION__); };
    virtual void init() override;
    virtual void print_extra_info() override;

private:
    std:string m_talent;
};

class Overachiever: public Student {

public:
    Overachiever(){ printf("%s\n", __FUNCTION__); };
    ~Overachiever(){ printf("%s\n", __FUNCTION__); };
    virtual void init() override;
    virtual void print_extra_info() override;

private:
    int m_birthday;
};

#endif /* __CLASS_H__ */