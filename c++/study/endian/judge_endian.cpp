#include <iostream>
#include <stdio.h>
using namespace std;

static union { char c[4]; unsigned long mylong; } endian_test = {{ 'l', '?', '?', 'b' } };
#define ENDIANNESS ((char)endian_test.mylong)

static union {
    int i;
    char c;
} temp={1};

// 不出意外，这个比较的写法是有问题的，#if不支持变量比较
#if ((temp.c[0]) == 1)
#define BYTE_LITTLE_ENDIAN
#else
#define BYTE_BIG_ENDIAN
#endif

static union {
    int i;
    char c;
} temp1={'1'};

static union {
    char c;
    int i;
} temp2={'1'};

static union {
    int i;
    char c[sizeof(int)];
} temp3={1};


int checkCPU()
{
    union w
    {
        int  a;
        char b;
    }c;
    c.a = '1';
    cout << "b = " << c.b << endl;
        printf("%x",  c.b);
    if (c.b == 0x12) { 
        cout << "true" << endl;
    }  else {
        cout << "false" << endl;
    }
    return (c.b == 0x12); // 小端返回TRUE,大端返回FALSE
}

int main()
{
    char ret = '1234' >> 24;
    cout << ret << endl;

    ret = '4321' >> 24;
    cout << ret << endl;

    cout << temp1.c << endl;
    cout << temp2.c << endl;
    
    temp1.i = 1;
    temp2.i = 1;
    cout << temp1.c << endl;
    cout << temp2.c << endl;
    
    cout << temp3.c[0] << endl;
    cout << temp3.i << endl;
    cout << temp3.c[3] << endl;
 
    cout << ENDIANNESS << endl;
    cout << checkCPU() << endl;
    return 0;
}
