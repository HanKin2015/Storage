#include <iostream>
#include <cstdio>
#include <unistd.h>

int g;
static void test(int x, int y)
{
    short  x;
    int    y;
    double g;
    return;
}

int main()
{
    test(3, 4);
    return 0;
}
/*
[root@ubuntu0006:/media/sangfor/vdb/TransferStation] #g++ test_shadow.cpp -Wshadow
test_shadow.cpp: In function ‘void test(int, int)’:
test_shadow.cpp:8:12: error: declaration of ‘short int x’ shadows a parameter
     short  x;
            ^
test_shadow.cpp:9:12: error: declaration of ‘int y’ shadows a parameter
     int    y;
            ^
test_shadow.cpp:10:12: warning: declaration of ‘g’ shadows a global declaration [-Wshadow]
     double g;
            ^
test_shadow.cpp:5:5: note: shadowed declaration is here
 int g;
     ^
*/