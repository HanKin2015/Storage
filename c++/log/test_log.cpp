/**
* 文 件 名: test_log.cpp
* 文件描述: 示例调用log.h文件
* 作    者: HanKin
* 创建日期: 2023.06.19
* 修改日期：2023.06.19
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include "log.h"

int main()
{
    int age = 34;
    LOGI("I am hero, %d", age);
    
    init_log("./test_log.log");
    LOGE("I am hero, %d", age);
    return 0;
}
