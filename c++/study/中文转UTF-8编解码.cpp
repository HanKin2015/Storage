/*
 *
 * URL����(URL encoding)��Ҳ�����ٷֺű���(Percent-encoding)�� ���ض������ĵ�ͳһ��Դ��λ�� (URL)�ı�����ơ�
 * ����ԭ������Ҫת����ַ�תΪ16���ƣ�Ȼ����ҵ���ȡ4λ(����4λֱ�Ӵ���)��ÿ2λ��һλ��ǰ�����%�������%XY��ʽ��
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
    //utf-8-> unicode-> ����
    int len = strlen(URLcode.c_str());
    char* temp = new char[len + 1];
    temp[len] = '\0';
    int temp_pos = 0;

    //ȥ��%��
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

    //���ַ�ת�������֣��õ���ʵ��UTF8��
    for (int i = 0; i < UTF8len * 2; i+=2) {
        char convert[3] = { 0 };
        convert[0] = temp[i];
        convert[1] = temp[i + 1];
        char *end;
        int tempint = strtol(convert, &end, 16);
        UTF8str[i / 2] = tempint;
    }

    //UTF8ת����UTF16
    int wcslen = ::MultiByteToWideChar(CP_UTF8, NULL, UTF8str, UTF8len, NULL, 0);
    wchar_t* wszString = new wchar_t[wcslen + 1];
    ::MultiByteToWideChar(CP_UTF8, NULL, UTF8str, UTF8len, wszString, wcslen);
    wszString[wcslen] = L'\0';

    //��������
    std::wcout.imbue(std::locale("CHS"));
    //wcout << wszString << endl;

    //��wstring תΪ string
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

//���� תΪ utf-8
string UTF8_URL_ENCODE(char* Chinese)
{
    //���� -> unicode  -> utf-8
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
    Encode_Str = UTF8_URL_ENCODE("��BAA345");
    cout << Encode_Str << endl;
    cout << 1 << endl;
    string Decode_Str = UTF8_URL_DECODE(Encode_Str);
    cout << 1 << endl;
    cout  << Decode_Str << endl;
    return 0;

}
