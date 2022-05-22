#include <iostream>
#include <stdio.h>
using namespace std;

static union {
    int i;
    char c;
}endian={1};



const char test = 'k';
#if (test == 'k')
#define YES
#else
#define NO
#endif

int main()
{
#ifdef YES
    cout << "YES" << endl;
#endif

#ifdef NO
    cout << "NO" << endl;
#endif

    if (test == 'k') {
        cout << "HEJIAN" << endl;
    }


    cout << "c = " << endian.c << endl;
    printf("%d\n", endian.c);
    if (endian.c == 1) {
        cout << "little endian" << endl;
    }

    const char c = 65; //A
    cout << c << endl;
    printf("%c\n", c);

    // 神奇不神奇,把B赋值给i结果输出到c中
    endian.i = 66;
    cout << endian.c << endl;
    return 0;
}
