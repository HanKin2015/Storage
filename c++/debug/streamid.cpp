#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int val = 0x10007;
    int epid = val & 0xff;
    printf("%d\n", epid);
    int streamid = (val >> 16) & 0xffff;
    printf("%d\n", streamid);
    return 0;
}
