/*******************************************************************************
* 文 件 名: callback_function.c
* 文件描述: 回调函数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2023.11.30
* 修改日期：2023.11.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

void handle_event(int event_type, void (*callback)(void))
{
    printf("event %d occurred\n", event_type);

    if (callback)
    {
        callback();
    }
}

void callback_function()
{
    printf("callback function called\n");
}

int main()
{
    handle_event(1, callback_function);
    handle_event(2, NULL);
    return 0;
}
/*
event 1 occurred
callback function called
event 2 occurred
*/