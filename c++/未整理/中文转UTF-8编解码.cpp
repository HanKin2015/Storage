/*
 *
 * URL编码(URL encoding)，也称作百分号编码(Percent-encoding)， 是特定上下文的统一资源定位符 (URL)的编码机制。
 * 编码原理：将需要转码的字符转为16进制，然后从右到左，取4位(不足4位直接处理)，每2位做一位，前面加上%，编码成%XY格式。
 */

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string UTF8_URL_DECODE(string URLcode);
string UTF8_URL_ENCODE(char* Chinese);

string UTF8_URL_DECODE(string URLcode)
{
    //utf-8-> unicode-> 中文
    int len = strlen(URLcode.c_str());
    char* temp = new char[len + 1];
    temp[len] = '\0';
    int temp_pos = 0;

    //去掉%号
    for (int i = 0; i < len; i++) {
        if (URLcode[i] != '%') {
            temp[temp_pos++] = URLcode[i];
        }
    }
    temp[temp_pos] = '\0';
    //cout << temp << endl;
    int temp_len = strlen(temp);
    int UTF8len = temp_len / 2;
    char* UTF8str = new char[UTF8len + 1];
    UTF8str[UTF8len] = '\0';

    //把字符转换成数字，得到真实的UTF8串
    for (int i = 0; i < UTF8len * 2; i+=2) {
        char convert[3] = { 0 };
        convert[0] = temp[i];
        convert[1] = temp[i + 1];
        char *end;
        int tempint = strtol(convert, &end, 16);
        UTF8str[i / 2] = tempint;
    }

    //UTF8转换到UTF16
    int wcslen = ::MultiByteToWideChar(CP_UTF8, NULL, UTF8str, UTF8len, NULL, 0);
    wchar_t* wszString = new wchar_t[wcslen + 1];
    ::MultiByteToWideChar(CP_UTF8, NULL, UTF8str, UTF8len, wszString, wcslen);
    wszString[wcslen] = L'\0';

    //设置区域
    std::wcout.imbue(std::locale("CHS"));
    //wcout << wszString << endl;

    //把wstring 转为 string
    wstring DecodeStr = wszString;
    string OutStr;
    int nLen = (int)DecodeStr.length() * 2;
    OutStr.resize(nLen, ' ');
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)DecodeStr.c_str(), nLen, (LPSTR)OutStr.c_str(), nLen, NULL, NULL);
    delete[]temp;
    delete[]UTF8str;
    delete[] wszString;
    return OutStr;
}

//中文 转为 utf-8
string UTF8_URL_ENCODE(char* Chinese)
{
    //中文 -> unicode  -> utf-8
    wchar_t unicode[128] = { 0 };
    MultiByteToWideChar(CP_ACP, 0, Chinese, strlen(Chinese), unicode, 128);
    unsigned char sz[128] = { 0 };
    WideCharToMultiByte(CP_UTF8, 0, unicode, wcslen(unicode), (LPSTR)sz, 128, 0, 0);
    string EncodeStr;
    char SrcStr[128] = { 0 };
    for (int i = 0; i < 128; i++) {
        if (sz[i] != NULL) {
            sprintf_s(SrcStr, "%%%X", sz[i]);
            EncodeStr += SrcStr;
        }
    }
    transform(EncodeStr.begin(), EncodeStr.end(), EncodeStr.begin(), ::tolower);
    return EncodeStr;
}

int main(int argc, char *argv[])
{
    string Encode_Str;
    Encode_Str = UTF8_URL_ENCODE("苏BAA345");
    cout << Encode_Str << endl;
    cout << 1 << endl;
    string Decode_Str = UTF8_URL_DECODE(Encode_Str);
    cout << 1 << endl;
    cout  << Decode_Str << endl;
    return 0;

}
