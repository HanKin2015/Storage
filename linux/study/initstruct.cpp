#include <iostream>
using namespace std;

struct node {
    int x;
    int y;
};

int main()
{
    struct node t1;
    struct node t2 = {1};
    struct node t3 = {1, 2};
    cout << t1.x << ' ' << t1.y << endl;
    cout << t2.x << ' ' << t2.y << endl;
    cout << t3.x << ' ' << t3.y << endl;
    return 0;
}
