#include <iostream>
using namespace std;

namespace my1 {
    int x = 123;
    int y = 456;
}

namespace my2 {
    int a = 98;
    int b = 76;
}
using namespace my2;

int main()
{
    int m = 100;
    {
        int n = 200;
    }
    cout << m << endl;
    //cout << n << endl;
    
    cout << my1::x << my1::y << endl;
    cout << a << b << endl;
    return 0;
}
