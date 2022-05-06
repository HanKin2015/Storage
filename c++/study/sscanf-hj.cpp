#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    const char* str = "123";
    int n = 2;
    
    // 将str转换为%d格式存储到n
    sscanf(str, "%d", &n);
    cout << "n = " << n << endl;
    return 0;
}

