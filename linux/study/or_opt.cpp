#include <iostream>
using namespace std;

int main()
{
    int x = 0;
    int y = 1;
   
    // 可加括号可不加
    int ret1 = x || y;
    int ret2 = (x || y);
    // error: expected primary-expression before ‘=’ token
    //ret1 ||= x;
    
    cout << ret1 << endl;
    cout << ret2 << endl;
    return 0;
}
