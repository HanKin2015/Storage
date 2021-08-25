#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int main()
{
    printf("%s\n", __FILE__);
    cout <<  __STDC__ << endl;
    cout << __LINE__ << endl;
    cout << __FUNCTION__ << endl;
    cout <<  __DATE__ << ' ' << __TIME__ << endl;
    return 0;
}
