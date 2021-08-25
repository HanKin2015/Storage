#include <iostream>
#include <cstring>
using namespace std;

#define a "b" "234"

void fun(const char *str)
{
    cout << "str = " << str << endl;
    cout << *str << endl;
    str++;
    cout << *str << endl;
    return;
}

int main()
{
    string sn = "";
    string mac = "";
    string msg = sn + "," + mac;
    if (sn.empty() && mac.empty()) {
        msg = "";
        cout << "null" << endl;
    }
    cout << sn << ' ' << mac << ' ' << msg << endl;

    string hj = "" + mac;
    cout << "hj = " << hj << endl;

    fun("abc");

    //strchr
    int i = 'a';
    cout << i << endl;

    char ip[] = "199.200.250.20";
    char *ret = NULL;
    ret = strtok(ip, ".");
    while (ret != NULL) {
        cout << ret << endl;
        ret = strtok(NULL, ".");
    }

    cout << a << endl;
    cout << "dsad" "12345" << endl;
    return 0;
}
