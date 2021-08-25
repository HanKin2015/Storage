#include <iostream>
using namespace std;

static 
struct node {
    int x;
    
    struct son {
        int y;
    };
} hejian;

void func(node &tmp) 
{
    tmp.x = 100;
}

void f1(node::son &tmp)
{
    tmp.y = 250;
}

int main()
{
    node a;
    a.x = 10;
    cout << a.x << endl;
    func(a);
    cout << a.x << endl;
 
    node::son b;
    node::son c;
    b.y = 233;
    c.y = 1;
    cout << b.y << endl;
    f1(b);
    f1(c);
    cout << b.y << endl;
    cout << c.y << endl;
    return 0;
}
