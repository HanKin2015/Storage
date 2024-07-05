/**
* 文 件 名: strstr_strchr_strrchr_example.cpp
* 文件描述: 学习strstr/strchr/strrchr函数
* 作    者: HanKin
* 创建日期: 2021.08.24
* 修改日期：2022.12.06
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <string>
#include <string.h>
using namespace std;

static int strstr_example()
{
    const char *vmInfo = "<DesktopPolicy EnableVirPrint=\"0\" EnableUSBWrite=\"0\" EnableVideoRedirect=\"1\" EnableFolderRedirect=\"1\">\n"
            "<!-- diskmap policy -->\n"
            "<User><![CDATA[hankin]]></User>\n"
            "<XML><![CDATA[<DiskMapConf LocalDiskRight=\"3\" USBCDRight=\"2\"/>]]></XML>\n"
            "</DesktopPolicy>";

    const char *pos = strstr(vmInfo, "<![CDATA[");
    cout << pos << endl;
    return 0;
}
/*
<![CDATA[hankin]]></User>
<XML><![CDATA[<DiskMapConf LocalDiskRight="3" USBCDRight="2"/>]]></XML>
</DesktopPolicy>
*/

static void strchr_strrchr_example()
{
    const char *s = "hello world";
    // 返回值需要加const否则就会有上面这个错误，函数原型const char * strchr ( const char * str, int character );
    const char *s1 = strchr(s, 'o');    // 正方向第一个匹配
    const char *s2 = strrchr(s, 'o');   // 反方向第一个匹配
    cout << s1 << endl;
    cout << s2 << endl;
    return;
}
/*
o world
orld
*/

int main()
{
    strstr_example();
    strchr_strrchr_example();
    return 0;
}
