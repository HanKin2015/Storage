// https://www.zhihu.com/question/264040979

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

typedef unsigned char u8;

// 分离含有汉字的字符串
// 一个汉字占三个字节
void test()
{
    string text = u8"机1器人3你4会什么";
    vector<string> vec;
    int len = text.size();
    for (int i = 0; i < len; i++) {
        //if (text[i] & 0x80) {
        if (text[i] < 0) {
            vec.push_back(text.substr(i, 3));
            i += 2;
        } else {
            vec.push_back(text.substr(i, 1));
        }
    }
    
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int main()
{
#if 0
    string text = u8"机器人你会什么";
    vector<char> vec;
    int len = text.size();
    cout << "len: " << len << endl;
    for (int i = 0; i < len; i++) {
        vec.push_back(text[i]);
        cout << text[i] << ' ';
    }
    cout << endl;
    
    cout << sizeof(text[0]) << endl;
    char c = text[0];
    cout << c << ' ' << text[0] << endl;
    
    int vec_size = vec.size();
    for (int i = 0; i < vec_size; i++) {
        cout << vec[i];
    }
    cout << endl << endl;
    
    string str("hfdja64我爱中华3jkdl;78"), strchar("");
    int ln = str.length();
    for(int i = 0; i < ln; i++) {
        cout << (int)str[i] << ' ';
        if (str[i] & 0x80) {
            strchar += str.substr(i, 1);
            cout << strchar << endl;
        }
    }
#endif
    test();
    return 0;
}
