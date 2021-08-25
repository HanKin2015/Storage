#include <iostream>
using namespace std;

int func(int &x)
{
    x = 45;
    return 0;
}

int main()
{
    int x = 0;
    func(x);
    cout << x << endl;
    return 0;
}
