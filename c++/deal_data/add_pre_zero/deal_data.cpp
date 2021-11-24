#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    
    string in, out;
    while (cin >> in) {
        if (in.size() < 2) {
            out = "0" + in;
        } else {
            out = in;
        }
        cout << out << " ";
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}