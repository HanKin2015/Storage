#include <bits/stdc++.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

void func(int arr[4])
{
    arr[2] = 234;
    return;
}

void f1(int i)
{
    cout << "i = " << i << endl;
    return;
}

typedef struct _stguestAddress{
    uint8_t ipLen;
    uint8_t macLen;
    char data[0];
}VDGuestAddress;

int main()
{
    const char *hj = "25hejianhahah";
    VDGuestAddress *yj = (VDGuestAddress *)hj;
    cout << yj->ipLen << endl;
    cout << yj->macLen << endl;
    cout << yj->data << endl;

    
    int a, b, c,
        d, e;
    d = 100;
    ++d;
    f1(++d);

    int hFile = open("./data", O_RDONLY);
    char str[100];
    read(hFile, str, 100);
    cout << strlen(str) << endl;
    cout << sizeof(str) << endl;
    cout << str << endl;
    
    uint32_t v = 540;
    cout << v << endl;
    uint32_t temp = htonl(v);
    cout << temp << endl;
 
    int arr[4];
    func(arr);
    cout << arr[2] << endl;
    return 0;
}

