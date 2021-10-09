#include <iostream>
#include <string.h>

#include <typeinfo>
using namespace std;

int main()
{
    int *len = new int(100);
    int *arr = NULL;
    arr = new int[100];
    cout << "len type = " << typeid(len).name() << endl;
    cout << "arr type = " << typeid(arr).name() << endl;

    arr[55] = 100;
    arr[4] = 55;
    cout << arr[55] << endl;
    memset(arr, 0, *len);
    cout << arr[55] << endl;
    cout << arr[4] << endl;
    memset(arr, 0, sizeof(arr)*100);
    cout << arr[55] << endl;
    cout << len[0] << endl;
    cout << len[1] << endl;

    cout << sizeof(unsigned char) << endl;
    cout << sizeof(unsigned char *) << endl;
    return 0;
}
