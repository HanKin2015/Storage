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
#include "class.h"

void Student::set_school_name()
{
    m_school_name = "NEUQ";
}

void print_info()
{
    printf("%s %d %d %d %s\n", m_name.c_str(), m_age, m_height, m_sex, m_school_name.c_str());
}

void Underachiever::init()
{
    m_name = "ZhangSan";
    m_age = 12;
    m_height = 175;
    m_sex = 1;

    m_talent = "ping-pong";
}

void Underachiever::print_extra_info()
{
    printf("extra_info: %s\n", m_talent.c_str());
}

void Overachiever::init()
{
    m_name = "LiSi";
    m_age = 31;
    m_height = 170;
    m_sex = 0;

    m_birthday = 1994;
}

void Overachiever::print_extra_info()
{
    printf("extra_info: %d\n", m_birthday);
}
