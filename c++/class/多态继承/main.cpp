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

int main(int argc, char *argv[])
{
    Student *obj = new Underachiever();
    obj->init();
    obj->set_school_name();
    obj->print_info();
    obj->print_extra_info();
    return 0;
}
