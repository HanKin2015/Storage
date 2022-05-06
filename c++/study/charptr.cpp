#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int Test(char **arg)
{
    if (arg == NULL) {
        cout << "arg is null!" << endl;
    } else {
        cout << "arg is not null" << endl;
    }
    return 0;
}

int main()
{
    char *c1 = NULL;
    Test(&c1);

    char **c2 = (char **)malloc(10*sizeof(char *));
    Test(c2);

    const char *c3 = "hejian";
    cout << "c3 = " << c3 << endl;
    cout << "*c3 = " << *c3 << endl;
    cout << "&c3 = " << &c3 << endl;
    c3 = "jian";
    cout << "c3 = " << c3 << endl;
    cout << "*c3 = " << *c3 << endl;
    cout << "&c3 = " << &c3 << endl;
    c3 += 2;
    cout << "c3 = " << c3 << endl;

    const string c4 = "hejian";
    cout << "*c3 = " << *c3 << endl;    
    cout << "&c3 = " << &c3 << endl;
    //c4 = "jian";

    char const *c5  = "hejian";
    c5 = "jian";
    cout << c5 << endl;
    return 0;
}
