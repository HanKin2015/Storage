#include <iostream>
#include <stdio.h>
using namespace std;

static union { 
    char c[4]; 
    unsigned long mylong; 
} endian_test = {{ 'l', '?', '?', 'b' }};

#define ENDIANNESS2 ((char)endian_test.mylong)

static union {
        char c[4];
            unsigned long ul;
} endian = {{ 'l', '?', '?', 'b' }};
const char ENDIANNESS = ((char)endian.ul);
#if (ENDIANNESS == 'l')
#define BYTE_LITTLE_ENDIAN
#else
#define BYTE_BIG_ENDIAN
#endif


int main()
{
#ifdef BYTE_LITTLE_ENDIAN
    cout << "BYTE_LITTLE_ENDIAN" << endl;
#endif
#ifdef BYTE_BIG_ENDIAN
    cout << "BYTE_BIG_ENDIAN" << endl;
#endif

    cout << ENDIANNESS << endl;

    if (ENDIANNESS == 'l') {
        cout << "hejian" << endl;
    }
    return 0;
}
