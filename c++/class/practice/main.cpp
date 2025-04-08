/*******************************************************************************
* 文 件 名: main.cpp
* 文件描述: 多态继承重写
* 备    注: 需要指定--std=c++11，并且需要链接class.cpp
* 作    者: HanKin
* 创建日期: 2025.04.07
* 修改日期：2025.04.07
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include "class.h"

int main(int argc, char *argv[])
{
    Student *obj = new Underachiever();
    //Student *obj = new Overachiever();
    obj->init();
    obj->set_school_name();
    obj->print_info();
    obj->print_extra_info();
    return 0;
}
/*
[root@ubuntu0006:/media/vdb] #g++ main.cpp class.cpp --std=c++11
[root@ubuntu0006:/media/vdb] #./a.out
Student
Underachiever
ZhangSan 12 175 1 NEUQ
extra_info: ping-pong
[root@ubuntu0006:/media/vdb] #vi main.cpp
[root@ubuntu0006:/media/vdb] #g++ main.cpp class.cpp --std=c++11
[root@ubuntu0006:/media/vdb] #./a.out
Student
Overachiever
LiSi 31 170 0 NEUQ
extra_info: 1994
*/