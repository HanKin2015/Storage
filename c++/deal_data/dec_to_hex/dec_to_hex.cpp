#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    freopen("in.txt",  "r", stdin);
    freopen("out.txt", "w", stdout);

    int num;
    while (cin >> num) {
        printf("0x%04x\n", num);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}