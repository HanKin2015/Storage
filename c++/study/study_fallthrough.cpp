#include <iostream>
using namespace std;

int main()
{
    int state = 1;
    switch(state) {
    case 0:
        cout << 0 << endl;
    case 1:
        cout << 1 << endl;
    case 2:
        cout << 2 << endl;
    default:
        cout << 3 << endl;
    }
    return 0;
}