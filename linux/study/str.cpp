#include <iostream>
#include <stdio.h>
#include <string.h>
#define maxn (100)
using namespace std;

const char *hj = NULL;

struct node {
    int a;
    int b;
};

void func(const char *c)
{
    hj = "hello";
    if (!*c) {
        cout << "YES" << endl;
        return;
    }
    cout << "NO" << endl;
    return;
}

int main()
{
    struct node init = {0, 0};

    //func(NULL);
    func("0");
    func("");

    const char strr[]="1234xyz";
    const char *str1=strstr(strr,"34");
    cout << str1 << endl;

    const char *test = "abcd";
    cout << strlen(test) << endl;

    string s = "sangfor";
    const char *str = "he"
                "jian";
    s.append("123");
    cout << s << endl;
    cout << maxn << endl;
    cout << str << endl;
    
    const char *c = "~034";
    short *h = (short*)c;
    
    int len = strlen(c);
    for (int i = 0; i < len / 2; i++) {
        cout << h[i] << endl;
    }
    cout << endl;

    for (int i = 0; i < len; i += 2) {
        short a = c[i];
        short b = c[i + 1];
        short d = a + (b << 8);
        cout << d << endl;
    }

    cout << endl;
    unsigned char *p = (unsigned char*)c;
    for (int i = 0; i < len; i += 2) {
        unsigned short x = p[i];
        unsigned short y = p[i + 1];
        unsigned short z = x + (y << 8);
        cout << z << endl;
    }
    return 0;
}
