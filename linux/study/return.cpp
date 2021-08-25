#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;

int main()
{
    const char a[] = "12345", b[] = "12345";
    cout << "a=" << a << ",b=" << b << endl;
    if (a == b) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    int ret = (a == b);
    cout << ret << endl;
    ret = strncmp(a, b, 5);
    cout << ret << endl;
    ret = (string(a) == string(b));
    cout << ret << endl;
    return 0;
}

