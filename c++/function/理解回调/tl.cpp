/*

问：回调函数是否能访问原函数文件中的函数，即me.h文件通过回调函数是否能访问A()
答：可以
问：对于类，将类的成员函数注册到回调函数，是否能访问类的成员变量


*/
#include <iostream>
#include <cstdio>
#include "me.h"

void A()
{
    printf("%s\n", __FUNCTION__);
}

void B(void *priv)
{
    A();
    printf("%s\n", __FUNCTION__);
}

int main()
{
    usbmagic_usb_channel_backend backend;
    backend.priv = NULL;
    backend.writev = B;
    test(backend);
    return 0;
}
